/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 17:18:39 by tefroiss          #+#    #+#             */
/*   Updated: 2021/07/13 16:07:22 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	philo_do_something(t_philo *philo, void (*ph_action)(t_philo *))
{
	long	timestamp;
	long	time_passed;

	timestamp = get_timestamp(philo);
	time_passed = get_timestamp(philo) + philo->time_limit[philo->status];
	if (philo->many_eat == 0)
	{
		philo_pass_away(philo, STOP);
		return ;
	}
	if (timestamp > philo->args->t_die)
	{
		philo_pass_away(philo, DIED);
		return ;
	}
	if (time_passed > philo->time_limit[DIED])
	{
		philo_tempo(philo->time_limit[DIED] - timestamp);
		philo_pass_away(philo, DIED);
		return ;
	}
	ph_action(philo);
}

void	go_phiphi(t_philo *philo)
{
	static const t_actions	ph_action[4] = {
		ph_think,
		ph_eat,
		ph_take_fork,
		ph_sleep,
	};

	gettimeofday(&philo->begin_eat, NULL);
	while (philo->status != DIED && philo->status != STOP && *philo->alive)
		philo_do_something(philo, ph_action[philo->status]);
	sem_post(philo->fork);
	sem_post(philo->fork);
}

void	table_init(int ac, char **av, t_table *table)
{
	table->sema_init = 0;
	ft_get_arg(ac, av, table);
	sem_unlink("fork");
	sem_unlink("lock_output");
	table->fork = sem_open("fork", O_CREAT | O_EXCL, 0644, table->args.n_philo);
	if (!table->fork)
	{
		printf("ERROR : \nFORK SEMAPHORE INITIALIZATION FAILED\n");
		return ;
	}
	table->lock_output = sem_open("lock_output", O_CREAT | O_EXCL, 0644, 1);
	if (!table->lock_output)
	{
		printf("ERROR : \nLOCK_OUTPUT SEMAPHORE INITIALIZATION FAILED\n");
		return ;
	}
	table->alive = TRUE;
	ft_get_philo(table);
	table->sema_init = 1;
}

int	main(int ac, char **av)
{
	t_table	table;

	if (!ft_args(ac, av))
	{
		printf("I think... Something wrong with args. Is the Earth round ?\n");
		exit(EXIT_FAILURE);
	}
	table_init(ac, av, &table);
	if (!table.sema_init)
		exit(EXIT_FAILURE);
	launch_engine(&table);
	control_the_mind(&table);
	return (0);
}
