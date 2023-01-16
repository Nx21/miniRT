/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 15:06:30 by nhanafi           #+#    #+#             */
/*   Updated: 2023/01/15 15:07:08 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_coordinates cross_prod_c(t_coordinates v, t_coordinates u)
{
	t_coordinates res;

	res.x = v.y * u.z - v.z * u.y;
	res.y = v.z * u.x - v.x * u.z;
	res.z = v.x * u.y - v.y * u.x;

	return res;
}

double doty_prod_c(t_coordinates v, t_coordinates u)
{
	return v.x * u.x + v.y * u.y + v.z * u.z;
}

t_coordinates add_c(t_coordinates v, t_coordinates u)
{
	return mak_cor(v.x + u.x, v.y + u.y, v.z + u.z);
}

t_coordinates prod_c(double a, t_coordinates u)
{
	return mak_cor(a * u.x, a * u.y, a * u.z);
}


t_coordinates sub_c(t_coordinates v, t_coordinates u)
{
	return mak_cor(v.x - u.x, v.y - u.y, v.z - u.z);
}