/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 23:15:01 by nhanafi           #+#    #+#             */
/*   Updated: 2022/12/26 00:58:02 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"



void    check_float(char *str)
{
    int i;

    if (ft_strchr(str, '.') != ft_strrchr(str, '.') &&\
    ft_strchr(str, 'e') != ft_strrchr(str, 'e') &&\
    ft_strchr(str, 'e') < ft_strrchr(str, '.'))
        exit(1);
	i = 0;
	while(str[i])
	{
		if ((str[i] < '0' || str[i] > '9') \
        && str[i] != 'e' && str[i] != '.')
			exit(1);
		i++;
	}
}

double ft_atof(char *str)
{
    double value;
    int sign;
    int i = 0;
    double scale;
    
    value = 0;
    i = 0;
    sign = 1 - 2 * (check_negative(str, &i) % 2);
    while (str[i] >= '0' && str[i] <= '9')
    {
        value = value * 10 + (str[i] - '0');
        i++;
    }
    if (str[i] == '.')
        i++;
    scale = 1.0;
    while (str[i] >= '0' && str[i] <= '9')
        value += (str[i++] - '0') * (scale *= 0.1);
    if (str[i] == 'e') 
        value *= pow(10, ft_atoi(str + i + 1));
    return sign * value;
}