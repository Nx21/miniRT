/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 17:14:15 by nhanafi           #+#    #+#             */
/*   Updated: 2022/12/24 23:27:26 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void draw_circle(void *mlx, void *win, int x0, int y0, int radius)
{
    int x = radius;
    int y = 0;
    int decisionOver2 = 1 - x;   // Decision criterion divided by 2 evaluated at x=r, y=0

    while(y <= x)
    {
        mlx_pixel_put(mlx, win,  x + x0,  y + y0, 0); // Octant 1
        mlx_pixel_put(mlx, win,  y + x0,  x + y0, 0); // Octant 2
        mlx_pixel_put(mlx, win, -x + x0,  y + y0, 0); // Octant 3
        mlx_pixel_put(mlx, win, -y + x0,  x + y0, 0); // Octant 4
        mlx_pixel_put(mlx, win, -x + x0, -y + y0, 0); // Octant 5
        mlx_pixel_put(mlx, win, -y + x0, -x + y0, 0); // Octant 6
        mlx_pixel_put(mlx, win,  x + x0, -y + y0, 0); // Octant 7
        mlx_pixel_put(mlx, win,  y + x0, -x + y0, 0); // Octant 8
        y++;
        if (decisionOver2<=0)
        {
            decisionOver2 += 2 * y + 1;   // Change in decision criterion for y -> y+1
        }
        else
        {
            x--;
            decisionOver2 += 2 * (y - x) + 1;   // Change for y -> y+1, x -> x-1
        }
    }
}

int main()
{
    void *mlx;
    void *win;
    int x, y, r;

    mlx = mlx_init();
    win = mlx_new_window(mlx, 640, 480, "My Window");
    for (size_t i = 0; i < 640; i++)
        for (size_t j = 0; j < 480; j++)
            mlx_pixel_put(mlx, win,  i,  j, ( 0x77ff0000) - (i * 0x77000000) / 640);

    x = 320;
    y = 240;
    r = 100;

    // draw_circle(mlx, win, x, y, r);
    for (int i = 0; i < 640; i++)
    {
        for (int j = 0; j < 480; j++)
        {
            if((i - x +100) * (i - x +100) + (j - y) * (j - y) <= r * r)
            {
                mlx_pixel_put(mlx, win,  i,  j, 0x55000000);
            }
        }
        printf("%d \n", ((((50 + i - x) *  0x77) / 100)));
    }
    for (int i = 0; i < 640; i++)
    {
        for (int j = 0; j < 480; j++)
        {
            if((i - x) * (i - x) + (j - y) * (j - y) <= r * r)
            {
                mlx_pixel_put(mlx, win,  i,  j, ((((100 + i - x) *  0x77) / 100)) + 20);
            }
        }
        printf("%d \n", ((((50 + i - x) *  0x77) / 100)));
    }
    

    mlx_loop(mlx);

    return 0;
}
