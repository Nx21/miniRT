/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 21:14:08 by nhanafi           #+#    #+#             */
/*   Updated: 2022/12/31 13:59:09 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int equal(double a, double b)
{
    return fabs(a - b) < EPSILON;
}

int greater(double a, double b)
{
    return a >= b || equal(a, b);
}

int equalc(t_coordinates a, t_coordinates b)
{
    return equal(a.x, b.x) && equal(a.y, b.y) && equal(a.z, b.z);
}


double  dist_sq(t_coordinates a, t_coordinates b)
{
    return pow(a.x + b.x, 2) + pow(a.y + b.y, 2) + pow(a.z + b.z, 2);
}
