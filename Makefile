NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror -FPIC #-O3
INCLUDES = -I$(LIBFT_DIR)/includes -I$(INC_DIR)
LDFLAGS = -L$(LIBFT_DIR) -lft
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
SRC_DIR = src
INC_DIR = include
OBJ_DIR = build

SRC_FILES = main.c map.c loader.c file.c parse.c validation.c \
			utils.c utils1.c utils2.c utils3.c

SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^ $(INCLUDES) $(LDFLAGS)
	@echo "Done!"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDES)

$(LIBFT):
	@make -s -C $(LIBFT_DIR)

clion: CFLAGS += -g -g3 #-fsanitize=address
clion: re

valgrind: clion
	@valgrind --log-file=valgrind.log -s --leak-check=full \
		--show-leak-kinds=all --track-origins=yes \
 		./$(NAME) ./maps/valid_map1.cub

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

run: clion
	@./$(NAME) ./maps/valid_map1.cub

.PHONY: all clean fclean re clion valgrind