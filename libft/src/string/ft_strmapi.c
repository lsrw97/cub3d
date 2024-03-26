/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparreir <fparreir@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 18:38:29 by fparreir          #+#    #+#             */
/*   Updated: 2023/05/13 14:34:45 by fparreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*buffer;

	i = -1;
	buffer = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!buffer)
		return (0);
	while (s[++i])
		buffer[i] = f(i, s[i]);
	buffer[i] = 0;
	return (buffer);
}
