/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 02:28:55 by nhanafi           #+#    #+#             */
/*   Updated: 2022/12/26 04:18:31 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_coordinates	ft_atoc(char *str)
{
	t_coordinates	res;
	char			**list;

	list = ft_split(str, ',');
	if (ft_listlen(list) != 3 && ft_count(str, '.') != 3)
		exit(1);
	res.x = ft_atof(list[0]);
	res.y = ft_atof(list[1]);
	res.z = ft_atof(list[2]);
	free_list(list);
	return	(res);
}