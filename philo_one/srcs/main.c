/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 17:18:39 by tefroiss          #+#    #+#             */
/*   Updated: 2021/07/12 14:28:03 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

void	philo_pass_away(t_philo *philo, t_state status)
{
	int	timestamp;

	philo->status = status;
	pthread_mutex_lock(philo->lock_output);
	timestamp = get_timestamp(philo);
	if (*philo->alive)
	{
		if (philo->status == DIED)
		{
			printf("%d ... Philo %u ... %s", timestamp, philo->index, \
				"sadly DEAD... Rip.\n");
			*philo->alive = FALSE;
		}
		else if (philo->status == STOP)
		{
			printf("%d ... Philo %u ... %s", timestamp, philo->index, \
				"STOP everything. I'm not Gargantua. Just a Philo !\n");
		}
	}
	pthread_mutex_unlock(philo->lock_output);
}

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
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
}

void	table_init(int ac, char **av, t_table *table)
{
	ft_get_arg(ac, av, table);
	pthread_mutex_init(&table->lock_output, NULL);
	table->alive = TRUE;
	ft_get_fork(table);
	ft_get_philo(table);
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
	launch_engine(&table);
	control_the_mind(&table);
	return (0);
}
