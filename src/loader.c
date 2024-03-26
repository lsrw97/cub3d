/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparreir <fparreir@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:18:26 by fparreir          #+#    #+#             */
/*   Updated: 2024/03/26 10:09:39 by fparreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <map.h>

int	get_texture_path(t_file *file, char *to_find, int position,
	char **texture_path)
{
	char	*temp;

	temp = ft_post_strnstr(file->file[position], to_find, 2);
	if (temp)
	{
		if (!*texture_path)
		{
			if (ft_strlen_no_ws(temp) != 0)
			{
				*texture_path = ft_strdup(temp);
				free(file->file[position]);
				file->file[position] = 0;
				return (0);
			}
		}
		else
		{
			ft_putendl_fd(ERR_DUP_TEXTURE, STDERR_FILENO);
			return (printf("texture_getter\n"), 1);
		}
	}
	return (0);
}

int	parse_textures(t_file *file, t_textures *textures)
{
	int		i;

	i = 0;
	while (i < file->file_size)
	{
		if (file->file[i]
			&& (get_texture_path(file, "NO", i, &textures->north_file)
				|| get_texture_path(file, "SO", i, &textures->south_file)
				|| get_texture_path(file, "EA", i, &textures->east_file)
				|| get_texture_path(file, "WE", i, &textures->west_file)))
			return (1);
		i++;
	}
	return (0);
}

//TODO: open textures?
int	load_textures_paths(t_file *file, t_textures *textures)
{
	if (parse_textures(file, textures))
	{
		printf("here\n");
		return (1);
	}
	if (!textures->south_file || ! textures->north_file
		|| !textures->east_file || !textures->west_file)
	{
		ft_putendl_fd(ERR_MISSING_TEXTURE, STDERR_FILENO);
		return (1);
	}
	return (0);
}

int	get_color(t_file *file, int position, long *color, char *to_find)
{
	char	*temp;

	temp = ft_post_strnstr(file->file[position], to_find, 2);
	if (temp)
	{
		if (!*color)
		{
			*color = rgb_to_int(temp);
			if (*color == -1)
				return (1);
			free(file->file[position]);
			file->file[position] = NULL;
			return (0);
		}
		ft_putendl_fd(ERR_DUP_COLORS, STDERR_FILENO);
		return (1);
	}
	return (0);
}

int	load_colors(t_file *file, t_textures *textures)
{
	int		i;

	i = 0;
	while (i < file->file_size)
	{
		if (file->file[i] != NULL)
		{
			if (get_color(file, i, &textures->ceiling, "C ")
				|| get_color(file, i, &textures->floor, "F "))
				return (1);
		}
		i++;
	}
	if (!textures->floor || !textures->ceiling)
	{
		ft_putendl_fd(ERR_MISSING_COLOR, STDERR_FILENO);
		return (1);
	}
	return (0);
}
