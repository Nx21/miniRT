/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 05:36:12 by nhanafi           #+#    #+#             */
/*   Updated: 2022/09/15 22:38:32 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	*ft_calloc(int number, int size)
{
	int		i;
	char	*c;

	i = 0;
	c = malloc(number * size);
	while (i < number * size)
	{
		c[i] = 0;
		i++;
	}
	return ((void *)c);
}
