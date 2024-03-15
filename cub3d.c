/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelisaro <eelisaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:30:56 by eelisaro          #+#    #+#             */
/*   Updated: 2024/03/14 22:44:40 by eelisaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <fcntl.h>
#include <math.h>

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

double degreeToRadians(int degree)
{
	M_PI;
	return ((double)degree * M_PI / 180);
}

int	printline(t_data *data)
{
	int	wall = 0;
	int	nextWall = 0;
	// int	x;
	// int	y;
	// printf("%d, %d, %d, %f, %f\n", (int)floor(ray.y), (int)floor(ray.x), wall, rayCos, raySin);
	int i = 0;

	while(wall == 0)
	{
		data->player->ray.x += data->player->rayCos;
		data->player->ray.y += data->player->raySin;
		// x = data->player->ray.x + data->player->rayCos;
		// y = data->player->ray.y + data->player->raySin;
		wall = data->map->strmap[(int)floor(data->player->ray.y) / IMG_SIZE][(int)floor(data->player->ray.x) / IMG_SIZE] - 48;
		// printf("%f, %f, \n", data->player->ray.x, data->player->ray.y);
		// printf("%d, %d, \n", (int)floor(data->player->ray.x) % IMG_SIZE, (int)floor(data->player->ray.y) % IMG_SIZE);
		// printf("%d, %d, %d, %d, %d\n", (int)floor(data->player->ray.y) / IMG_SIZE, (int)floor(data->player->ray.x) / IMG_SIZE, wall, data->player->rayCos, data->player->raySin);
		my_mlx_pixel_put(data, (int)data->player->ray.x, (int)data->player->ray.y, 0xFFFF0000);
	}
	data->player->ray.last_point_x = data->player->ray.x;
	data->player->ray.last_point_y = data->player->ray.y;
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);

}

void	init_map(char *file, t_data *data)
{
	data->map->open = 0;
	data->map->x = 0;
	data->map->y = 0;
	data->map->px = -1;
	data->map->strmap = getmap(file);
	data->map->mw = ft_strlen(data->map->strmap[0]);
	data->map->mh = getmapy(data->map->strmap);
	data->mlx_win = mlx_new_window(data->mlx, data->map->mw * IMG_SIZE, data->map->mh * IMG_SIZE, "square");
	data->img = mlx_new_image(data->mlx, data->map->mw * IMG_SIZE, data->map->mh * IMG_SIZE);
	data->addr = mlx_get_data_addr(data->img, &data->bpp, &data->ll, &data->e);
	printf("cos: %f, sin: %f\n", cos(degreeToRadians(data->player->angle)), sin(degreeToRadians(data->player->angle)));
	printmap(data);
	// data->map = map;
}

void	moveright(t_data *data)
{
	data->player->ray.x = data->player->x;
	data->player->ray.y = data->player->y;
	data->player->angle++;
	data->player->rayCos = cos(degreeToRadians(data->player->angle));
	data->player->raySin = sin(degreeToRadians(data->player->angle));
	printf("cos: %f, sin: %f\n", cos(degreeToRadians(data->player->angle)), sin(degreeToRadians(data->player->angle)));
}

void	moveleft(t_data *data)
{
	data->player->ray.x = data->player->x;
	data->player->ray.y = data->player->y;
	data->player->angle--;
	data->player->rayCos = cos(degreeToRadians(data->player->angle));
	data->player->raySin = sin(degreeToRadians(data->player->angle));
	printf("cos: %f, sin: %f\n", cos(degreeToRadians(data->player->angle)), sin(degreeToRadians(data->player->angle)));
}

void	movefront(t_data *data)
{
	data->player->y += sin(degreeToRadians(data->player->angle));
	data->player->x += cos(degreeToRadians(data->player->angle));
	data->player->ray.x = data->player->x;
	data->player->ray.y = data->player->y;
	printf("%f, %f, %f\n", data->player->ray.x, data->player->x, data->player->rayCos);
	printf("cos: %f, sin: %f\n", cos(degreeToRadians(20)), sin(degreeToRadians(20)));
}

void	moveback(t_data *data)
{
	data->player->y -= sin(degreeToRadians(data->player->angle));
	data->player->x -= cos(degreeToRadians(data->player->angle));
	data->player->ray.x = data->player->x;
	data->player->ray.y = data->player->y;
	printf("%f, %f, %f\n", data->player->ray.x, data->player->x, data->player->rayCos);
	printf("cos: %f, sin: %f\n", cos(degreeToRadians(20)), sin(degreeToRadians(20)));
}

double calc_length(t_data *data)
{
	int dx = abs(data->player->x - data->player->ray.last_point_x);
	int dy = abs(data->player->y - data->player->ray.last_point_y);
	data->player->ray.distance = sqrt(pow(dx, 2) + pow(dy, 2));
	return sqrt(pow(dx, 2) + pow(dy, 2));
}

double	calc_wall_height(t_data *data)
{
	data->player->ray.wallheight = data->player->ray.wallheight = floor(HALFHEIGHT / data->player->ray.distance);
	return data->player->ray.wallheight;
}

void	shoot_rays(t_data *data)
{
	int rayCount = 0;
	double angle = data->player->angle;

	while(rayCount < WIN_WIDTH)
	{
		data->player->ray.x = data->player->x;
		data->player->ray.y = data->player->y;
		data->player->angle += RAYCAST_INCREMENT_ANGLE;
		data->player->rayCos = cos(degreeToRadians(data->player->angle));
		data->player->raySin = sin(degreeToRadians(data->player->angle));
		printf("%d, x: %f, y: %f, angle: %f, %f\n", rayCount, data->player->x, data->player->y, data->player->angle, RAYCAST_INCREMENT_ANGLE);
		printline(data);
		rayCount++;
	}
	data->player->angle = angle;
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
	printf("%f. %f\n", data->player->ray.last_point_x, data->player->ray.last_point_y);
	printf("length: %f, wallheight: %f\n\n", calc_length(data), calc_wall_height(data));
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
	printf("%p\n", data->map);
	data->player->dir = 1;
	data->player->ray.x = 100;
	data->player->ray.y = 66;
	printline(data);
}

int main(int argc, char ** argv)
{
	t_data		data;
	t_map		map;
	t_player	player;

	data.map = &map;
	data.player = &player;

	data.mlx = mlx_init();
	// data.mlx_win = mlx_new_window(data.mlx, 600, 900, "square");
	// data.img = mlx_new_image(data.mlx, 600, 900);
	// data.addr = mlx_get_data_addr(data.img, &data.bpp, &data.ll, &data.e);
	init_map(argv[1], &data);
	init_player(&data);
	// init_player(&player, &data);
	// validatemap(argv[1], &data);
	mlx_hook(data.mlx_win, 17, 1L << 2, freeexit, &data);
	mlx_put_image_to_window(data.mlx, data.mlx_win, data.img, 0, 0);

	mlx_hook((&data)->mlx_win,2, 1L<<0, movement, &data);
	mlx_loop(data.mlx);
}

// make floor, sky
