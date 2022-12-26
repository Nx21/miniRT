/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:59:19 by nhanafi           #+#    #+#             */
/*   Updated: 2022/12/26 00:52:18 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_strchr(char *str, int c)
{
	int		i;

	if (!c)
		return ((char *)str + ft_strlen(str));
	i = 0;
	while (str[i])
	{
		if ((int)str[i] == c)
			return ((char *)str + i);
		i++;
	}
	return (NULL);
}
