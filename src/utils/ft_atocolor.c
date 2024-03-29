/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atocolor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orekabe <orekabe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 02:41:46 by nhanafi           #+#    #+#             */
/*   Updated: 2023/02/09 17:46:05 by orekabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_color	ft_atocolor(char *str)
{
	t_color	res;
	char	**list;

	list = ft_split(str, ',');
	if (ft_lstsize(list) != 3 && ft_count(str, ',') != 3)
		err();
	res.r = ft_atof(list[0]);
	res.g = ft_atof(list[1]);
	res.b = ft_atof(list[2]);
	res.tr = 0;
	free_list(list);
	return (res);
}

t_color	ft_itocolor(int color)
{
	t_color	res;

	res.tr = (color >> 24) % 256;
	res.r = (color >> 16) % 256;
	res.g = (color >> 8) % 256;
	res.b = (color) % 256;
	return (res);
}

int	ft_colortoi(t_color color)
{
	if (color.r > 255)
		color.r = 255;
	if (color.r < 1)
		color.r = 0;
	if (color.g > 255)
		color.g = 255;
	if (color.g < 1)
		color.g = 0;
	if (color.b < 1)
		color.b = 0;
	if (color.b >= 255)
		color.b = 255;
	return ((((int)color.r) << 16) + (((int)color.g) << 8) + ((int)color.b));
}
