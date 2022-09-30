# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmalesev <dmalesev@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/08 13:06:32 by dmalesev          #+#    #+#              #
#    Updated: 2022/09/30 14:29:35 by dmalesev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#COLORS
COLOR := $(shell printf "\e[38;2")
BACKGROUND_COLOR := $(shell printf "\e[48;2")
RESET := $(shell printf "\e[0m")
BOLD := $(shell printf "\e[1m")

#PRINTING TOOLS
ERASE_LINE = \e[K
MOVE = \e[
UP = A
DOWN = B
RIGHT = C
LEFT = D

#FLAGS AND CONFIGS
MAKEFLAGS += --no-print-directory
SHELL = /bin/bash

MAKE_COLOR = ;50;125;150m
PROJECT_NAME = RTv1
NAME = $(PROJECT_NAME)
PRINT_NAME = $(BOLD)$(COLOR)$(MAKE_COLOR)$(PROJECT_NAME)$(RESET)
CC  = gcc
OPTI_FLAGS = -O3 -flto
DEBUG_FLAGS = -g -fsanitize=address
FLAGS = -Wall -Wextra -Werror -Wconversion
FLAGS += $(DEBUG_FLAGS)
FLAGS += $(OPTI_FLAGS)

UNAME = $(shell uname)
ifeq ($(UNAME), Darwin)
LIBS = -lmlx -framework AppKit -framework OpenGL $(DM_BDF_RENDER) $(LIBFT) $(DM_2D) $(DM_VECTORS)
endif
ifeq ($(UNAME), Linux)
LIBS = -O ./minilibx/libmlx_Linux.a -lXext -lX11 -lm $(DM_BDF_RENDER) $(LIBFT) $(DM_2D) $(DM_VECTORS)
endif

LIBRARIES_DIRECTORY = ./libraries/

DM_BDF_RENDER_DIRECTORY = $(LIBRARIES_DIRECTORY)dm_bdf_render/
DM_BDF_RENDER = $(DM_BDF_RENDER_DIRECTORY)dm_bdf_render.a
DM_BDF_RENDER_HEADERS = $(DM_BDF_RENDER_DIRECTORY)includes/

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
				lnx_def.h\
				bitmask_keys.h
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
				transformations.c\
				intersect_cone.c\
				intersect_cylinder.c\
				add_obj_to_scene.c\
				change_obj_color.c\
				create_object.c\
				image0.c\
				image1.c\
				image2.c\
				image3.c\
				image4.c\
				image5.c\
				image6.c\
				image7.c\
				image8.c\
				draw_increment.c\
				draw_decrement.c\
				rgb_slider.c\
				display_strings.c\
				load_scene.c\
				read_object_info.c\
				create_images.c\
				delete_sel_object.c
SOURCES = $(addprefix $(SOURCES_DIRECTORY), $(SOURCES_LIST))
SOURCE_COUNT = $(words $(SOURCES_LIST))

OBJECTS_DIRECTORY = objects/
OBJECTS_LIST = $(patsubst %.c, %.o, $(SOURCES_LIST))
OBJECTS	= $(addprefix $(OBJECTS_DIRECTORY), $(OBJECTS_LIST))

INCLUDES = -I$(HEADERS_DIRECTORY) -I$(LIBFT_HEADERS) -I$(DM_2D_HEADERS) -I$(DM_VECTORS_HEADERS) -I$(DM_BDF_RENDER_HEADERS) -I./minilibx/

ASSERT_OBJECT = && printf "$(ERASE_LINE)" && printf "$@ $(COLOR)$(MAKE_COLOR)$(BOLD) ✓$(RESET)" || printf "$@ $(COLOR)$(MAKE_COLOR)$(BOLD)✘$(RESET)\n\n" | exit -1

ifneq ($(MAKECMDGOALS),progress_bar)
$(info Entering $(PRINT_NAME) Makefile!)
endif

all: $(NAME)

$(NAME): $(LIBFT) $(DM_2D) $(DM_VECTORS) $(DM_BDF_RENDER) $(OBJECTS_DIRECTORY) $(OBJECTS)
	@$(CC) $(FLAGS) $(INCLUDES) $(OBJECTS) $(LIBS) -o $(NAME)
	@printf "Compiled $(BOLD)$(COLOR)$(MAKE_COLOR)$(NAME)$(RESET)!\n\n"

$(OBJECTS_DIRECTORY):
	@mkdir -p $(OBJECTS_DIRECTORY)
	@printf "$(COLOR)$(MAKE_COLOR)__________________________________________________________________________________\n"
	@printf "$(PRINT_NAME): Created $(OBJECTS_DIRECTORY) directory.$(RESET)\n\n\n"

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

$(DM_BDF_RENDER):
	@make -C $(DM_BDF_RENDER_DIRECTORY)

clean:
	@rm -rf $(OBJECTS_DIRECTORY)
	@printf "$(PRINT_NAME): Deleted $(OBJECTS_DIRECTORY)*\n"
	@make -C $(LIBFT_DIRECTORY) clean
	@make -C $(DM_2D_DIRECTORY) clean
	@make -C $(DM_VECTORS_DIRECTORY) clean
	@make -C $(DM_BDF_RENDER_DIRECTORY) clean
	@printf "\n"

bclean:
	@rm -f $(NAME)
	@printf "$(PRINT_NAME): Deleted $(NAME)\n"

fclean: clean
	@make bclean
	@make -C $(LIBFT_DIRECTORY) bclean
	@make -C $(DM_2D_DIRECTORY) bclean
	@make -C $(DM_VECTORS_DIRECTORY) bclean
	@make -C $(DM_BDF_RENDER_DIRECTORY) bclean
	@printf "\n"

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
