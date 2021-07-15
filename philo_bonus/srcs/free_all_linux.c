/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all_linux.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 12:12:28 by tefroiss          #+#    #+#             */
/*   Updated: 2021/07/15 11:38:51 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	its_the_end(t_table *table)
{
	if (table && table->philo)
	{
		free(table->philo);
		table->philo = NULL;
		table = NULL;
		sem_close(table->fork);
		sem_unlink("fork");
	}
	sem_close(table->lock_output);
	sem_unlink("lock_output");
}

void	clean_semaphore(t_philo *philo)
{
	if (philo->status == DIED)
		*philo->alive = FALSE;
	pthread_join(philo->threads, NULL);
	sem_close(philo->lock_output);
	sem_close(philo->fork);
	sem_unlink("fork");
	sem_unlink("lock_output");
}

void	clean_table(t_table	*table)
{
	if (table && table->philo)
	{
		free(table->philo);
		table->philo = NULL;
		table = NULL;
	}
}

void	philo_pass_away(t_philo *philo, t_state status)
{
	int	timestamp;

	philo->status = status;
	sem_wait(philo->lock_output);
	timestamp = get_timestamp(philo);
	if (*philo->alive)
	{
		if (philo->status == DIED)
		{
			printf("%d ... Philo %u ... %s", timestamp, philo->index, \
				"sadly DEAD... Rip in peace.\n");
			clean_semaphore(philo);
			clean_table(philo->table);
			exit(1);
		}
		else if (philo->status == STOP)
		{
			printf("%d ... Philo %u ... %s", timestamp, philo->index, \
				"STOP everything. I'm not Gargantua. Just a Philo !\n");
			sem_post(philo->lock_output);
			clean_semaphore(philo);
			clean_table(philo->table);
			exit(0);
		}
	}
}
