/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_referance.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 10:43:27 by nhanafi           #+#    #+#             */
/*   Updated: 2023/02/01 15:10:32 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ref	creat_ref(t_coordinates vec)
{
	t_ref	ref;

	ref.i = norm_c(vec);
	ref.j = make_coor(1,0,0);
	if(equal_coor(ref.i, make_coor(1,0,0)))
		ref.j = make_coor(0,1,0);
	ref.k = norm_c(cross_prod_c(ref.i, ref.j));
	ref.j = norm_c(cross_prod_c(ref.k, ref.i));
	return ref;
}