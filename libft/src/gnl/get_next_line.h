/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparreir <fparreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 16:34:23 by fparreir          #+#    #+#             */
/*   Updated: 2023/05/23 12:34:52 by fparreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# include "../../includes/libft.h"

char	*get_next_line(int fd);
int		ft_strlenc(char *str);
char	*ft_strjoinc(char *s1, char *s2);
char	*ft_get_line(char *buffer);
char	*ft_del_line(char *buffer);
char	*ft_strchrc(char *str, char c);
char	*ft_get_buffer(char *buffer, int fd);

#endif
