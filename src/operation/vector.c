/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orekabe <orekabe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 15:07:49 by nhanafi           #+#    #+#             */
/*   Updated: 2023/02/09 03:14:16 by orekabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_coordinates	make_coor(double x, double y, double z)
{
	t_coordinates	res;

	res.x = x;
	res.y = y;
	res.z = z;
	return (res);
}

double	magnitude(t_coordinates v)
{
	return (sqrt(dot_prod_c(v, v)));
}

t_coordinates	norm_c(t_coordinates v)
{
	return (prod_c(1 / magnitude(v), v));
}
