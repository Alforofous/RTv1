# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmalesev <dmalesev@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/08 13:06:32 by dmalesev          #+#    #+#              #
#    Updated: 2022/06/17 17:13:46 by dmalesev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#COLORS
GREEN = \033[32m
YELLOW = \033[33m
VIOLET = \033[0;35m
RESET = \033[0m
RED = \033[31m
CYAN = \033[36m
BOLD = \033[1m

NAME =		RTv1
CC =		gcc
FLAGS =		-Wall -Wextra -Werror -Wconversion
LNX_FLAGS = -Wall -Wextra -Werror -Wconversion

UNAME = $(shell uname)
ifeq ($(UNAME), Darwin)
LIBS =	-lmlx -framework AppKit -framework OpenGL $(LIBFT) $(DM_2D) $(DM_VECTORS)
endif
ifeq ($(UNAME), Linux)
LIBS =	-O -lmlx_Linux -lXext -lX11 -lm $(LIBFT) $(DM_2D) $(DM_VECTORS)
endif

DM_VECTORS_DIRECTORY = ./dm_vectors/
DM_VECTORS = $(DM_VECTORS_DIRECTORY)dm_vectors.a
DM_VECTORS_HEADERS = $(DM_VECTORS_DIRECTORY)includes/

DM_2D_DIRECTORY = ./dm_2d/
DM_2D = $(DM_2D_DIRECTORY)dm_2d.a
DM_2D_HEADERS = $(DM_2D_DIRECTORY)includes/

LIBFT_DIRECTORY = ./libft/
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
				load_obj.c\
				obj_params.c\
				put_pixel.c\
				left_mouse.c\
				right_mouse.c\
				scroll_mouse.c\
				hooks.c\
				init_matrix.c\
				mouse.c\
				plot_obj.c\
				render_screen.c\
				transformations.c
SOURCES = $(addprefix $(SOURCES_DIRECTORY), $(SOURCES_LIST))

OBJECTS_DIRECTORY = objects/
OBJECTS_LIST = $(patsubst %.c, %.o, $(SOURCES_LIST))
OBJECTS	= $(addprefix $(OBJECTS_DIRECTORY), $(OBJECTS_LIST))

INCLUDES = -I$(HEADERS_DIRECTORY) -I$(LIBFT_HEADERS) -I$(DM_2D_HEADERS) -I$(DM_VECTORS_HEADERS) -I./minilibx/


ASSERT_OBJECT = && echo "$@ $(YELLOW)$(BOLD) ✔$(RESET)" || echo "$@ $(RED)$(BOLD)✘$(RESET)"

all: $(NAME)

$(NAME): $(LIBFT) $(DM_2D) $(DM_VECTORS) $(OBJECTS_DIRECTORY) $(OBJECTS)
	@$(CC) $(FLAGS) $(LIBS) $(INCLUDES) $(OBJECTS) -o $(NAME)
	@echo "Compiled $(BOLD)$(NAME)$(RESET)!\n"

$(OBJECTS_DIRECTORY):
	@mkdir -p $(OBJECTS_DIRECTORY)
	@echo "$(NAME): $(YELLOW)$(OBJECTS_DIRECTORY) was created$(RESET)"

$(OBJECTS_DIRECTORY)%.o : $(SOURCES_DIRECTORY)%.c $(HEADERS)
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@ $(ASSERT_OBJECT)

$(LIBFT):
	@echo "$(NAME): $(GREEN)Creating $(LIBFT)...$(RESET)"
	@make -C $(LIBFT_DIRECTORY)

$(DM_VECTORS):
	@echo "$(NAME): $(VIOLET)Creating $(DM_VECTORS)...$(RESET)"
	@make -C $(DM_VECTORS_DIRECTORY)

$(DM_2D):
	@echo "$(NAME): $(CYAN)Creating $(DM_2D)...$(RESET)"
	@make -C $(DM_2D_DIRECTORY)

clean:
	@make -C $(LIBFT_DIRECTORY) clean
	@make -C $(DM_2D_DIRECTORY) clean
	@make -C $(DM_VECTORS_DIRECTORY) clean
	@rm -rf $(OBJECTS_DIRECTORY)
	@echo "$(NAME): $(RED)$(OBJECTS_DIRECTORY) was deleted$(RESET)"
	@echo "$(NAME): $(RED)object files were deleted$(RESET)\n"

fclean: clean
	@rm -f $(LIBFT)
	@echo "$(NAME): $(RED)$(LIBFT) was deleted$(RESET)"
	@rm -f $(DM_2D)
	@echo "$(NAME): $(RED)$(DM_2D) was deleted$(RESET)\n"
	@rm -f $(DM_VECTORS)
	@echo "$(NAME): $(RED)$(DM_VECTORS) was deleted$(RESET)\n"
	@rm -f $(NAME)
	@echo "$(NAME): $(RED)$(NAME) was deleted$(RESET)\n"

re:
	@make fclean
	@make all

.PHONY: all clean fclean re
