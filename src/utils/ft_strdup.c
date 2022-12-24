/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaanit <rjaanit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 21:40:51 by nhanafi           #+#    #+#             */
/*   Updated: 2022/09/14 17:21:28 by rjaanit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_strdup(char *src)
{
	int		l;
	char	*cpy;
	int		i;

	if (!src)
		return (NULL);
	i = 0;
	l = ft_strlen(src);
	cpy = (char *)malloc(sizeof(char) * (l + 1));
	if (cpy == NULL)
		return (NULL);
	while (src[i])
	{
		cpy[i] = src[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}
