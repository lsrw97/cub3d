/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparreir <fparreir@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:59:41 by fparreir          #+#    #+#             */
/*   Updated: 2024/03/26 12:18:38 by fparreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# define ERR_MANY_ARGS "Error\nToo many arguments, goodbye!"
# define ERR_NO_MAP "Error\nNo map provided, goodbye!"
# define ERR_INVALID_EXTENSION "Error\nCould wrong file, goodbye!"
# define ERR_INVALID_MAP "Error\nInvalid map, goodbye!"
# define ERR_WRONG_MAP_POSITION "Error\nFound map before all assets, goodbye!"
# define ERR_NO_MAP_FOUND "Error\nCould not find any map, goodbye!"
# define ERR_INVALID_CHARS "Error\nThere are invalid chars in the map, goodbye!"
# define ERR_MULTIPLE_PLAYER "Error\nMore than one player found, goodbye!"
# define ERR_NO_PLAYER "Error\nCannot find a player, goodbye!"
# define ERR_DUP_TEXTURE "Error\nDuplicated texture, goodbye!"
# define ERR_MISSING_TEXTURE "Error\nOne of the textures wasn't found, goodbye!"
# define ERR_DUP_COLORS "Error\nDuplicated colors, goodbye!"
# define ERR_MISSING_COLOR "Error\nThere is a missing color, goodbye!"
# define ERR_MALLOC_FAIL "Error\nMemory allocation error, goodbye!"
# define ERR_INVALID_COLOR "Error\nI was given an invalid number, goodbye!"
# define ERR_FILE_OPEN "Error\nCannot open the map file, goodbye!"
# define ERR_INVALID_TEXTURE "Error\nOne of the textures is missing, goodbye!"

# include <libft.h>
# include <stdbool.h>

typedef struct s_textures	t_textures;
typedef struct s_track		t_track;
typedef struct s_point		t_point;
typedef struct s_file		t_file;
typedef struct s_map		t_map;
typedef enum e_type			t_type;

struct s_textures {
	long	floor;
	long	ceiling;
	char	*west_file;
	char	*east_file;
	char	*south_file;
	char	*north_file;
	void	*west;
	void	*east;
	void	*south;
	void	*north;
};

struct s_point {
	int		x;
	int		y;
	char	rotation;
};

enum e_type {
	NIL,
	HOLES,
	LIMIT,
	NORMAL,
	INVALID,
};

struct s_file {
	char	**file;
	int		file_size;
};

struct s_map {
	char		**map;
	int			height;
	char		*file_path;
	t_point		player;
	t_file		*file;
	t_textures	textures;
};

struct s_track {
	int		start;
	int		end;
	int		position;
	bool	gaps;
	t_type	prev;
};

#endif //TYPES_H
