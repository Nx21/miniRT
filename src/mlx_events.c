/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orekabe <orekabe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 04:44:04 by orekabe           #+#    #+#             */
/*   Updated: 2023/02/09 17:56:35 by orekabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_close(t_scene *scene)
{
	mlx_destroy_image(scene->img.mlx, scene->img.img);
	mlx_destroy_window(scene->img.mlx, scene->img.mlx_win);
	exit(0);
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
	exit(0);
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
	*(unsigned int *)dst = color;
}
