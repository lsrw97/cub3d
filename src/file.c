/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparreir <fparreir@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:09:24 by fparreir          #+#    #+#             */
/*   Updated: 2024/03/18 11:07:44 by fparreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <map.h>

t_file	*file_startup(void)
{
	t_file	*res;

	res = malloc(sizeof(t_file));
	if (!res)
		return (NULL);
	res->file = NULL;
	res->file_size = 0;
	return (res);
}

void	file_destroy(t_file *file)
{
	int	i;

	if (!file)
		return ;
	if (file->file)
	{
		i = 0;
		while (i < file->file_size)
			free(file->file[i++]);
		free(file->file);
	}
	free(file);
}

int	count_file_lines(int fd)
{
	int		length;
	char	*line;

	length = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		free(line);
		length++;
	}
	close(fd);
	return (length);
}

char	**fill_file_array(int fd)
{
	char	**res;
	char	*line;
	int		length;

	res = ft_calloc(map()->file->file_size + 1, sizeof(char *));
	if (!res)
		return (NULL);
	length = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		res[length] = ft_strclean(line, '\n', ft_strlen(line));
		free(line);
		length++;
	}
	res[length] = 0;
	close(fd);
	return (res);
}

char	**load_file(char *file_path)
{
	int		fd;
	char	**res;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
	{
		ft_putendl_fd(ERR_FILE_OPEN, STDERR_FILENO);
		return (NULL);
	}
	map()->file->file_size = count_file_lines(fd);
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
	{
		ft_putendl_fd(ERR_FILE_OPEN, STDERR_FILENO);
		file_destroy(map()->file);
		map()->file = NULL;
		return (NULL);
	}
	res = fill_file_array(fd);
	return (res);
}
