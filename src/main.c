/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 08:51:17 by nhanafi           #+#    #+#             */
/*   Updated: 2022/12/26 04:39:25 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	scene_init(t_scene *scene)
{
	scene->ambientcolor = -1;
	scene->fov = -1;
	scene->light_color = -1;
	scene->obj = NULL;
}

void	ambientchar(char *line, t_scene *scene, int fd)
{
	char **tmp;

	tmp = ft_split(line, ' ');
	if (scene->ambientcolor >= 0 || ft_listlen(tmp) != 3 || ft_strcmp(tmp[0], "A"))
		exit(1);
	scene->ratio = ft_atof(tmp[1]);
	scene->ambientcolor = ft_atocolor(tmp[2]);
	if (scene->ratio < 0 || scene->ratio > 1)
		exit(1);
	free(line);
	free_list(tmp);
	parse(scene, fd);
}

void	camera(char *line, t_scene *scene, int fd)
{
	char **tmp;

	tmp = ft_split(line, ' ');
	if (scene->fov >= 0 || ft_listlen(tmp) != 4 || ft_strcmp(tmp[0], "C"))
		exit(1);
	scene->cam_co = ft_atoc(tmp[1]);
	scene->cam_vec = ft_atoc(tmp[2]);
	scene->fov = ft_atof(tmp[3]);
	if (scene->fov < 0 || scene->fov > 180)
		exit(1);
	if (fabs(scene->cam_co.x) > 1 || fabs(scene->cam_co.y) > 1 || fabs(scene->cam_co.z) > 1)
		exit(1);
	free(line);
	free_list(tmp);
	parse(scene, fd);
}

void	light(char *line, t_scene *scene, int fd)
{
	char **tmp;

	tmp = ft_split(line, ' ');
	if (scene->fov >= 0 || ft_listlen(tmp) != 4 || ft_strcmp(tmp[0], "L"))
		exit(1);
	scene->light_co = ft_atoc(tmp[1]);
	scene->light_b = ft_atof(tmp[2]);
	scene->light_color = ft_atocolor(tmp[3]);
	if (scene->light_b < 0 || scene->light_b > 1)
		exit(1);
	free(line);
	free_list(tmp);
	parse(scene, fd);
}

void	parse(t_scene *scene, int fd)
{
	char	*line;

	line = get_next_line(fd);
	line = ft_strtrim(line, "\n \t");
	if (!line)
		return ;
	if (ft_strcmp(line, "") == 0)
		return (free(line), parse(scene, fd));
	if (start_with(line, "A"))
		return (ambient(line, scene, fd));
	if (start_with(line, "C"))
		return (camera(line, scene, fd));
	if (start_with(line, "L"))
		return (light(line, scene, fd));
	return obj(line, scene, fd);
}


int main(int argc, char const *argv[])
{
	t_scene	scene;
	int		fd;

	if (argc != 2)
		return 1;
	if (!end_with((char *)argv[1], ".rt"))
		return (1);
	fd = open("foo.txt", O_RDONLY);
	if(fd < 0)
		return (1);
	scene_init(&scene);
	parse(&scene, fd);
	return 0;
}
