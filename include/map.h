/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparreir <fparreir@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:57:00 by fparreir          #+#    #+#             */
/*   Updated: 2024/03/26 12:08:21 by fparreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include <types.h>
# include <libft.h>

int			parser(int ac, char **av);
t_map		*map(void);
int			validate_chunk(char **array, t_track *tracker);
int			map_load(t_map *ptr);
int			map_init(int ac, char **av);
int			validate_extension(char *file_path);
int			validate_args(int ac, char **av, char **file);
void		map_destroy(void);
char		**get_map(t_file *file, int map_size);

//textures
int			textures_parse(t_textures *textures);

//checker
int			recursion_is_fun(char **array, t_track *tracker);
int			is_map_well_placed(t_file *ptr);

//loader
int			load_colors(t_file *file, t_textures *textures);
int			get_texture_path(t_file *file, char *to_find, int pos,
				char **texture_ptr);
int			parse_textures(t_file *file, t_textures *textures);
int			get_color(t_file *file, int pos, long *color, char *to_find);
int			load_textures_paths(t_file *file, t_textures *textures);
int			validate_player(char **array);

// file
void		file_destroy(t_file *file);
t_file		*file_startup(void);
char		**load_file(char *file_path);

//utils.c
int			is_whitespace(char c);
int			get_map_size(t_file *ptr);
int			find_wall(char *line);
int			is_nothing(char c);
int			is_player(char c);
int			is_wall(char c);
int			rgb_to_int(char *rgb_str);
int			validate_chars(t_map *ptr);
int			ft_strlen_no_ws(char *str);
int			validate_rgb(const long colors[3]);
char		*ft_post_strnstr(char *haystack, char *needle, size_t size);
t_type		get_line_type(char *str, char prev, int pos, bool gaps);
void		clean_empty_lines(t_file *ptr);
void		check_tracker_positions(t_track *tracker, t_type current);
int			valid_texture(char *path);
int			check_surroundings(char **array, int x, int y);
int			validate_line(char *line, int y);

#endif //MAP_H