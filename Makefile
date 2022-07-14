# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmalesev <dmalesev@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/08 13:06:32 by dmalesev          #+#    #+#              #
#    Updated: 2022/07/13 18:15:18 by dmalesev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#COLORS
COLOR := $(shell printf "\e[38;2")
BACKGROUND_COLOR := $(shell printf "\e[48;2")
RESET := $(shell printf "\e[0m")
BOLD := $(shell printf "\e[1m")

#PRINTING TOOLS
ERASE_LINE = \033[K
MOVE = \033[
UP = A
DOWN = B
RIGHT = C
LEFT = D

#FLAGS AND CONFIGS
MAKEFLAGS += --no-print-directory
SHELL = /bin/bash

MAKE_COLOR = ;50;125;150m
NAME = RTv1
BINARY_NAME = $(NAME)
CC  = gcc
FLAGS = -Wall -Wextra -Werror -Wconversion -O3

UNAME = $(shell uname)
ifeq ($(UNAME), Darwin)
LIBS = -lmlx -framework AppKit -framework OpenGL $(LIBFT) $(DM_2D) $(DM_VECTORS)
endif
ifeq ($(UNAME), Linux)
LIBS = -O ./minilibx/libmlx_Linux.a -lXext -lX11 -lm $(LIBFT) $(DM_2D) $(DM_VECTORS)
endif

LIBRARIES_DIRECTORY = ./libraries/

DM_VECTORS_DIRECTORY = $(LIBRARIES_DIRECTORY)dm_vectors/
DM_VECTORS = $(DM_VECTORS_DIRECTORY)dm_vectors.a
DM_VECTORS_HEADERS = $(DM_VECTORS_DIRECTORY)includes/

DM_2D_DIRECTORY = $(LIBRARIES_DIRECTORY)dm_2d/
DM_2D = $(DM_2D_DIRECTORY)dm_2d.a
DM_2D_HEADERS = $(DM_2D_DIRECTORY)includes/

LIBFT_DIRECTORY = $(LIBRARIES_DIRECTORY)libft/
LIBFT = $(LIBFT_DIRECTORY)libft.a
LIBFT_HEADERS = $(LIBFT_DIRECTORY)includes/

HEADERS_DIRECTORY = ./includes/
HEADERS_LIST =	rtv1.h\
				mac_def.h\
				lnx_def.h
HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))

SOURCES_DIRECTORY = ./sources/
SOURCES_LIST =	rtv1.c\
				camera.c\
				init.c\
				help_funcs.c\
				keyboard.c\
				put_pixel.c\
				left_mouse.c\
				right_mouse.c\
				scroll_mouse.c\
				hooks.c\
				init_matrix.c\
				mouse.c\
				render_screen.c\
				transformations.c
SOURCES = $(addprefix $(SOURCES_DIRECTORY), $(SOURCES_LIST))
SOURCE_COUNT = $(words $(SOURCES_LIST))

OBJECTS_DIRECTORY = objects/
OBJECTS_LIST = $(patsubst %.c, %.o, $(SOURCES_LIST))
OBJECTS	= $(addprefix $(OBJECTS_DIRECTORY), $(OBJECTS_LIST))

INCLUDES = -I$(HEADERS_DIRECTORY) -I$(LIBFT_HEADERS) -I$(DM_2D_HEADERS) -I$(DM_VECTORS_HEADERS) -I./minilibx/

ASSERT_OBJECT = && printf "$(ERASE_LINE)" && printf "$@ $(COLOR)$(MAKE_COLOR)$(BOLD) ✓$(RESET)" || printf "$@ $(COLOR)$(MAKE_COLOR)$(BOLD)✘$(RESET)\n\n" | exit -1

ifneq ($(MAKECMDGOALS),progress_bar)
$(info Entering $(BOLD)$(COLOR)$(MAKE_COLOR)$(NAME) $(RESET)Makefile!)
endif

all: $(NAME)

$(NAME): $(LIBFT) $(DM_2D) $(DM_VECTORS) $(OBJECTS_DIRECTORY) $(OBJECTS)
	@$(CC) $(FLAGS) $(INCLUDES) $(OBJECTS) $(LIBS) -o $(NAME)
	@printf "$(NAME): $(COLOR)$(MAKE_COLOR)object files were created.$(RESET)\n"
	@printf "Compiled $(BOLD)$(COLOR)$(MAKE_COLOR)$(NAME)$(RESET)!\n\n"

$(OBJECTS_DIRECTORY):
	@mkdir -p $(OBJECTS_DIRECTORY)
	@printf "$(COLOR)$(MAKE_COLOR)__________________________________________________________________________________\n"
	@printf "$(NAME): $(COLOR)$(MAKE_COLOR)$(OBJECTS_DIRECTORY) directory was created.$(RESET)\n\n\n"

$(OBJECTS_DIRECTORY)%.o : $(SOURCES_DIRECTORY)%.c $(HEADERS)
	@printf "$(MOVE)2$(UP)"
	@$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@ $(ASSERT_OBJECT)
	@make progress_bar

$(LIBFT):
	@make -C $(LIBFT_DIRECTORY)

$(DM_VECTORS):
	@make -C $(DM_VECTORS_DIRECTORY)

$(DM_2D):
	@make -C $(DM_2D_DIRECTORY)

clean:
	@rm -rfv $(OBJECTS_DIRECTORY)
	@make -C $(LIBFT_DIRECTORY) clean
	@make -C $(DM_2D_DIRECTORY) clean
	@make -C $(DM_VECTORS_DIRECTORY) clean

fclean: clean
	@rm -fv $(NAME)
	@rm -fv $(LIBFT)
	@rm -fv $(DM_2D)
	@rm -fv $(DM_VECTORS)

re: fclean all

progress_bar:
	$(eval LOADED_COUNT = $(words $(wildcard $(OBJECTS_DIRECTORY)*.o)))
	@printf "\r$(MOVE)76$(RIGHT)Files compiled [$(BOLD)$(COLOR)$(MAKE_COLOR)$(LOADED_COUNT)$(RESET) / $(BOLD)$(COLOR)$(MAKE_COLOR)$(SOURCE_COUNT)$(RESET)]\n"
	@for ((i = 1; i <= 100; i++)) ; do\
		if ((i <= $(LOADED_COUNT) * 100 / $(SOURCE_COUNT))) ; then \
			printf "$(BACKGROUND_COLOR)$(MAKE_COLOR)$(COLOR);0;0;0m" ; \
		else \
			printf "$(BACKGROUND_COLOR);255;255;255m$(COLOR);0;0;0m" ; \
		fi ; \
		if ((i == 47 && $(LOADED_COUNT) * 100 / $(SOURCE_COUNT) >= 100)) ; then \
			printf "[$(RESET)" ; \
		elif ((i == 48 && $(LOADED_COUNT) * 100 / $(SOURCE_COUNT) >= 10 && $(LOADED_COUNT) * 100 / $(SOURCE_COUNT) < 100)) ; then \
			printf "[$(RESET)" ; \
		elif ((i == 49 && $(LOADED_COUNT) * 100 / $(SOURCE_COUNT) < 10)) ; then \
			printf "[$(RESET)" ; \
		elif ((i == 48 && $(LOADED_COUNT) * 100 / $(SOURCE_COUNT) >= 100)) ; then \
			printf "$$(($(LOADED_COUNT) * 100 / $(SOURCE_COUNT) / 100 % 10))$(RESET)" ; \
		elif ((i == 49 && $(LOADED_COUNT) * 100 / $(SOURCE_COUNT) >= 10)) ; then \
			printf "$$(($(LOADED_COUNT) * 100 / $(SOURCE_COUNT) / 10 % 10))$(RESET)" ; \
		elif ((i == 50)) ; then \
			printf "$$(($(LOADED_COUNT) * 100 / $(SOURCE_COUNT) % 10))$(RESET)" ; \
		elif ((i == 51)) ; then \
			printf "." ; \
		elif ((i == 52)) ; then \
			printf "$$(($(LOADED_COUNT) * 1000 / $(SOURCE_COUNT) % 10))$(RESET)" ; \
		elif ((i == 53)) ; then \
			printf "%%$(RESET)" ; \
		elif ((i == 54)) ; then \
			printf "]$(RESET)" ; \
		else \
			printf " $(RESET)"; \
		fi ; \
	done ;
	@printf "\n"

.PHONY: all clean fclean re
