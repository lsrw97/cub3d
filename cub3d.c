/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelisaro <eelisaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:30:56 by eelisaro          #+#    #+#             */
/*   Updated: 2024/03/19 13:21:18 by eelisaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <fcntl.h>
#include <math.h>
#include <unistd.h>

int	freeexit(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->mlx_win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->ll + x * (data->bpp / 8));
	*(unsigned int *) dst = color;
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

char	**getmap(char *file)
{
	int		fd;
	char	*line;
	char	**map;
	int		i;

	i = 0;
	fd = open(file, O_RDONLY);
	line = malloc(charcount(file) + 1);
	while (read(fd, &line[i], 1))
		i++;
	line[i] = '\0';
	map = ft_split(line, '\n');
	free(line);
	return (map);
}

int	getmapy(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	printplayer(t_data *data, long long color)
{
	int			y;
	int			x;

	y = -1;
	x = -1;
	while (++y < PLAYER_SIZE)
	{
		while (++x < PLAYER_SIZE)
			my_mlx_pixel_put(data, x + data->map->x, y + data->map->y, color);
		x = -1;
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
}

void	printimg(t_data *data, long long color)
{
	int			y;
	int			x;

	y = -1;
	x = -1;

	while (++y < IMG_SIZE)
	{
		while (++x <= IMG_SIZE)
			my_mlx_pixel_put(data, x + data->map->x, y + data->map->y, color);
		x = -1;
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
}

void	checkforloce(t_data *data, int i, int j)
{
	if (data->map->strmap[i][j] == '1')
		printimg(data, 0xFFFFFFFF);
	else if (data->map->strmap[i][j] == '0')
		printimg(data, 0xFF000000);
	else if (data->map->strmap[i][j] == 'P')
		printplayer(data, 0xFFFFFF00);

}

void	printmap(t_data *data)
{
	int		i;
	int		j;

	i = -1;
	j = -1;
	while(++i < WIN_HEIGHT)
	{
		while (++j < WIN_WIDTH)
		{
			my_mlx_pixel_put(data, j, i, 0xFF000000);
		}
		j = 0;
	}
	i = -1;
	j = -1;
	while (data->map->strmap[++i])
	{
		while (data->map->strmap[i][++j])
		{
			checkforloce(data, i, j);
			data->map->x += IMG_SIZE;
		}
		data->map->x = 0;
		j = -1;
		data->map->y += IMG_SIZE;
	}
	data->map->x = 0;
	data->map->y = 0;
}

double degreeToRadians(double degree)
{
	M_PI;
	return (degree * M_PI / 180);
}

int	printline(t_data *data)
{
	int	wall = 0;

	while(wall == 0)
	{
		data->player->rayCos = cos(degreeToRadians(data->player->ray.angle));
		data->player->raySin = sin(degreeToRadians(data->player->ray.angle));
		data->player->ray.x += data->player->rayCos;
		data->player->ray.y += data->player->raySin;
		wall = data->map->strmap[(int)floor(data->player->ray.y) / IMG_SIZE][(int)floor(data->player->ray.x) / IMG_SIZE] - 48;
		my_mlx_pixel_put(data, (int)data->player->ray.x, (int)data->player->ray.y, 0xFFFF0000);
	}
		// printf("ray.x: %f, ray.y: %f, angle: %f, raySin: %f, rayCos: %f\n", data->player->ray.x, data->player->ray.y, data->player->angle, data->player->raySin, data->player->rayCos);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
}

void	init_map(char *file, t_data *data)
{
	data->map->open = 0;
	data->map->x = 0;
	data->map->y = 0;
	data->map->px = -1;
	data->map->strmap = getmap(file);
	data->map->mw = WIN_WIDTH;
	data->map->mh = WIN_HEIGHT;
	printf("llllllllllllllllllllllllllllllllllllllllllllllllllllllll\n");
	data->mlx_win = mlx_new_window(data->mlx, data->map->mw, data->map->mh, "square");
	data->img = mlx_new_image(data->mlx, data->map->mw, data->map->mh);
	data->addr = mlx_get_data_addr(data->img, &data->bpp, &data->ll, &data->e);
	// printf("cos: %f, sin: %f\n", cos(degreeToRadians(data->player->angle)), sin(degreeToRadians(data->player->angle)));
	printmap(data);
	// data->map = map;
}

void	moveright(t_data *data)
{
	data->player->ray.x = data->player->x;
	data->player->ray.y = data->player->y;
	data->player->angle += 20;
	data->player->rayCos = cos(degreeToRadians(data->player->angle));
	data->player->raySin = sin(degreeToRadians(data->player->angle));
	// printf("cos: %f, sin: %f\n", cos(degreeToRadians(data->player->angle)), sin(degreeToRadians(data->player->angle)));
}

void	moveleft(t_data *data)
{
	data->player->ray.x = data->player->x;
	data->player->ray.y = data->player->y;
	data->player->angle -= 20;
	data->player->rayCos = cos(degreeToRadians(data->player->angle));
	data->player->raySin = sin(degreeToRadians(data->player->angle));
	// printf("cos: %f, sin: %f\n", cos(degreeToRadians(data->player->angle)), sin(degreeToRadians(data->player->angle)));
}

void	movefront(t_data *data)
{
	data->player->y += sin(degreeToRadians(data->player->angle)) * 10;
	data->player->x += cos(degreeToRadians(data->player->angle)) * 10;
	data->player->ray.x = data->player->x;
	data->player->ray.y = data->player->y;
	// printf("%f, %f, %f\n", data->player->ray.x, data->player->x, data->player->rayCos);
	// printf("cos: %f, sin: %f\n", cos(degreeToRadians(20)), sin(degreeToRadians(20)));
}

void	moveback(t_data *data)
{
	data->player->y -= sin(degreeToRadians(data->player->angle));
	data->player->x -= cos(degreeToRadians(data->player->angle));
	data->player->ray.x = data->player->x;
	data->player->ray.y = data->player->y;
	// printf("%f, %f, %f\n", data->player->ray.x, data->player->x, data->player->rayCos);
	// printf("cos: %f, sin: %f\n", cos(degreeToRadians(20)), sin(degreeToRadians(20)));
}

double calc_distance(t_data *data)
{
	data->player->ray.distance = sqrt(pow(data->player->x - data->player->ray.x, (double)2) + pow(data->player->y - data->player->ray.y, (double)2));
	// data->player->ray.distance = data->player->ray.distance * cos(degreeToRadians(data->player->ray.angle - data->player->angle));
	// printf("\ndistance: %f, x %f, rx %f, y %f, ry %f\n\n", data->player->ray.distance, data->player->x, data->player->ray.x, data->player->y, data->player->ray.y);
	return data->player->ray.distance;
}

double	calc_wall_height(t_data *data)
{
	data->player->ray.wallheight = floor(WIN_HEIGHT / 2 / data->player->ray.distance * 32);

	// printf("Wallheight: %f, mapHeight: %f\n", data->player->ray.wallheight, data->map->mh);
	return data->player->ray.wallheight;
}

void	print_3d_line(t_data *data)
{
	int	y;
	int ty;
	y = -1;

	while (!isinf(data->player->ray.wallheight) && ++y < WIN_HEIGHT && y < data->player->ray.wallheight)
	{
		ty = WIN_HEIGHT / 2 - data->player->ray.wallheight / 2 + y;
		// printf("ty: %f\n", ty);
		if (ty > WIN_HEIGHT)
			ty = 0 + y;
		else if (ty < 0)
		{
			ty = 0 + y;
		}
		// printf("print3dLine: x: %d, y: %d, %f\n", (int)data->player->ray.id, ty, data->player->ray.wallheight);
		my_mlx_pixel_put(data, (int)data->player->ray.id, ty, 0xFF00FF00);
	}
}

void	print_ceil_floor()
{
	int i = -1;
	int j = -1;

	while (++i < WIN_HEIGHT / 2)
	{
		while (++j < WIN_WIDTH)
		{

		}
	}
}

void	shoot_rays(t_data *data)
{
	data->player->ray.id = 0;
	double angle = data->player->angle;

	while(data->player->ray.id < data->map->mw)
	{
		data->player->ray.x = data->player->x;
		data->player->ray.y = data->player->y;
		data->player->ray.angle = data->player->angle - 30 + RAYCAST_INCREMENT_ANGLE * data->player->ray.id;
		printline(data);
		calc_distance(data);
		calc_wall_height(data);
		print_3d_line(data);
		data->player->ray.id++;
	}
	data->player->ray.angle = angle;

	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
}

int	movement(int keycode, t_data *data)
{
	if (keycode == 65307)
	{
		write(1, "Closing Game!\n", 14);
		freeexit(data);
		exit(0);
	}
	else if (keycode == 100)
		moveright(data);
	else if (keycode == 97)
		moveleft(data);
	else if (keycode == 119)
		movefront(data);
	else if (keycode == 115)
		moveback(data);
	printmap(data);
	shoot_rays(data);
	// printline(data);
	// printf("length: %f, wallheight: %f\n\n", calc_distance(data), calc_wall_height(data));
}

void	init_player(t_data *data)
{
	t_ray ray;

	// define angle for direction
	data->player->angle = 90;
	data->player->x = 100;
	data->player->y = 66;
	data->player->rayCos = cos(degreeToRadians(data->player->angle));
	data->player->raySin = sin(degreeToRadians(data->player->angle));
	data->player->ray = ray;
	data->player->dir = 1;
	data->player->ray.x = data->player->x;
	data->player->ray.y = data->player->y;
	shoot_rays(data);
}

int main(int argc, char ** argv)
{
	t_data		data;
	t_map		map;
	t_player	player;

	data.map = &map;
	data.player = &player;

	data.mlx = mlx_init();
	init_map(argv[1], &data);
	init_player(&data);
	mlx_hook(data.mlx_win, 17, 1L << 2, freeexit, &data);
	mlx_put_image_to_window(data.mlx, data.mlx_win, data.img, 0, 0);
	mlx_hook((&data)->mlx_win,2, 1L<<0, movement, &data);
	mlx_loop(data.mlx);
}

// make floor, sky
