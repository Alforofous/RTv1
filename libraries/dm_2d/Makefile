# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/03 09:10:41 by dmalesev          #+#    #+#              #
#    Updated: 2022/07/06 11:43:40 by dmalesev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#COLORS
BLUE = \033[34m
GREEN = \033[32m
YELLOW = \033[33m
GRAY = \033[37m
VIOLET = \033[35m
RED = \033[31m
BLACK = \033[30m
WHITE = \033[37m
CYAN = \033[36m
CYAN_BACKGROUND = \033[46m
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

NAME = dm_2d.a
FLAGS = -Wall -Wextra -Werror -Wconversion
CC = gcc

HEADERS_DIRECTORY = ./includes/
HEADERS_LIST =	dm_2d.h\
HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))

SOURCES_DIRECTORY = ./sources/
SOURCES_LIST =	draw_line.c\
				draw_circle.c\
				draw_square.c\
				draw_rect.c\
				draw_quadril.c\
				draw_rectf.c\
				draw_trif.c\
				color_mix.c\
				combine_rgb.c\
				seperate_rgb.c\
				abs.c
SOURCES = $(addprefix $(SOURCES_DIRECTORY), $(SOURCES_LIST))
SOURCE_COUNT = $(words $(SOURCES_LIST))

OBJECTS_DIRECTORY = objects/
OBJECTS_LIST = $(patsubst %.c, %.o, $(SOURCES_LIST))
OBJECTS	= $(addprefix $(OBJECTS_DIRECTORY), $(OBJECTS_LIST))

INCLUDES = $(HEADERS_DIRECTORY)

ASSERT_OBJECT = && printf "$(ERASE_LINE)" && printf "$@ $(CYAN)$(BOLD) ✔$(RESET)" || printf "$@ $(CYAN)$(BOLD)✘$(RESET)\n\n"

all: $(NAME)

$(NAME): $(OBJECTS_DIRECTORY) $(OBJECTS)
	@ar rc $(NAME) $(OBJECTS)
	@ranlib $(NAME)
	@printf "$(NAME): $(CYAN)object files were created.$(RESET)\n"
	@printf "Compiled $(BOLD)$(CYAN)$(NAME)$(RESET)!\n\n"

$(OBJECTS_DIRECTORY):
	@mkdir -p $(OBJECTS_DIRECTORY)
	@printf "$(CYAN)_________________________________________________________________\n"
	@printf "$(NAME): $(CYAN)$(OBJECTS_DIRECTORY) directory was created.$(RESET)\n\n\n"

$(OBJECTS_DIRECTORY)%.o : $(SOURCES_DIRECTORY)%.c $(HEADERS)
	@printf "$(MOVE)2$(UP)"
	@$(CC) $(FLAGS) -c -I$(INCLUDES) $< -o $@ $(ASSERT_OBJECT)
	@make pbar

clean:
	@rm -rf $(OBJECTS_DIRECTORY)
	@printf "$(NAME): $(RED)$(OBJECTS_DIRECTORY) directory was deleted.$(RESET)\n"
	@printf "$(NAME): $(RED)object files were deleted.$(RESET)\n"

fclean: clean
	@rm -f $(NAME)
	@printf "$(NAME): $(RED)$(NAME) was deleted.$(RESET)\n"

re: fclean all

pbar:
	$(eval LOADED_COUNT = $(words $(wildcard $(OBJECTS_DIRECTORY)*.o)))
	@printf "\r$(MOVE)76$(RIGHT)Files compiled [$(BOLD)$(CYAN)$(LOADED_COUNT)$(RESET) / $(BOLD)$(CYAN)$(SOURCE_COUNT)$(RESET)]\n"
	@for ((i = 1; i <= 100; i++)) ; do\
		if ((i <= $(LOADED_COUNT) * 100 / $(SOURCE_COUNT))) ; then \
			printf "$(CYAN_BACKGROUND)$(BOLD)$(BLACK)" ; \
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

.PHONY: all clean fclean re
