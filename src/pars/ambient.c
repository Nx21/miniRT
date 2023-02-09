/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orekabe <orekabe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 05:02:28 by nhanafi           #+#    #+#             */
/*   Updated: 2023/02/09 17:45:43 by orekabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ambient_pars(char *line, t_scene *scene, int fd)
{
	char	**tmp;

	tmp = ft_split(line, ' ');
	if (scene->ratio >= 0 || ft_lstsize(tmp) != 3 || ft_strcmp(tmp[0], "A"))
		err();
	scene->ratio = ft_atof(tmp[1]);
	scene->ambientcolor = ft_atocolor(tmp[2]);
	if (scene->ratio < 0 || scene->ratio > 1)
		err();
	free(line);
	free_list(tmp);
	pars(scene, fd);
}
