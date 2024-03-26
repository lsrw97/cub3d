/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstget.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparreir <fparreir@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 18:20:04 by fparreir          #+#    #+#             */
/*   Updated: 2023/11/25 18:23:04 by fparreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lists.h"

t_list	*ft_lstget(t_list *lst, int index)
{
	int		i;
	t_list	*n;

	i = 0;
	n = lst;
	if (!n)
		return (NULL);
	if (!n->next)
		return (n);
	while (n != NULL)
	{
		if (i >= index)
			return (n);
		n = n->next;
		i++;
	}
	return (NULL);
}
