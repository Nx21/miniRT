/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orekabe <orekabe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 13:02:05 by nhanafi           #+#    #+#             */
/*   Updated: 2023/02/09 02:34:59 by orekabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	instr(char str, const char *to_find)
{
	int	i;

	i = 0;
	while (to_find[i])
	{
		if (to_find[i] == str)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char *s1, char *set)
{
	int		t[2];
	char	*res;

	if (!s1)
		return (NULL);
	if (!(*s1))
		return (free(s1), ft_strdup(""));
	if (!set || !(*s1))
		return (s1);
	t[0] = 0;
	t[1] = ft_strlen(s1) - 1;
	while (instr(s1[t[0]], set))
		t[0]++;
	if (t[1] <= t[0])
		return (free(s1), ft_strdup(""));
	while (instr(s1[t[1]], set))
		t[1]--;
	res = ft_substr(s1, t[0], t[1] - t[0] + 1);
	return (free(s1), res);
}
