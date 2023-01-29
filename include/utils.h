/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 09:17:28 by nhanafi           #+#    #+#             */
/*   Updated: 2023/01/26 17:20:32 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "structs.h"

int				ft_strlen(char *str);
char			*ft_strjoin(char *s1, char *s2);
unsigned int	ft_atoi(char *str);
char			*ft_strdup(char *src);
char			*ft_substr(char *s, int start, int len);
char			**ft_split(char *s, char c);
int				ft_strcmp(char *str1, char *str2);
int				ft_putstr_fd(char *s, int fd);
int				ft_get_first_ind(char *str, char *to_find);
int				ft_get_last_ind(char *str, char *to_find);
int				end_with(char *src, char *to_find);
int				start_with(char *src, char *to_find);
char			*ft_strtrim(char *s1, char *set);
int             check_negative(char *str, int *i);
double          ft_atof(char *str);
char            *ft_strchr(char *str, int c);
char            *ft_strrchr(char *str, int c);
size_t			ft_count(char *str, int c);
int				ft_lstsize(char **list);
void			free_list(char **list);
t_coordinates	ft_atoc(char *str);
int				ft_atocolor(char *str);
void        	ft_fswap(double *a, double *b);
#endif