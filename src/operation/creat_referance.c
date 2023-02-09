/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_referance.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 10:43:27 by nhanafi           #+#    #+#             */
/*   Updated: 2023/02/09 02:58:44 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ref	creat_ref(t_coordinates vec)
{
	t_ref	ref;

	ref.i = norm_c(vec);
	ref.j = norm_c(make_coor(ref.i.z,-ref.i.x,ref.i.y));
	ref.k = norm_c(cross_prod_c(ref.i, ref.j));
	ref.j = norm_c(cross_prod_c(ref.k, ref.i));
	return ref;
}