# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmalesev <dmalesev@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/08 13:06:32 by dmalesev          #+#    #+#              #
#    Updated: 2022/07/11 12:32:02 by dmalesev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#COLORS
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
VIOLET = \033[35m
CYAN = \033[36m
GRAY = \033[37m
RED = \033[31m
BLACK = \033[30m
WHITE = \033[37m
BLUE_BACKGROUND = \033[44m
GRAY_BACKGROUND = \033[47m
GREEN_BACKGROUND = \033[42m
WHITE_BACKGROUND = \033[47m
VIOLET_BACKGROUND = \033[45m
YELLOW_BACKGROUND = \033[43m
BOLD = \033[1m
RESET = \033[0m

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

NAME = RTv1
CC  = gcc
FLAGS = -Wall -Wextra -Werror -Wconversion

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

ASSERT_OBJECT = && printf "$(ERASE_LINE)" && printf "$@ $(BLUE)$(BOLD) ✔$(RESET)" || printf "$@ $(BLUE)$(BOLD)✘$(RESET)\n\n"

all: $(NAME)

$(NAME): $(LIBFT) $(DM_2D) $(DM_VECTORS) $(OBJECTS_DIRECTORY) $(OBJECTS)
	@$(CC) $(FLAGS) $(INCLUDES) $(OBJECTS) $(LIBS) -o $(NAME)
	@printf "$(NAME): $(BLUE)object files were created.$(RESET)\n"
	@printf "Compiled $(BOLD)$(BLUE)$(NAME)$(RESET)!\n\n"

$(OBJECTS_DIRECTORY):
	@mkdir -p $(OBJECTS_DIRECTORY)
	@printf "$(BLUE)__________________________________________________________________________________\n"
	@printf "$(NAME): $(BLUE)$(OBJECTS_DIRECTORY) directory was created.$(RESET)\n\n\n"

$(OBJECTS_DIRECTORY)%.o : $(SOURCES_DIRECTORY)%.c $(HEADERS)
	@$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@ $(ASSERT_OBJECT)
	@printf "$(MOVE)2$(UP)"
	@make pbar

$(LIBFT):
	@make -C $(LIBFT_DIRECTORY)

$(DM_VECTORS):
	@make -C $(DM_VECTORS_DIRECTORY)

$(DM_2D):
	@make -C $(DM_2D_DIRECTORY)

clean:
	@make -C $(LIBFT_DIRECTORY) clean
	@make -C $(DM_2D_DIRECTORY) clean
	@make -C $(DM_VECTORS_DIRECTORY) clean
	@rm -rf $(OBJECTS_DIRECTORY)
	@printf "$(NAME): $(RED)$(OBJECTS_DIRECTORY) directory was deleted.$(RESET)\n"
	@printf "$(NAME): $(RED)object files were deleted.$(RESET)\n"

fclean: clean
	@rm -f $(LIBFT)
	@printf "$(NAME): $(RED)$(LIBFT) was deleted.$(RESET)\n"
	@rm -f $(DM_2D)
	@printf "$(NAME): $(RED)$(DM_2D) was deleted.$(RESET)\n"
	@rm -f $(DM_VECTORS)
	@printf "$(NAME): $(RED)$(DM_VECTORS) was deleted.$(RESET)\n"
	@rm -f $(NAME)
	@printf "$(NAME): $(RED)$(NAME) was deleted.$(RESET)\n"

re: fclean all

pbar:
	$(eval LOADED_COUNT = $(words $(wildcard $(OBJECTS_DIRECTORY)*.o)))
	@printf "\r$(MOVE)76$(RIGHT)Files compiled [$(BOLD)$(BLUE)$(LOADED_COUNT)$(RESET) / $(BOLD)$(BLUE)$(SOURCE_COUNT)$(RESET)]\n"
	@for ((i = 1; i <= 100; i++)) ; do\
		if ((i <= $(LOADED_COUNT) * 100 / $(SOURCE_COUNT))) ; then \
			printf "$(BLUE_BACKGROUND)$(BOLD)$(WHITE)" ; \
		else \
			printf "$(WHITE_BACKGROUND)$(BOLD)$(BLACK)" ; \
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

.PHONY: all clean fclean re internal-target external-target

external-target:
	bash -c "trap 'trap - SIGINT SIGTERM ERR; printf "TEST FOR EXIT\n\n\n"; exit 1' SIGINT SIGTERM ERR; $(MAKE) internal-target"

internal-target:
	echo "doing stuff here"
