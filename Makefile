# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgroleo <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/08 17:17:12 by jgroleo           #+#    #+#              #
#    Updated: 2019/11/08 17:17:32 by jgroleo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit

CC = gcc
CC_FLAGS = -Wall -Wextra -Werror

SRC_PATH = ./srcs/
INC_PATH = ./includes/
OBJ_PATH = ./obj/
LFT_PATH = ./libft/

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
INC = $(addprefix -I, $(INC_PATH))

OBJ_NAME = $(SRC_NAME:.c=.o)

INC_NAME = fillit.h

SRC_NAME = main.c \
	  read.c \
	  solve.c \
	  support.c

GREEN = \033[0;32m
WHITE = \033[m
RED = \033[0;31m

.PHONY: all clean fclean re

.SUFFIXES: .c .o

all: $(NAME)

$(NAME): $(LFT_PATH) $(OBJ)
	make -C $(LFT_PATH)
	$(CC) $(CC_FLAGS) $(OBJ) -o $(NAME) ./libft/libft.a
	@echo "$(GREEN)✓ Building $(NAME)$(WHITE)"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CC_FLAGS) $(INC) -o $@ -c $<

%.o: %.c
	$(CC) $(CC_FLAGS) -o $@ -c $<

clean:
	@make -C $(LFT_PATH) clean
	@/bin/rm -rf $(OBJ_PATH)
	@echo "$(RED)✗ Deletion of object files$(WHITE)"

fclean: clean
	@make -C $(LFT_PATH) fclean
	@/bin/rm -f $(NAME)
	@echo "$(RED)✗ Deletion of $(NAME)$(WHITE)"

re: fclean all
