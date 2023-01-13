/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 09:17:28 by nhanafi           #+#    #+#             */
/*   Updated: 2023/01/04 10:59:33 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include "structs.h"

int				ft_strlen(char *str);
char			*ft_join(char *s1, char *s2);
int				ft_instr(char *str, char c);
int				ft_get_last_ind(char *str, char *to_find);
unsigned int	ft_atoi(char *str);
char			*ft_strdup(char *src);
char			*ft_substr(char *s, int start, int len);
char			**ft_split(char *s, char c);
int				ft_strcmp(char *str1, char *str2);
int				ft_putstr_fd(char *s, int fd);
unsigned int	ft_atoi(char *str);
int				ft_get_last_ind(char *str, char *to_find);
void			*ft_memset(void *str, int c, size_t n);
char			*ft_strstr(char *str, char *ch1);
int				ft_isalnum( int str );
void			*ft_calloc(int number, int size);
char			*ft_strcat(char *dest, char *src);
int				ft_get_first_ind(char *str, char *to_find);
int				end_with(char *src, char *to_find);
int				start_with(char *src, char *to_find);
char			*ft_strtrim(char *s1, char *set);
int             check_negative(char *str, int *i);
double          ft_atof(char *str);
char            *ft_strchr(char *str, int c);
char            *ft_strrchr(char *str, int c);
size_t			ft_count(char *str, int c);
int				ft_listlen(char **list);
void			free_list(char **list);
t_coordinates	ft_atoc(char *str);
int				ft_atocolor(char *str);
#endif