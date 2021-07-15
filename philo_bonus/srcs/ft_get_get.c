/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 15:03:56 by tefroiss          #+#    #+#             */
/*   Updated: 2021/07/15 11:31:52 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	ft_init_time_philo(t_philo *philo, t_args *args)
{
	philo->time_limit[EAT] = args->t_eat;
	philo->time_limit[SLEEP] = args->t_sleep;
	philo->time_limit[DIED] = args->t_die;
	philo->time_limit[FORK] = 0;
	philo->time_limit[THINK] = 0;
	philo->time_limit[STOP] = 0;
}

void	ft_philo_init(int i, t_args *args, t_philo *philo, t_table *table)
{
	philo->index = i + 1;
	philo->alive = &table->alive;
	philo->args = args;
	philo->many_eat = args->n_eat;
	if (philo->index % 2 == 0)
		philo->status = FORK;
	else
		philo->status = SLEEP;
	philo->fork_take = 0;
	philo->lock_output = table->lock_output;
	philo->fork = table->fork;
	ft_init_time_philo(philo, args);
}

void	ft_get_arg(int ac, char **av, t_table *table)
{
	table->args.n_philo = ft_atoi(av[1]);
	table->args.t_die = ft_atoi(av[2]);
	table->args.t_eat = ft_atoi(av[3]);
	table->args.t_sleep = ft_atoi(av[4]);
	if (ac == 6)
		table->args.n_eat = ft_atoi(av[5]);
	else
		table->args.n_eat = -1;
}

void	ft_get_philo(t_table *table)
{
	int	i;

	table->philo = (t_philo *)malloc(sizeof(t_philo) * table->args.n_philo);
	if (table->philo)
	{
		i = 0;
		while (i < table->args.n_philo)
		{
			ft_philo_init(i, &table->args, &table->philo[i], table);
			table->philo[i].table = table;
			i++;
		}
	}
}
