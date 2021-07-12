/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 17:48:18 by tefroiss          #+#    #+#             */
/*   Updated: 2021/05/29 18:22:19 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_one.h"

int	ft_atoi(char *str)
{
	int	i;
	int	result;

	result = 0;
	i = 0;
	if (str != NULL)
	{
		while (ft_isspace(*str))
			str++;
		if (*str == '-' || *str == '+')
			i = 1;
		while (str[i] && ft_isdigit(str[i]) != 0)
			result = result * 10 + (str[i++] - '0');
		if (*str == '-')
			return (-result);
		return (result);
	}
	return (0);
}
