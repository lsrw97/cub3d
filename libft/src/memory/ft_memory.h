/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memory.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparreir <fparreir@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:12:19 by fparreir          #+#    #+#             */
/*   Updated: 2023/12/06 16:19:33 by fparreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MEMORY_H
# define FT_MEMORY_H

# include "../../includes/libft.h"

void	*ft_memset(void *str, int c, size_t length);
void	*ft_memcpy(void *dest, const void *src, size_t length);
void	*ft_memmove(void *dest, const void *src, size_t length);
void	*ft_memchr(const void *str, int c, size_t length);
int		ft_memcmp(const void *s1, const void *s2, size_t length);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_fsplit(char **arr);

#endif
