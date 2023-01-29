/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 02:32:27 by nhanafi           #+#    #+#             */
/*   Updated: 2022/12/27 04:58:13 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int ft_lstsize(char **list)
{
	int len;

	if(!list)
		return 0;
	len = 0;
	while(list[len])
		len++;
	return len;
}

void	free_list(char **list)
{
	int	i;

	i = 0;
	while(list[i])
	{
		free(list[i]);
		i++;
	}
	free(list);
}