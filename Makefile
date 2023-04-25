# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/25 15:58:23 by mpuig-ma          #+#    #+#              #
#    Updated: 2023/04/25 19:17:03 by mpuig-ma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

AUTHOR		?=	mpuig-ma
BUILD_DIR	:=	build
SRC_DIR		:=	src
NAME		:=	spider

CC			:=	gcc
CFLAGS		:=	-Wall -Werror -Wextra
CFLAGS		+=	-MMD
LFLAGS		:=	-lcurl
DEBUG		:=	-g -fsanitize='address,undefined'
#CFLAGS		+=	$(DEBUG)
INC			:=	-I$(SRC_DIR)
RM			:=	rm -rf

OS			:=	$(shell uname)
#ifeq ($(OS),Linux)
#endif

NOSTYLE		:=	\033[0m
STYLE		:=	\033[0;32m

SRC_FILES	:=	main.c
OBJ_FILES	=	$(addprefix $(BUILD_DIR)/, $(addsuffix .o, $(notdir $(basename $(SRC_FILES)))))
DEP_FILES	=	$(addprefix $(BUILD_DIR)/, $(addsuffix .d, $(notdir $(basename $(SRC_FILES)))))

.PHONY: clean fclean re all debug

$(NAME): $(OBJ_FILES) $(DEP_FILES) $(SRC_DIR)/arachnida.h
	$(CC) $(INC) $(CFLAGS) $(LFLAGS) $(OBJ_FILES) -o $(NAME)
	@echo "Built $(STYLE)$(basename $@)$(NOSTYLE)"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(INC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(BUILD_DIR)/

fclean: clean
	$(RM) $(NAME)*

re: fclean
	$(MAKE)

all: $(NAME)
