/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparreir <fparreir@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 13:01:32 by fparreir          #+#    #+#             */
/*   Updated: 2023/11/26 18:50:36 by fparreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*result;

	if (ptr == NULL)
		return (malloc(size));
	if (!size)
		return (ptr);
	result = malloc(size);
	ft_memcpy(result, ptr, size);
	free(ptr);
	return (result);
}
