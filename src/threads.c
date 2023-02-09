/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 04:46:51 by orekabe           #+#    #+#             */
/*   Updated: 2023/02/10 00:29:20 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	*routine(void *add)
{
	t_thread	*thread;
	int			i;
	int			j;
	int			c;

	i = 0;
	thread = add;
	while (i < WIDTH)
	{
		j = thread->start;
		while (j < thread->end)
		{
			c = ft_colortoi(pixel_color(*thread->scene, i, j));
			my_mlx_pixel_put(&thread->scene->img, i, j, c);
			j++;
		}
		i++;
	}
	return (NULL);
}

void	render(t_scene *scene)
{
	t_thread	*threads;
	int			n;
	int			i;

	i = 0;
	n = 6;
	threads = malloc(sizeof(t_thread) * n);
	if (!threads)
		err();
	while (i < n)
	{
		threads[i].scene = scene;
		threads[i].id = i;
		threads[i].start = ((i * HEIGHT) / n);
		threads[i].end = (((i + 1) * HEIGHT) / n);
		if (pthread_create(&threads[i].thread, NULL, &routine, threads + i))
			return ;
		i++;
	}
	i = -1;
	while (++i < n)
		if (pthread_join(threads[i].thread, NULL) != 0)
			return ;
	free(threads);
}
