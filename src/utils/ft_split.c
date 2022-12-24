/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaanit <rjaanit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 02:08:04 by nhanafi           #+#    #+#             */
/*   Updated: 2022/09/16 02:22:23 by rjaanit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	check1(char *str, char c)
{
	int	i;
	int	count;
	int	j;

	j = 0;
	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c && j == 0)
		{
			count++;
			j = 1;
		}
		if (str[i] == c && j == 1)
			j = 0;
		i++;
	}
	return (count);
}

static int	check2(char *str, char c)
{
	int	count;

	count = 0;
	if (*str == c)
		str++;
	while (*str != c && *str != '\0')
	{
		count++;
		str++;
	}
	return (count);
}

char	*ft_free(int i, char **s)
{
	while (i >= 0)
	{
		free(s[i]);
		i--;
	}
	free(s);
	return (NULL);
}

char	**ft_split(char *s, char c)
{
	int		i;
	int		j;
	char	**ptr;
	int		len;

	i = 0;
	if (!s)
		return (NULL);
	len = check1(s, c);
	ptr = (char **)malloc(sizeof(char *) * (check1(s, c) + 1));
	if (!ptr)
		return (NULL);
	while (i < len)
	{
		while (*s == c && *s)
			s++;
		j = check2(s, c);
		ptr[i] = ft_substr(s, 0, j);
		if (!ptr)
			ft_free(i, ptr);
		s = s + j;
		i++;
	}
	ptr[i] = NULL;
	return (ptr);
}
