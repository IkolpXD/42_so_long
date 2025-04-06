# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: made-jes <made-jes@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/04 17:35:32 by made-jes          #+#    #+#              #
#    Updated: 2025/04/05 15:21:08 by made-jes         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

# PATHS

LIBFT_DIR = ./libraries/libft

LIBFT = $(LIBFT_DIR)/libft.a

MINILIBX_DIR = ./libraries/minilibx-linux

MINILIBX = $(MINILIBX_DIR)/libmlx.a

INC = ./includes

SRC_DIR = ./sources

OBJ_DIR = ./obj

# Source files

SOURCES = so_long.c parsing.c map.c free_exit.c checker_map.c \
			gameplay.c utils.c utils2.c utils3.c \

SRCS = $(addprefix $(SRC_DIR)/, $(SOURCES))

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Compiler flags
CC = cc -g 

CFLAGS = -Wall -Wextra -Werror -I $(INC)

# Rules
all: $(NAME)

$(LIBFT):
	@echo "Libft is compiling..."
	@$(MAKE) -C $(LIBFT_DIR) > /dev/null
	@echo "Libft is compiled!"

$(MINILIBX):
	@echo "Minilibx is compiling"
	@$(MAKE) -C $(MINILIBX_DIR) > /dev/null
	@echo "Minilibx is compiled"
	
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@ > /dev/null

$(NAME): $(LIBFT) $(OBJS) $(MINILIBX)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MINILIBX) -Lmlx -lXext -lX11 -lm -lz -lbsd -o $(NAME) > /dev/null
	@echo "so_long is compiled!"

clean:
	@echo "Cleaning object files..."
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean > /dev/null
	@$(MAKE) -C $(MINILIBX_DIR) clean > /dev/null
	@echo "Objects cleaned!"

fclean: clean
	@echo "Cleaning project..."
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean > /dev/null
	@echo "All cleaned!"

re: fclean all

.PHONY: all clean fclean re libft minilibx