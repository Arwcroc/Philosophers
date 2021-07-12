/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_n_launch.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 15:16:34 by tefroiss          #+#    #+#             */
/*   Updated: 2021/07/12 12:00:32 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

void	its_the_end(t_table *table)
{
	int	i;

	if (table)
	{
		i = 0;
		while (i < table->args.n_philo)
		{
			pthread_mutex_destroy(table->philo[i].left);
			pthread_mutex_destroy(table->philo[i].right);
			i++;
		}
		free(table->philo);
		free(table->fork);
	}
}

void	control_the_mind(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->args.n_philo)
	{
		pthread_join(table->philo[i].threads, NULL);
		i++;
	}
	its_the_end(table);
}

void	*create_phi_thread(void *philo)
{
	t_philo	*phiphi;

	phiphi = (t_philo *)philo;
	go_phiphi(phiphi);
	return (NULL);
}

void	launch_engine(t_table *table)
{
	int	i;

	if (table)
	{
		i = 0;
		while (i < table->args.n_philo)
		{
			pthread_create(&table->philo[i].threads, NULL, \
				create_phi_thread, &table->philo[i]);
			i++;
		}
	}
}
