/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparreir <fparreir@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:34:25 by fparreir          #+#    #+#             */
/*   Updated: 2024/03/18 13:36:00 by fparreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <map.h>

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\v' || c == '\f' || c == '\r');
}

int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

int	is_wall(char c)
{
	return (c == '1');
}

int	is_nothing(char c)
{
	return (c == '0');
}

int	find_wall(char *line)
{
	int	i;

	if (!line)
		return (0);
	i = 0;
	while (is_whitespace(line[i]))
		i++;
	if (line[i] == '1' && line[i + 1]
		&& (is_whitespace(line[i + 1])
			|| is_player(line[i + 1])
			|| is_nothing(line[i + 1])
			|| is_wall(line[i + 1])))
		return (1);
	else
		return (0);
}
