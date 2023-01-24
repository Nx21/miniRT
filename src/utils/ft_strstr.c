/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 19:57:39 by nhanafi           #+#    #+#             */
/*   Updated: 2023/01/23 19:57:42 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_strstr(char *str, char *ch1)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	if (!ch1 || ch1[j] == '\0' )
		return ((char *)(str));
	while (str[i])
	{
		j = 0;
		while (ch1[j] && ch1[j] == str[i + j])
		{
			if (ch1[j + 1] == '\0')
				return ((char *) &str[i + j]);
			j++;
		}
		i++;
	}
	return (NULL);
}
