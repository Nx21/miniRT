/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orekabe <orekabe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:59:11 by nhanafi           #+#    #+#             */
/*   Updated: 2023/02/09 02:35:20 by orekabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_strrchr(char *str, int c)
{
	int	len;

	if (!str)
		return (NULL);
	if (!c)
		return ((char *)str + ft_strlen(str));
	len = ft_strlen(str);
	while (len >= 0)
	{
		if ((int)str[len] == c)
			return ((char *)str + len);
		len--;
	}
	return (NULL);
}
