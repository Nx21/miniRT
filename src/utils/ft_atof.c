/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orekabe <orekabe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 23:15:01 by nhanafi           #+#    #+#             */
/*   Updated: 2023/02/09 17:46:05 by orekabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	check_float(char *str)
{
	int	i;

	if (ft_strchr(str, '.') != ft_strrchr(str, '.')
		&& ft_strchr(str, 'e') != ft_strrchr(str, 'e')
		&& ft_strchr(str, 'e') < ft_strrchr(str, '.'))
		err();
	i = 0;
	while (str[i])
	{
		if ((str[i] < '0' || str[i] > '9') \
			&& str[i] != 'e' && str[i] != '.')
			exit (1);
		i++;
	}
}

double	ft_atof(char *str)
{
	double	value;
	int		sign;
	int		i;
	double	scale;

	value = 0;
	i = 0;
	sign = 1 - 2 * (check_negative(str, &i) % 2);
	check_float(str + i);
	while (str[i] >= '0' && str[i] <= '9')
	{
		value = value * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] == '.')
		i++;
	scale = 1.0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		scale *= 0.1;
		value += (str[i++] - '0') * scale;
	}
	if (str[i] == 'e')
		value *= pow(10, ft_atoi(str + i + 1));
	return (sign * value);
}
