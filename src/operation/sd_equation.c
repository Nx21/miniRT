/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sd_equation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orekabe <orekabe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 22:24:59 by nhanafi           #+#    #+#             */
/*   Updated: 2023/02/09 03:19:34 by orekabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_quad_eq	sd_equation(t_quad_eq parm)
{
	parm.delta = pow(parm.b, 2) - 4 * parm.a * parm.c;
	if (parm.delta < 0)
		return (parm);
	parm.r1 = (-parm.b - sqrt(parm.delta)) / (2 * parm.a);
	parm.r2 = (-parm.b + sqrt(parm.delta)) / (2 * parm.a);
	if ((parm.r1 > parm.r2 || parm.r1 <= 0) && parm.r2 > 0)
		ft_fswap(&parm.r1, &parm.r2);
	if (parm.r1 < 0)
		parm.delta = -1;
	return (parm);
}
