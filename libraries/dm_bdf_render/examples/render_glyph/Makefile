# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/03 09:10:41 by dmalesev          #+#    #+#              #
#    Updated: 2022/07/22 11:34:40 by dmalesev         ###   ########.fr        #
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

MAKE_COLOR = ;230;50;50m
PROJECT_NAME = example
NAME = $(PROJECT_NAME)
PRINT_NAME = $(BOLD)$(COLOR)$(MAKE_COLOR)$(PROJECT_NAME)$(RESET)
FLAGS = -Wall -Wextra -Werror -Wconversion
CC = gcc

DM_BDF_RENDER_DIRECTORY = ../../
DM_BDF_RENDER = $(DM_BDF_RENDER_DIRECTORY)dm_bdf_render.a
DM_BDF_RENDER_HEADERS = $(DM_BDF_RENDER_DIRECTORY)includes/

LIBFT_DIRECTORY = ../../../libft/
LIBFT = $(LIBFT_DIRECTORY)libft.a
LIBFT_HEADERS = $(LIBFT_DIRECTORY)includes/

SOURCES_DIRECTORY = ./sources/
SOURCES_LIST =	example.c
SOURCES = $(addprefix $(SOURCES_DIRECTORY), $(SOURCES_LIST))
SOURCE_COUNT = $(words $(SOURCES_LIST))

OBJECTS_DIRECTORY = objects/
OBJECTS_LIST = $(patsubst %.c, %.o, $(SOURCES_LIST))
OBJECTS = $(addprefix $(OBJECTS_DIRECTORY), $(OBJECTS_LIST))

INCLUDES = -I$(DM_BDF_RENDER_HEADERS) -I$(LIBFT_HEADERS)
LIBS = $(DM_BDF_RENDER) $(LIBFT) 

ASSERT_OBJECT = && printf "$(ERASE_LINE)" && printf "$@ $(COLOR)$(MAKE_COLOR)$(BOLD) ✓$(RESET)" || printf "$@ $(COLOR)$(MAKE_COLOR)$(BOLD)✘$(RESET)\n\n"

ifneq ($(MAKECMDGOALS),progress_bar)
$(info Entering $(PRINT_NAME) Makefile!)
endif

all: $(NAME)

$(NAME): $(DM_BDF_RENDER) $(OBJECTS_DIRECTORY) $(OBJECTS)
	@$(CC) $(FLAGS) $(INCLUDES) $(OBJECTS) $(LIBS) -o $(NAME)
	@printf "Compiled $(BOLD)$(COLOR)$(MAKE_COLOR)$(NAME)$(RESET)!\n\n"

$(OBJECTS_DIRECTORY):
	@printf "$(COLOR)$(MAKE_COLOR)_________________________________________________________________\n"
	@printf "$(PRINT_NAME): Created $(OBJECTS_DIRECTORY) directory.\n\n\n"
	@mkdir -p $(OBJECTS_DIRECTORY)

$(OBJECTS_DIRECTORY)%.o : $(SOURCES_DIRECTORY)%.c $(HEADERS)
	@printf "$(MOVE)2$(UP)"
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@ $(ASSERT_OBJECT)
	@make progress_bar

$(DM_BDF_RENDER):
	@make -C $(DM_BDF_RENDER_DIRECTORY)

clean:
	@rm -rf $(OBJECTS_DIRECTORY)
	@printf "$(PRINT_NAME): Deleted $(OBJECTS_DIRECTORY)*\n"
	@make -C $(DM_BDF_RENDER_DIRECTORY) clean
	@printf "\n"

bclean:
	@rm -f $(NAME)
	@printf "$(PRINT_NAME): Deleted $(NAME)\n"

fclean: clean
	@make bclean
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
