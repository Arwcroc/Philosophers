/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_act_fork.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 15:08:23 by tefroiss          #+#    #+#             */
/*   Updated: 2021/06/28 15:08:48 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

void	take_fork(t_philo *philo)
{
	pthread_t	thread;

	philo->fork_take = 0;
	pthread_create(&thread, NULL, wait_irt, philo);
	pthread_detach(thread);
	pthread_mutex_lock(philo->left);
	scream_what_u_do(philo, \
		"take a FORK. It's mine now. What is property... ?\n");
	pthread_mutex_lock(philo->right);
	scream_what_u_do(philo, \
		"take a FORK. It's mine now. What is property... ?\n");
	philo->fork_take = 2;
}

void	ph_take_fork(t_philo *philo)
{
	long	time;

	if (philo->args->n_philo > 1)
	{
		take_fork(philo);
		philo->status = EAT;
		gettimeofday(&philo->begin_eat, NULL);
	}
	else
	{
		time = philo->time_limit[DIED] - get_timestamp(philo);
		philo_tempo(time);
		philo_pass_away(philo, DIED);
	}
}
