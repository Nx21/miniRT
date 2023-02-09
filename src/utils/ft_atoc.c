/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orekabe <orekabe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 02:28:55 by nhanafi           #+#    #+#             */
/*   Updated: 2023/02/09 17:46:05 by orekabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_coordinates	ft_atoc(char *str)
{
	t_coordinates	res;
	char			**list;

	list = ft_split(str, ',');
	if (ft_lstsize(list) != 3 && ft_count(str, '.') != 3)
		err();
	res.x = ft_atof(list[0]);
	res.y = ft_atof(list[1]);
	res.z = ft_atof(list[2]);
	free_list(list);
	return (res);
}
