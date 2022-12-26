/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atocolor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 02:41:46 by nhanafi           #+#    #+#             */
/*   Updated: 2022/12/26 02:51:37 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_atocolor(char *str)
{
	int	res;
	t_coordinates tmp;

	tmp = ft_atoc(str);
	res = (((int)tmp.x & 0xff) << 16) + (((int)tmp.y & 0xff) << 8) + ((int)tmp.z & 0xff); 
	return (res);
}