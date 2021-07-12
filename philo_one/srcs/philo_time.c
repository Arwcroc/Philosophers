/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 15:14:55 by tefroiss          #+#    #+#             */
/*   Updated: 2021/06/28 15:15:17 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

long	transform_timeval_ms(struct timeval *time)
{
	return ((long)time->tv_usec / 1000 + (double)time->tv_sec * 1000);
}

long	get_timestamp(t_philo *philo)
{
	struct timeval	time;
	long			i;

	gettimeofday(&time, NULL);
	i = transform_timeval_ms(&time) - transform_timeval_ms(&philo->begin_eat);
	return (i);
}

long	get_actual_time(void)
{
	struct timeval	time;
	long			i;

	gettimeofday(&time, NULL);
	i = transform_timeval_ms(&time);
	return (i);
}

void	philo_tempo(int time_limit)
{
	long	dest_tmp;

	dest_tmp = get_actual_time() + time_limit;
	while (get_actual_time() < dest_tmp)
		usleep(1000);
}
