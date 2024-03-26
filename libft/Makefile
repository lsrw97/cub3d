# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fparreir <fparreir@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/12 15:45:36 by fparreir          #+#    #+#              #
#    Updated: 2023/05/23 12:33:42 by fparreir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc
CFLAGS = -Wall -Werror -Wextra
OBJDIR = build/
INCDIR = includes/
SRC = src/
CHAR = $(SRC)char/
FD = $(SRC)fd/
LISTS = $(SRC)lists/
MEM = $(SRC)memory/
NUM = $(SRC)numbers/
STR = $(SRC)string/
PRINTF = $(SRC)printf/
GNL = $(SRC)gnl/

SRC_CHAR = $(CHAR)ft_isalnum.c $(CHAR)ft_isalpha.c $(CHAR)ft_isascii.c \
		   $(CHAR)ft_isdigit.c $(CHAR)ft_isprint.c $(CHAR)ft_toupper.c  \
		   $(CHAR)ft_tolower.c
SRC_FD = $(FD)ft_putchar_fd.c $(FD)ft_putstr_fd.c $(FD)ft_putnbr_fd.c \
			$(FD)ft_putendl_fd.c
SRC_LISTS = $(LISTS)ft_lstadd_back.c $(LISTS)ft_lstadd_front.c \
			$(LISTS)ft_lstclear.c $(LISTS)ft_lstdelone.c \
			$(LISTS)ft_lstlast.c $(LISTS)ft_lstmap.c $(LISTS)ft_lstnew.c \
			$(LISTS)ft_lstsize.c $(LISTS)ft_lstget.c $(LISTS)ft_lstiter.c
SRC_MEM = $(MEM)ft_memchr.c $(MEM)ft_memcmp.c $(MEM)ft_memcpy.c \
			$(MEM)ft_calloc.c $(MEM)ft_memmove.c $(MEM)ft_memset.c \
			$(MEM)ft_realloc.c $(MEM)ft_fsplit.c
SRC_NUM = $(NUM)ft_atoi.c $(NUM)ft_itoa.c $(NUM)ft_atol.c
SRC_STR = $(STR)ft_bzero.c $(STR)ft_split.c $(STR)ft_strchr.c \
			$(STR)ft_strdup.c $(STR)ft_striteri.c $(STR)ft_strjoin.c \
			$(STR)ft_strlcat.c $(STR)ft_strlcpy.c $(STR)ft_strlen.c  \
			$(STR)ft_strmapi.c $(STR)ft_strncmp.c $(STR)ft_strnstr.c \
          $(STR)ft_strrchr.c $(STR)ft_strtrim.c $(STR)ft_substr.c \
          $(STR)ft_strclean.c
SRC_PRINTF = $(PRINTF)ft_printf.c $(PRINTF)put_utils.c $(PRINTF)utils.c
SRC_GNL = $(GNL)get_next_line.c $(GNL)get_next_line_utils.c

SOURCES = $(SRC_CHAR) $(SRC_FD) $(SRC_LISTS) $(SRC_MEM) $(SRC_NUM) $(SRC_STR) \
          $(SRC_PRINTF) $(SRC_GNL)
OBJECTS = $(patsubst $(SRC)%.c,$(OBJDIR)%.o,$(SOURCES))

all: $(NAME)

$(NAME): $(OBJDIR) $(OBJECTS)
	@echo "Compiling Libft"
	@ar rcs $(NAME) $(OBJECTS)
	@echo "Done!"

$(OBJDIR):
	@mkdir -p $(dir $(OBJECTS))

$(OBJDIR)%.o: $(SRC)%.c
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJDIR)

debug: CFLAGS += -g3
debug: fclean $(NAME)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
