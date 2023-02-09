/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orekabe <orekabe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 21:14:08 by nhanafi           #+#    #+#             */
/*   Updated: 2023/02/09 03:21:06 by orekabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	equal(double a, double b)
{
	return (fabs(a - b) < 1e-6);
}

int	greater(double a, double b)
{
	return (a >= b || equal(a, b));
}

int	equal_coor(t_coordinates a, t_coordinates b)
{
	return (equal(a.x, b.x) && equal(a.y, b.y) && equal(a.z, b.z));
}

double	dist_sq(t_coordinates a, t_coordinates b)
{
	return (pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2));
}
