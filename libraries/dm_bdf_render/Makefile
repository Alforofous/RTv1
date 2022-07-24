# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/03 09:10:41 by dmalesev          #+#    #+#              #
#    Updated: 2022/07/22 13:06:00 by dmalesev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#COLORS
COLOR := $(shell printf "\e[38;2")
BACKGROUND_COLOR := $(shell printf "\e[48;2")
RESET := $(shell printf "\e[0m")
BOLD := $(shell tput bold)

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

MAKE_COLOR = ;180;0;10m
PROJECT_NAME = dm_bdf_render
NAME = $(PROJECT_NAME).a
PRINT_NAME = $(BOLD)$(COLOR)$(MAKE_COLOR)$(PROJECT_NAME)$(RESET)
FLAGS = -Wall -Wextra -Werror -Wconversion
CC = gcc

HEADERS_DIRECTORY = ./includes/
HEADERS_LIST =	$(PROJECT_NAME).h
HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))

LIBFT_DIRECTORY = ../libft/
LIBFT = $(LIBFT_DIRECTORY)libft.a
LIBFT_HEADERS = $(LIBFT_DIRECTORY)includes/

SOURCES_DIRECTORY = ./sources/
SOURCES_LIST =	load_bdf_file.c\
				font_params_branch.c\
				font_properties_branch.c\
				font_glyphs_branch.c\
				font_bitmap_branch.c\
				print_font_info.c\
				render_glyph.c\
				render_str.c
SOURCES = $(addprefix $(SOURCES_DIRECTORY), $(SOURCES_LIST))
SOURCE_COUNT = $(words $(SOURCES_LIST))

OBJECTS_DIRECTORY = objects/
OBJECTS_LIST = $(patsubst %.c, %.o, $(SOURCES_LIST))
OBJECTS	= $(addprefix $(OBJECTS_DIRECTORY), $(OBJECTS_LIST))

INCLUDES = -I$(HEADERS_DIRECTORY) -I$(LIBFT_HEADERS)

ASSERT_OBJECT = && printf "$(ERASE_LINE)" && printf "$@ $(COLOR)$(MAKE_COLOR)$(BOLD) ✓$(RESET)" || printf "$@ $(COLOR)$(MAKE_COLOR)$(BOLD)✘$(RESET)\n\n"

ifneq ($(MAKECMDGOALS),progress_bar)
$(info Entering $(PRINT_NAME) Makefile!)
endif

all: $(NAME)

$(NAME): $(OBJECTS_DIRECTORY) $(OBJECTS)
	@ar rc $(NAME) $(OBJECTS)
	@ranlib $(NAME)
	@printf "Compiled $(BOLD)$(COLOR)$(MAKE_COLOR)$(NAME)$(RESET)!\n\n"

$(OBJECTS_DIRECTORY):
	@printf "$(COLOR)$(MAKE_COLOR)_________________________________________________________________\n"
	@printf "$(PRINT_NAME): Created $(OBJECTS_DIRECTORY) directory.\n\n\n"
	@mkdir -p $(OBJECTS_DIRECTORY)

$(OBJECTS_DIRECTORY)%.o : $(SOURCES_DIRECTORY)%.c $(HEADERS)
	@printf "$(MOVE)2$(UP)"
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@ $(ASSERT_OBJECT)
	@make progress_bar

clean:
	@rm -rf $(OBJECTS_DIRECTORY)
	@printf "$(PRINT_NAME): Deleted $(OBJECTS_DIRECTORY)*\n"

bclean:
	@rm -f $(NAME)
	@printf "$(PRINT_NAME): Deleted $(NAME)\n"

fclean: bclean clean

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
