# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eelisaro <eelisaro@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/16 17:02:19 by mgranate          #+#    #+#              #
#    Updated: 2024/03/14 16:33:19 by eelisaro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# /* ~~~~~~ SOURCES ~~~~~~ */
NAME		=	cub3d
CC			=	gcc

SRCS		=	cub3d.c

CFLAGS		=	-g -fsanitize=address # -Wall -Wextra -Werror
MLXFLAGS	=	-L ./mlx/ -lmlx -framework OpenGL -framework AppKit -lz
MLX 		=	mlx/libmlx.a
LIBFT		=	libft/libft.a
GETNEXTLINE =	getnextline/

RM			=	rm -f

OBJS		=	$(SRCS:%.c=%.o)

ifeq ($(shell uname), Linux)
MLXFLAGS	=	-L ./mlx/ -lmlx -Ilmlx -lXext -lX11 -lm
endif

all:		$(NAME)

$(NAME):	$(OBJS)
			@make -C libft
			@make -C mlx
			$(CC) $(SRCS) $(LIBFT) $(GNL) $(MLXFLAGS) $(CFLAGS) -o $(NAME)

clean:
			@make clean -C libft
			@make clean -C mlx
			$(RM) $(OBJS)

fclean:		clean
			@make fclean -C libft
			@make clean -C mlx
			$(RM) $(NAME)
			$(RM) $(OBJS)

re:			fclean all

.PHONY:		all clean fclean re
