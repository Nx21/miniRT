/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orekabe <orekabe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 04:11:13 by nhanafi           #+#    #+#             */
/*   Updated: 2023/02/09 17:46:05 by orekabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	check_negative(char *str, int *i)
{
	int	neg;

	neg = 0;
	while (str[*i] == ' ' || str[*i] == '\r'
		|| str[*i] == '\n' || str[*i] == '\v'
		|| str[*i] == '\f' || str[*i] == '\t')
		*i += 1;
	while (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			neg++;
		*i += 1;
	}
	return (neg);
}

void	check_int(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			err();
		i++;
	}
}

unsigned int	ft_atoi(char *str)
{
	int	i;
	int	a;
	int	neg;

	if (!str)
		return (0);
	i = 0;
	neg = check_negative(str, &i);
	check_int(str + i);
	a = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		a *= 10;
		a += str[i] - 48;
		i++;
	}
	if (neg % 2)
		a *= -1;
	return (a);
}
