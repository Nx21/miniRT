/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_front.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orekabe <orekabe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 04:40:49 by nhanafi           #+#    #+#             */
/*   Updated: 2023/02/09 04:54:44 by orekabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_obj	*add_front(t_obj *head, t_obj *obj)
{
	if (!head)
		return (obj);
	obj->next = head;
	return (obj);
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
	return (obj);
}
