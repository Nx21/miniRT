/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_back.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 04:40:49 by nhanafi           #+#    #+#             */
/*   Updated: 2022/12/27 05:28:45 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_obj *add_back(t_obj *head, t_obj *obj)
{
	t_obj	*tmp;
	if (!head)
	{
		obj->id = 0;
		return obj;
	}
	tmp = head;
	while(tmp->next)
		tmp = tmp->next;
	tmp->next = obj;
	obj->id = tmp->id + 1;
	return head;
}

t_obj	*new_obj(int type)
{
	t_obj	*obj;

	obj = (t_obj *)malloc(sizeof(t_obj));
	if (!obj)
		exit(1);
	obj->type = type;
	obj->next = NULL;
	return obj;
}