# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ctelma <ctelma@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/26 14:45:43 by ctelma            #+#    #+#              #
#    Updated: 2019/12/29 15:57:26 by ctelma           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

CC = gcc
FLAGS = -Wall -Werror -Wextra
INCLUDES = -I$(HEADERS_DIRECTORY) -I$(LIBFT_HEADERS_DIRECTORY)

# LIBFT

LIBFT = $(LIBFT_DIRECTORY)libft.a
LIBFT_DIRECTORY = ../libft/

# LIBFT_HEADERS

LIBFT_HEADERS_LIST = \
	libft.h
LIBFT_HEADERS_DIRECTORY = $(LIBFT_DIRECTORY)inc/
LIBFT_HEADERS = $(addprefix $(LIBFT_HEADERS_DIRECTORY), $(LIBFT_HEADERS_LIST))

# LIBFT_SOURCES

LIBFT_SOURCES_DIRECTORY = $(LIBFT_DIRECTORY)src
LIBFT_SOURCES_LIST =\
	        ft_isprint.c ft_lstnew.c ft_memmove.c ft_putnbr_fd.c ft_strcpy.c \
            ft_strlcat.c ft_strnequ.c ft_strsub.c ft_atoi.c ft_itoa.c \
            ft_memalloc.c ft_memset.c ft_putstr.c ft_strdel.c ft_strlen.c \
            ft_strnew.c ft_strtrim.c ft_bzero.c ft_lstadd.c ft_memccpy.c \
            ft_putchar.c ft_putstr_fd.c ft_strdup.c ft_strmap.c ft_strnlen.c \
            ft_tolower.c ft_isalnum.c ft_lstdel.c ft_memchr.c ft_putchar_fd.c \
            ft_strcat.c ft_strequ.c ft_strmapi.c ft_strnstr.c ft_toupper.c \
            ft_isalpha.c ft_lstdelone.c ft_memcmp.c ft_putendl.c ft_strchr.c \
            ft_striter.c ft_strncat.c ft_strrchr.c ft_isascii.c ft_lstiter.c \
            ft_memcpy.c ft_putendl_fd.c ft_strclr.c ft_striteri.c ft_strncmp.c \
            ft_strsplit.c ft_isdigit.c ft_lstmap.c ft_memdel.c ft_putnbr.c \
            ft_strcmp.c ft_strjoin.c ft_strncpy.c ft_strstr.c ft_bzero_safe.c

LIBFT_SOURCES = $(addprefix $(LIBFT_SOURCES_DIRECTORY), $(LIBFT_SOURCES_LIST))

# LIBFT_OBJECTS

LIBFT_OBJECTS_DIRECTORY = $(LIBFT_DIRECTORY)obj/
LIBFT_OBJECTS_LIST = $(patsubst %.c, %.o, $(LIBFT_SOURCES_LIST))
LIBFT_OBJECTS = $(addprefix $(LIBFT_OBJECTS_DIRECTORY), $(LIBFT_OBJECTS_LIST))

# HEADERS

HEADERS_LIST = ft_printf.h

HEADERS_DIRECTORY = ./
HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))

# SOURCES

SOURCES_DIRECTORY = ./
SOURCES_LIST = ft_is_flag.c ft_printf.c ft_work_out.c long_math.c \
		work_out_char.c work_out_d.c work_out_uxo.c ft_strlen.c \
		str_longmath.c work_out_f.c ft_strnew.c


SOURCES = $(addprefix $(SOURCES_DIRECTORY), $(SOURCES_LIST))

# OBJECTS

OBJECTS_DIRECTORY = objects/
OBJECTS_LIST = $(patsubst %.c, %.o, $(SOURCES_LIST))
OBJECTS	= $(addprefix $(OBJECTS_DIRECTORY), $(OBJECTS_LIST))

# COLORS

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(LIBFT) $(LIBFT_OBJECTS) $(OBJECTS_DIRECTORY) $(OBJECTS)
	@ar rc $(NAME) $(OBJECTS) $(LIBFT_OBJECTS)
	@ranlib $(NAME)
	@echo "\n$(NAME): $(GREEN)object files were created$(RESET)"
	@echo "$(NAME): $(GREEN)$(NAME) was created$(RESET)"

$(OBJECTS_DIRECTORY):
	mkdir -p $(OBJECTS_DIRECTORY)
	@echo "$(NAME): $(GREEN)$(OBJECTS_DIRECTORY) was created$(RESET)"

$(OBJECTS_DIRECTORY)%.o : $(SOURCES_DIRECTORY)%.c $(HEADERS)
	$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@
	@echo "$(GREEN).$(RESET)\c"

$(LIBFT):
	@echo "$(NAME): $(GREEN)Creating $(LIBFT)...$(RESET)"
	@$(MAKE) -sC $(LIBFT_DIRECTORY)

clean:
	@$(MAKE) -sC $(LIBFT_DIRECTORY) clean
	@rm -rf $(OBJECTS_DIRECTORY)
	@echo "$(NAME): $(RED)$(OBJECTS_DIRECTORY) was deleted$(RESET)"
	@echo "$(NAME): $(RED)object files were deleted$(RESET)"

fclean: clean
	@rm -f $(LIBFT)
	@echo "$(NAME): $(RED)$(LIBFT) was deleted$(RESET)"
	@rm -f $(NAME)
	@echo "$(NAME): $(RED)$(NAME) was deleted$(RESET)"

re:
	@$(MAKE) fclean
	@$(MAKE) all
