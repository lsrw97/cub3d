/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelisaro <eelisaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 13:16:09 by eelisaro          #+#    #+#             */
/*   Updated: 2024/03/11 18:02:52 by eelisaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../long.h"
#include "../mlx/mlx.h"
#include "./getnextline/get_next_line.h"
#include "./libft/libft.h"

void	checken(t_data *data)
{
	if (data->map->strmap[data->player->y / 64][data->player->x / 64] == 'E'
	&& data->map->open)
	{
		write(1, "Amazing! You found all the apples! You Rock!!!", 47);
		freeexit(data);
	}
	if (data->map->strmap[data->player->y / 64][data->player->x / 64] == 'N')
	{
		write(1, "Ahhh you fell into the Blackhole! You are dead...\n", 50);
		freeexit(data);
	}
}

int	checkdoublestartexit(char **map)
{
	int	p;
	int	e;
	int	i;
	int	j;

	p = 0;
	e = 0;
	i = -1;
	j = -1;
	while (map[++i])
	{
		while (map[i][++j])
		{
			if (map[i][j] == 'P')
				p++;
			if (map[i][j] == 'E')
				e++;
		}
		j = 0;
	}
	if (e < 1 || e > 1 || p < 1 || p > 1)
		return (0);
	return (1);
}

int	getmapy(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	charcount(char *file)
{
	int		i;
	char	*s[1];
	int		fd;

	i = 0;
	fd = open(file, O_RDONLY);
	while (read(fd, s, 1))
		i++;
	return (i);
}

int	main(int argc, char *argv[])
{
	t_data		data;
	t_player	player;
	t_map		map;
	int			fd;

	fd = open(argv[1], O_RDONLY);
	if (argc != 2)
		return (!write(1, "Check your Parameters! You need one!\n", 37));
	if (fd < 0
		|| ft_strlen(ft_strnstr(argv[1], ".ber", ft_strlen(argv[1]))) != 4)
		return (!write(1, "Couldn't read the file!\n", 24));
	else
		close(fd);
	data.mlx = mlx_init();
	init_map(&map, argv[1], &data);
	// init_player(&player, &data);
	validatemap(argv[1], &data);
	mlx_hook(data.m_w, 17, 1L << 2, freeexit, &data);
	// mlx_key_hook((&data)->m_w, key_hookright, &data);
	mlx_loop(data.mlx);
}

// maps name extension
// double \n??
// path checking
