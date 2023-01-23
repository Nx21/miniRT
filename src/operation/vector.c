/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 15:07:49 by nhanafi           #+#    #+#             */
/*   Updated: 2023/01/23 01:40:16 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_coordinates mak_cor(double x, double y, double z)
{
	t_coordinates res;

	res.x = x;
	res.y = y;
	res.z = z;
	return res;
}

t_coordinates norm_c(t_coordinates v)
{
	double magnitude;

	magnitude = sqrt(doty_prod_c(v,v));
	return prod_c(1/magnitude, v);	
}