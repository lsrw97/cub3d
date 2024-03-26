/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparreir <fparreir@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 18:04:06 by fparreir          #+#    #+#             */
/*   Updated: 2024/03/26 12:08:49 by fparreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <map.h>

static int	fuck_norm(char prev, const char *str)
{
	return (is_nothing(prev) || is_player(prev)
		|| is_nothing(*(str + 1)) || is_player(*(str + 1)));
}

t_type	get_line_type(char *str, char prev, int pos, bool gaps)
{
	char	temp;

	if (!pos && str && ft_strlen(str) > (size_t)ft_strlen_no_ws(str))
		str = str + (ft_strlen(str) - ft_strlen_no_ws(str));
	if (!str && pos == 0)
		return (NIL);
	else if (str && ((pos == 0 && is_nothing(prev))
			|| (!*str && is_nothing(prev))))
		return (INVALID);
	else if ((str && !*str && is_wall(prev) && !gaps && pos > 0)
		|| (!str && is_wall(prev)))
		return (NORMAL);
	if (str && (is_wall(*str) || is_player(*str) || is_nothing(*str)))
		return (temp = *str, get_line_type(++str, temp, pos + 1, gaps));
	else if (str && is_whitespace(*str))
	{
		if (fuck_norm(prev, str))
			return (INVALID);
		if (!gaps)
			gaps = true;
		return (temp = *str, get_line_type(++str, temp, pos + 1, gaps));
	}
	if (gaps)
		return (HOLES);
	return (INVALID);
}

void	check_tracker_positions(t_track *tracker, t_type current)
{
	if (current != NIL && tracker->prev == NIL)
		tracker->start = tracker->position;
	if (current == NIL && tracker->prev != NIL)
		tracker->end = tracker->position + 1;
	if (tracker->position == 0)
		tracker->end = tracker->position;
	if (current == HOLES)
		tracker->gaps = true;
	tracker->prev = current;
}

void	clean_empty_lines(t_file *ptr)
{
	int	i;

	i = 0;
	while (i < ptr->file_size)
	{
		if (ptr->file[i] && !ft_strlen(ptr->file[i]))
		{
			free(ptr->file[i]);
			ptr->file[i] = NULL;
		}
		i++;
	}
}

int	check_surroundings(char **array, int x, int y)
{
	if (array[y] && (y > 0 && array[y - 1]) && array[y + 1])
	{
		if (ft_strlen(array[y - 1]) == ft_strlen(array[y])
			&& ft_strlen(array[y + 1]) == ft_strlen(array[y]))
		{
			return (is_whitespace(array[y][x - 1])
					|| is_whitespace(array[y][x + 1])
					|| is_whitespace(array[y - 1][x])
					|| is_whitespace(array[y + 1][x]));
		}
		else
		{
			if (x >= (int)ft_strlen(array[y - 1])
				|| x >= (int)ft_strlen(array[y + 1]))
				return (1);
		}
	}
	else if ((array[y] && (y > 0 && array[y - 1]) && !array[y + 1])
		|| (array[y] && (y > 0 && !array[y - 1]) && array[y + 1])
		|| y == 0)
		return (1);
	return (0);
}
