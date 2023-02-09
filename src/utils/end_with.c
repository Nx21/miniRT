/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_with.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orekabe <orekabe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 02:08:40 by nhanafi           #+#    #+#             */
/*   Updated: 2023/02/09 17:53:41 by orekabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	end_with(char *src, char *to_find)
{
	int	i;
	int	j;

	i = ft_strlen(src) - 1;
	j = ft_strlen(to_find) - 1;
	while (j >= 0)
	{
		if (i < 0 || src[i] != to_find[j])
			return (0);
		i--;
		j--;
	}
	return (1);
}

int	start_with(char *src, char *to_find)
{
	int	i;

	i = 0;
	while (to_find[i])
	{
		if (src[i] != to_find[i])
			return (0);
		i++;
	}
	return (1);
}
