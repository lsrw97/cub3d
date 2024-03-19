/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelisaro <eelisaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 13:21:32 by eelisaro          #+#    #+#             */
/*   Updated: 2024/03/19 12:44:43 by eelisaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
#include <stdlib.h>
#include "cub3d.h"
#include "mlx/mlx.h"
#include "./libft/libft.h"
#include <math.h>
#define IMG_SIZE 32
#define WIN_WIDTH 1080
#define WIN_HEIGHT 720
#define PLAYER_SIZE 20
#define WALL_COLOR 0xFF000000
#define FLOOR_COLOR 0xFFFFFFFF
#define PLAYER_COLOR 0xFF00FF00
#define RAY_COLOR 0xFFFF0000
#define FOV 60
#define RAYCAST_INCREMENT_ANGLE ((float)FOV / WIN_WIDTH)
#define	RAYPRECISION 32
#define HALFHEIGHT WIN_HEIGHT / 2
#define M_PI 3.14159265358979323846

typedef struct s_ray
{
	int		id;
	double	x;
	double	y;
	int		side;		// If an x-side was hit, side is set to 0, if an y-side was hit, side will be 1
	double	distance;
	double	wallheight;
	double	angle;
} t_ray;

typedef struct s_player
{
	double	x;
	double	y;
	double	angle;
	int		dir;
	t_ray	ray;
	double	rayCos;
	double	raySin;
} t_player;


typedef struct s_map
{
	int		x;
	int		y;
	int		px;
	int		py;
	char	**strmap;
	int		mh;
	int		mw;
	int		open;
} t_map;

typedef struct s_data
{
	void *mlx;
	void *mlx_win;
	int bpp;
	int ll;
	int e;
	void *img;
	char *addr;
	t_player *player;
	t_map *map;
} t_data;

#endif
