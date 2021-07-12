/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 18:04:25 by tefroiss          #+#    #+#             */
/*   Updated: 2021/07/01 17:04:19 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_bonus.h"

int	ft_args(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac >= 5)
	{
		while (i < ac)
		{
			if (!ft_isnumber(av[i]))
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}
