# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/27 19:01:34 by mpuig-ma          #+#    #+#              #
#    Updated: 2023/05/08 12:08:10 by mpuig-ma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

AUTHOR		?=	mpuig-ma

BUILD_DIR	:=	build
SRC_DIR		:=	src
LIBFT_DIR	:=	$(SRC_DIR)/libft
LIBFT		:=	$(LIBFT_DIR)/libft.a
NAME		:=	spider

CC			:=	gcc
CFLAGS		:=	-Wall -Werror -Wextra -MMD
LFLAGS		:=	-lcurl -L./$(LIBFT_DIR) -lft
DEBUG		:=	-g -fsanitize='address,undefined' -Og
CFLAGS		+=	$(DEBUG)
INC			:=	-I$(SRC_DIR) -I$(LIBFT_DIR)/src
RM			:=	rm -rf

#OS			:=	$(shell uname)
#ifeq ($(OS),Linux)
#	...
#endif

NOSTYLE		:=	\033[0m
STYLE		:=	\033[0;32m

SRC_FILES	:=	src/main.c
OBJ_FILES	=	$(addprefix $(BUILD_DIR)/, $(addsuffix .o, $(notdir $(basename $(SRC_FILES)))))
DEP_FILES	=	$(addprefix $(BUILD_DIR)/, $(addsuffix .d, $(notdir $(basename $(SRC_FILES)))))

.PHONY: clean fclean re all debug

$(NAME): $(LIBFT) $(OBJ_FILES) $(DEP_FILES) $(SRC_DIR)/arachnida.h
	$(CC) $(INC) $(CFLAGS) $(LFLAGS) -O3 $(OBJ_FILES) -o $(basename $@)
	@echo "Built $(STYLE)$(basename $@)$(NOSTYLE)"

$(LIBFT):
	make -C $(dir $@)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(INC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(BUILD_DIR)/
	make fclean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME)*

re: fclean
	$(MAKE)

all: $(NAME)
