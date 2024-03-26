/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparreir <fparreir@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:57:33 by fparreir          #+#    #+#             */
/*   Updated: 2024/03/26 12:20:30 by fparreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <map.h>

t_map	*map(void)
{
	static t_map	map;

	return (&map);
}

int	map_init(int ac, char **av)
{
	t_map	*ptr;

	ptr = map();
	ptr->file = file_startup();
	ptr->player = (t_point){.x = -1, .y = -1};
	if (validate_args(ac, av, &ptr->file_path))
	{
		map_destroy();
		return (1);
	}
	return (0);
}

//todo: if something fails this function must also free the mlx_image
// pointers that ptr->textures may or may not already have initialized when
// the function is called.
void	map_destroy(void)
{
	int	i;

	if (map()->map)
	{
		i = 0;
		while (i < map()->height)
			free(map()->map[i++]);
		free(map()->map);
	}
	if (map()->file_path)
		free(map()->file_path);
	if (map()->textures.south_file)
		free(map()->textures.south_file);
	if (map()->textures.north_file)
		free(map()->textures.north_file);
	if (map()->textures.east_file)
		free(map()->textures.east_file);
	if (map()->textures.west_file)
		free(map()->textures.west_file);
	if (map()->file)
	{
		file_destroy(map()->file);
		map()->file = NULL;
	}
}

char	**get_map(t_file *file, int map_size)
{
	char	**result;
	char	*temp;
	int		i;
	int		k;

	result = ft_calloc(map_size + 1, sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	k = 0;
	while (i < file->file_size)
	{
		if (!file->file[i] && k > 0)
			result[++k] = NULL;
		if (file->file[i])
		{
			temp = file->file[i];
			file->file[i] = NULL;
			result[k++] = temp;
		}
		i++;
	}
	result[k] = 0;
	return (result);
}

int	is_map_well_placed(t_file *ptr)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < ptr->file_size)
	{
		if (ft_post_strnstr(ptr->file[i], "C ", 2)
			|| ft_post_strnstr(ptr->file[i], "F ", 2)
			|| ft_post_strnstr(ptr->file[i], "NO ", 3)
			|| ft_post_strnstr(ptr->file[i], "SO ", 3)
			|| ft_post_strnstr(ptr->file[i], "WE ", 3)
			|| ft_post_strnstr(ptr->file[i], "EA ", 3))
			count++;
		if (count < 6 && find_wall(ptr->file[i]) && ptr->file[i])
		{
			ft_putendl_fd(ERR_WRONG_MAP_POSITION, STDERR_FILENO);
			return (1);
		}
		i++;
	}
	return (0);
}
