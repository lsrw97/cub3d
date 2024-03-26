/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparreir <fparreir@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:12:08 by fparreir          #+#    #+#             */
/*   Updated: 2024/03/26 12:09:01 by fparreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <map.h>

int	get_map_size(t_file *file)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (i < file->file_size && !file->file[i])
		i++;
	if (i == (file->file_size - 1))
		return (0);
	while (i < file->file_size)
	{
		if ((res > 0 && !find_wall(file->file[i]))
			|| (file->file[i] && find_wall(file->file[i])))
			res++;
		i++;
	}
	return (res);
}

int	validate_rgb(const long colors[3])
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (colors[i] < 0 || colors[i] > 255)
		{
			ft_putendl_fd(ERR_INVALID_COLOR, STDERR_FILENO);
			return (1);
		}
		i++;
	}
	return (0);
}

int	rgb_to_int(char *rgb_str)
{
	long	rgb[3];
	char	**array;

	array = ft_split(rgb_str, ',');
	if (!array)
	{
		ft_putendl_fd(ERR_MALLOC_FAIL, STDERR_FILENO);
		return (-1);
	}
	if (!array[0] || !array[1] || !array[2])
	{
		ft_putendl_fd(ERR_MISSING_COLOR, STDERR_FILENO);
		ft_fsplit(array);
		return (-1);
	}
	rgb[0] = ft_atol(array[0]);
	rgb[1] = ft_atol(array[1]);
	rgb[2] = ft_atol(array[2]);
	if (validate_rgb(rgb))
		return (ft_fsplit(array), -1);
	ft_fsplit(array);
	return ((int)(rgb[0] << 16) | (int)(rgb[1] << 8) | (int)rgb[2]);
}

char	*ft_post_strnstr(char *haystack, char *needle, size_t size)
{
	char	*ptr;
	int		i;

	if (!haystack)
		return (NULL);
	ptr = ft_strnstr(haystack, needle, size);
	if (ptr)
	{
		i = 0;
		ptr += ft_strlen(needle);
		if (ptr)
		{
			while (is_whitespace(ptr[i]))
				i++;
			return ((ptr + i));
		}
		return (NULL);
	}
	return (NULL);
}

int	ft_strlen_no_ws(char *str)
{
	int	i;

	i = 0;
	while (str && *str && is_whitespace(*str))
		str++;
	while (str && *str++)
		i++;
	return (i);
}
