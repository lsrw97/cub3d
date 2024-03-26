/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparreir <fparreir@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:57:15 by fparreir          #+#    #+#             */
/*   Updated: 2024/03/26 11:47:57 by fparreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <map.h>

int	main(int ac, char **av)
{
	if (parser(ac, av))
	{
		map_destroy();
		return (1);
	}
	map_destroy();
	return (0);
}
