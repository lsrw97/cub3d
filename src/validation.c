/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparreir <fparreir@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 11:12:20 by fparreir          #+#    #+#             */
/*   Updated: 2024/03/26 11:27:26 by fparreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <map.h>

int	validate_args(int ac, char **av, char **file_path)
{
	if (ac > 2)
	{
		ft_putendl_fd(ERR_MANY_ARGS, STDERR_FILENO);
		return (1);
	}
	if (av[1] && !*file_path)
	{
		*file_path = ft_strdup(av[1]);
		return (0);
	}
	else
	{
		ft_putendl_fd(ERR_NO_MAP, STDERR_FILENO);
		return (1);
	}
}

int	validate_extension(char *file_path)
{
	char	*temp;

	temp = ft_strrchr(file_path, '.');
	if (temp)
	{
		if (ft_strncmp(temp, ".cub", 5) == 0)
			return (0);
		else
		{
			ft_putendl_fd(ERR_INVALID_EXTENSION, STDERR_FILENO);
			return (1);
		}
	}
	else
	{
		ft_putendl_fd(ERR_INVALID_EXTENSION, STDERR_FILENO);
		return (1);
	}
}

int	validate_chars(t_map *ptr)
{
	int	i;
	int	k;

	i = 0;
	while (i < ptr->height)
	{
		k = 0;
		while (ptr->map[i] && ptr->map[i][k])
		{
			if (!is_whitespace(ptr->map[i][k])
				&& !is_nothing(ptr->map[i][k])
				&& !is_player(ptr->map[i][k])
				&& !is_wall(ptr->map[i][k]))
				return (1);
			k++;
		}
		i++;
	}
	return (0);
}

int	validate_chunk(char **array, t_track *tracker)
{
	int	x;
	int	y;

	y = tracker->end;
	while (y <= tracker->start)
	{
		if (array[y])
		{
			x = 0;
			while (array[y][x])
			{
				if (is_nothing(array[y][x]) && check_surroundings(array, x, y))
					return (1);
				x++;
			}
		}
		y++;
	}
	return (0);
}

int	validate_line(char *line, int y)
{
	int	x;

	x = 0;
	while (line[x])
	{
		if (is_player(line[x]))
		{
			if (map()->player.x == -1 && map()->player.x == -1)
			{
				map()->player.x = x;
				map()->player.y = y;
				map()->player.rotation = line[x];
				return (0);
			}
			else
			{
				ft_putendl_fd(ERR_MULTIPLE_PLAYER, STDERR_FILENO);
				return (1);
			}
		}
		x++;
	}
	return (0);
}
