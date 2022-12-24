/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaanit <rjaanit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 06:28:51 by nhanafi           #+#    #+#             */
/*   Updated: 2022/09/14 17:24:20 by rjaanit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_instr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (c == str[i])
			return (i);
		i++;
	}
	return (-1);
}

int	ft_get_last_ind(char *str, char *to_find)
{
	int		i;
	int		j;
	char	c;

	i = ft_strlen(str) - 1;
	c = 0;
	while (i >= 0)
	{
		j = 0;
		if (!c && ft_instr("\"\'", str[i]) >= 0)
			c = str[i];
		else if (!c && ft_instr(")", str[i]) >= 0)
			c = str[i] - 1;
		else if (c == str[i])
			c = 0;
		while (!c && to_find[j] && str[i + j] == to_find[j])
			j++;
		if (!to_find[j])
			return (i + j - 1);
		i--;
	}
	return (-1);
}

int	ft_get_first_ind(char *str, char *to_find)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	c = 0;
	while (str[i])
	{
		j = 0;
		if (!c && ft_instr("\"\'", str[i]) >= 0)
			c = str[i];
		else if (!c && ft_instr("(", str[i]) >= 0)
			c = str[i] + 1;
		else if (c == str[i])
			c = 0;
		while (!c && to_find[j] && str[i + j] == to_find[j])
			j++;
		if (!to_find[j])
			return (i + j - 1);
		i++;
	}
	return (-1);
}
