/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orekabe <orekabe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 00:36:01 by orekabe           #+#    #+#             */
/*   Updated: 2023/02/08 05:37:24 by orekabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

typedef struct s_thread
{
    t_scene     *scene;
    pthread_t   thread;
    int         id;
    int         start;
    int         end;
}               t_thread;

void	ft_close(t_scene *scene)
{
	mlx_destroy_image(scene->img.mlx, scene->img.img);
	mlx_destroy_window(scene->img.mlx, scene->img.mlx_win);
	exit (0);
}

int	ft_keys(int key, t_scene *scene)
{
	if (key == 53)
		ft_close(scene);
	return (0);
}

int	ft_destroy(t_scene *scene)
{
	mlx_destroy_image(scene->img.mlx, scene->img.img);
	mlx_destroy_window(scene->img.mlx, scene->img.mlx_win);
	exit (0);
}

void	ft_hook(t_scene *scene)
{
	mlx_hook(scene->img.mlx_win, 2, 0, ft_keys, scene);
	mlx_hook(scene->img.mlx_win, 17, 0, ft_destroy, scene);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void    *routine(void *add)
{
    t_thread    *thread;

    thread = add;
    for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = thread->start; j < thread->end; j++)
		{
            pthread_mutex_lock(&thread->scene->mutex);
            int c = ft_colortoi(pixel_color(*thread->scene, i, j));
			my_mlx_pixel_put(&thread->scene->img, i, j, c);
            pthread_mutex_unlock(&thread->scene->mutex);
		}
	}
    pthread_mutex_lock(&thread->scene->mutex);
    thread->scene->rep++;
    pthread_mutex_unlock(&thread->scene->mutex);
    return (NULL);
}

void    create_threads(t_thread *threads)
{
    int i;

    i = 0;
    while(i < 8)
    {
        if (pthread_create(&threads[i].thread, NULL, &routine, threads + i))
            return ;
        i++;
    }
}

void    render(t_scene *scene)
{
    t_thread    *threads;
    int i;

    i = 0;
    scene->rep = 0;
    threads = malloc(sizeof(t_thread) * 8);
    if (!threads)
        return ;
    if (pthread_mutex_init(&scene->mutex, NULL))
        return ;
    while (i < 8)
    {
        threads[i].scene = scene;
        threads[i].id = i + 1;
        threads[i].start = (threads[i].id * (HEIGHT / 8)) - (HEIGHT / 8);
        threads[i].end = (threads[i].id * (HEIGHT) / 8);
        i++;
    }
    create_threads(threads);
    i = 0;
    while (1)
    {
        if (scene->rep > 7)
            break;
    }
    
}

void	scene_init(t_scene *scene)
{
	scene->ratio = -1;
	scene->fov = -1;
	scene->light = NULL;
	scene->obj = NULL;
	scene->v_cam = (t_coordinates **)malloc(WIDTH * sizeof(t_coordinates *));
	for (size_t i = 0; i < WIDTH; i++)
	{
		scene->v_cam[i] = (t_coordinates *)malloc(HEIGHT * sizeof(t_coordinates));
	}
	
}

void	change_referance(t_scene *scene)
{
	t_obj *obj;
	t_light *light;

	obj = scene->obj;
	while (obj)
	{
		obj->coor = sub_c(obj->coor, scene->cam_co);
		obj = obj->next;
	}
	light = scene->light;
	while(light)
	{
		light->light_co = sub_c(light->light_co, scene->cam_co);
		light = light->next;
	}
	scene->cam_co = sub_c(scene->cam_co, scene->cam_co);
}


void brighting(t_scene *scene)
{
	t_light *tmp;
	double	sum;

	tmp = scene->light;
	sum = 0;
	while (tmp)
	{
		sum++;
		tmp = tmp->next;
	}
	tmp = scene->light;
	while (tmp)
	{
		tmp->light_b /= sum;
		tmp = tmp->next;
	}
}

int main(int argc, char const *argv[])
{
	t_scene     scene;
	int	        fd;

	if (argc != 2)
		return 1;
	if (!end_with((char *)argv[1], ".rt"))
		return (1);
	fd = open(argv[1], O_RDONLY);
	if(fd < 0)
		return (1);
	scene_init(&scene);
	pars(&scene, fd);
	get_v_cam(&scene);
	change_referance(&scene);
	scene.img.mlx = mlx_init();
	scene.img.mlx_win = mlx_new_window(scene.img.mlx, WIDTH, HEIGHT, "miniRT");
	scene.img.img = mlx_new_image(scene.img.mlx, WIDTH, HEIGHT);
	scene.img.addr = mlx_get_data_addr(scene.img.img, &scene.img.bits_per_pixel, &scene.img.line_length,
								&scene.img.endian);
    render(&scene);
	mlx_put_image_to_window(scene.img.mlx, scene.img.mlx_win, scene.img.img, 0, 0);
	ft_hook(&scene);
    mlx_loop(scene.img.mlx);
	return 0;
}
