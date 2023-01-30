/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atocolor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 02:41:46 by nhanafi           #+#    #+#             */
/*   Updated: 2023/01/29 21:53:40 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_color	ft_atocolor(char *str)
{
	t_color	res;
	char	**list;

	list = ft_split(str, ',');
	if (ft_listlen(list) != 3 && ft_count(str, ',') != 3)
		exit(1);
	res.r = ft_atof(list[0]);
	res.g = ft_atof(list[1]);
	res.b = ft_atof(list[2]);
	res.tr = 0;
	free_list(list);
	return	(res);
}

t_color	ft_itocolor(int color)
{
	t_color	res;
	
	res.tr = (color >> 24) & 256;
	res.r = (color >> 16) % 256;
	res.g = (color >> 8) % 256;
	res.b = (color) % 256;
	return res;
}

int	ft_colortoi(t_color color)
{
	return  (((int)color.r ) << 16) + (((int)color.g ) << 8) + ((int)color.b);
}