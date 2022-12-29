/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 15:38:54 by orekabe           #+#    #+#             */
/*   Updated: 2022/12/27 05:03:17 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*ptr;
	int		i;
	int		j;

	if (!s1)
	{
		s1 = (char *)malloc(sizeof(char));
		*s1 = '\0';
	}
	if (!s2)
		return (NULL);
	i = -1;
	j = 0;
	ptr = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	while (s1[++i])
		ptr[i] = s1[i];
	while (s2[j])
		ptr[i++] = s2[j++];
	ptr[i] = '\0';
	free (s1);
	return (ptr);
}

char	*ft_read(char *str, int fd)
{
	char	*ptr;
	int		rd;

	rd = 1;
	ptr = (char *)malloc(1 + 1);
	if (!ptr)
		return (NULL);
	while (!ft_strchr(str, '\n') && rd != 0)
	{
		rd = read(fd, ptr, 1);
		if (rd == -1)
		{
			free (ptr);
			return (NULL);
		}
		ptr[rd] = '\0';
		str = ft_strjoin(str, ptr);
	}
	free (ptr);
	return (str);
}
