/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_front.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 04:40:49 by nhanafi           #+#    #+#             */
/*   Updated: 2023/01/26 17:23:55 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_obj *add_front(t_obj *head, t_obj *obj)
{
	if (!head)
		return obj;
	obj->next = head;
	return obj;
}

t_obj	*new_obj(int type)
{
	t_obj	*obj;

	obj = (t_obj *)malloc(sizeof(t_obj));
	if (!obj)
		exit(1);
	obj->type = type;
	obj->next = NULL;
	obj->id = 0;
	return obj;
}