/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orekabe <orekabe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 05:36:12 by nhanafi           #+#    #+#             */
/*   Updated: 2023/02/09 17:52:22 by orekabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	*ft_calloc(int number, int size)
{
	int		i;
	char	*c;

	i = 0;
	c = malloc(number * size);
	if (!c)
		return (NULL);
	while (i < number * size)
	{
		c[i] = 0;
		i++;
	}
	return ((void *)c);
}
