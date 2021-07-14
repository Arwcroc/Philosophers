/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_n_launch.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 15:16:34 by tefroiss          #+#    #+#             */
/*   Updated: 2021/07/13 15:58:38 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

// void	its_the_end(t_table *table)
// {
// 	if (table && table->philo)
// 	{
// 		free(table->philo);
// 		sem_unlink("fork");
// 		sem_close(table->fork);
// 	}
// 	sem_unlink("lock_output");
// 	sem_close(table->lock_output);
// }

void	del_philo_th(t_table *table)
{
	int	i;

	if (table)
	{
		i = 0;
		while (i < table->args.n_philo)
		{
			kill(table->philo[i].fork_philo, SIGKILL);
			i++;
		}
	}
}

void	control_the_mind(t_table *table)
{
	int	signal;

	signal = 0;
	while (!signal)
	{
		if (waitpid(-1, &signal, 0) <= 0)
			break ;
	}
	del_philo_th(table);
	clean_semaphore(table->philo);
	clean_table(table);
}

void	create_phi_fork(t_philo *philo, t_table *table)
{
	philo->fork_philo = fork();
	if (philo->fork_philo == 0)
		go_phiphi(philo);
	else if (philo->fork_philo < 0)
	{
		printf("ERROR:\nFORK FAILED\n");
		del_philo_th(table);
		its_the_end(table);
		exit(-1);
	}
}

void	launch_engine(t_table *table)
{
	int	i;

	if (table)
	{
		i = 0;
		while (i < table->args.n_philo)
		{
			create_phi_fork(&table->philo[i], table);
			i++;
		}
	}
}
