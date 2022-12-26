/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 15:01:29 by orekabe           #+#    #+#             */
/*   Updated: 2022/12/26 00:51:56 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include "utils.h"

#define BUFFER_SIZE 42
char	*get_next_line(int fd);
char	*ft_read(char *str, int fd);
char	*ft_strjoin(char *s1, char *s2);
#endif