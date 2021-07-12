/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_act.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 16:54:13 by tefroiss          #+#    #+#             */
/*   Updated: 2021/07/12 14:34:58 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

void	scream_what_u_do(t_philo *philo, char *str)
{
	int	time;

	time = get_timestamp(philo);
	pthread_mutex_lock(philo->lock_output);
	if (*philo->alive == TRUE)
		printf("%d ... Philo %u ... %s", time, philo->index, str);
	pthread_mutex_unlock(philo->lock_output);
}

void	ph_sleep(t_philo *philo)
{
	scream_what_u_do(philo, "is SLEEPING. Rompich Rompich...zzZ...Zzzz...\n");
	philo_tempo(philo->time_limit[SLEEP]);
	philo->status = THINK;
}

void	ph_think(t_philo *philo)
{
	scream_what_u_do(philo, \
	"is THINKING. What is the answer to life the universe and everything...\n");
	philo->status = FORK;
}

void	ph_eat(t_philo *philo)
{
	scream_what_u_do(philo, "is EATING. Nom Nom Nom Nom Nom... Buuuurp !\n");
	philo_tempo(philo->time_limit[EAT]);
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
	if (philo->many_eat > 0)
		philo->many_eat--;
	philo->status = SLEEP;
}

void	*wait_irt(void *philo)
{
	t_philo	*phiphi;

	phiphi = (t_philo *)philo;
	while (phiphi->fork_take != 2)
	{
		if (get_timestamp(phiphi) > phiphi->time_limit[DIED])
		{
			philo_pass_away(phiphi, DIED);
			return (NULL);
		}
		philo_tempo(1);
	}
	return (NULL);
}
