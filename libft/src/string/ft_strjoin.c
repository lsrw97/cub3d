/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparreir <fparreir@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:01:15 by fparreir          #+#    #+#             */
/*   Updated: 2023/05/13 14:34:01 by fparreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*buffer;
	size_t	total_len;
	size_t	i;

	i = 0;
	total_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	buffer = (char *)malloc(total_len * sizeof(char));
	if (!buffer)
		return (0);
	while (*s1)
		buffer[i++] = *s1++;
	while (*s2)
		buffer[i++] = *s2++;
	buffer[i] = 0;
	return (buffer);
}
