/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparreir <fparreir@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:58:56 by fparreir          #+#    #+#             */
/*   Updated: 2024/03/26 11:46:47 by fparreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <map.h>

int	parser(int ac, char **av)
{
	t_track	temp;

	if (map_init(ac, av))
		return (1);
	if (map_load(map()))
	{
		map_destroy();
		exit(1);
	}
	temp = (t_track){.start = map()->height - 1, .end = -1,
		.position = map()->height - 1, .gaps = false, .prev = NIL};
	if (recursion_is_fun(map()->map, &temp))
	{
		ft_putendl_fd(ERR_INVALID_MAP, STDERR_FILENO);
		return (1);
	}
	if (validate_player(map()->map))
		return (1);
	if (textures_parse(&(map()->textures)))
		return (1);
	return (0);
}

int	map_load(t_map *ptr)
{
	if (validate_extension(ptr->file_path))
		return (1);
	ptr->file->file = load_file(ptr->file_path);
	if (!ptr->file->file || is_map_well_placed(ptr->file))
		return (1);
	clean_empty_lines(ptr->file);
	if (load_textures_paths(ptr->file, &ptr->textures)
		|| load_colors(ptr->file, &ptr->textures))
		return (1);
	ptr->height = get_map_size(ptr->file);
	if (!ptr->height)
	{
		ft_putendl_fd(ERR_NO_MAP_FOUND, STDERR_FILENO);
		return (1);
	}
	ptr->map = get_map(ptr->file, ptr->height);
	if (validate_chars(ptr))
	{
		ft_putendl_fd(ERR_INVALID_CHARS, STDERR_FILENO);
		return (1);
	}
	file_destroy(ptr->file);
	ptr->file = NULL;
	return (0);
}

int	recursion_is_fun(char **array, t_track *tracker)
{
	char	*temp;
	t_type	current;

	if ((tracker->position < 0 && tracker->prev != INVALID) \
	|| (tracker->position - 1 < -1 || tracker->position + 1 > map()->height))
		return (0);
	temp = *(array + tracker->position);
	if (temp)
		current = get_line_type(temp, *temp, 0, false);
	else
		current = get_line_type(temp, 0, 0, false);
	if (current == INVALID)
		return (1);
	check_tracker_positions(tracker, current);
	if ((tracker->start > 0 || tracker->start != tracker->position)
		&& tracker->end != -1)
	{
		if (validate_chunk(array, tracker))
			return (1);
		tracker->start = -1;
		tracker->end = -1;
	}
	tracker->position -= 1;
	return (recursion_is_fun(array, tracker));
}

int	validate_player(char **array)
{
	int	y;

	y = 0;
	while (y <= map()->height)
	{
		if (array[y])
		{
			if (validate_line(array[y], y))
				return (1);
		}
		y++;
	}
	if (map()->player.x != -1 && map()->player.x != -1)
		return (0);
	ft_putendl_fd(ERR_NO_PLAYER, STDERR_FILENO);
	return (1);
}

int	textures_parse(t_textures *textures)
{
	if (valid_texture(textures->north_file)
		|| valid_texture(textures->south_file)
		|| valid_texture(textures->east_file)
		|| valid_texture(textures->west_file))
		return (1);
	return (0);
}
