# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ctelma <ctelma@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/24 18:19:09 by ctelma            #+#    #+#              #
#    Updated: 2020/09/22 22:17:47 by ctelma           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

VM_NAME = corewar
ASM_NAME = asm

CC = gcc
FLAGS = -Wall -Werror -Wextra
WROWFL = -lncurses

VM_LIB = -L $(FT_PRINTF_DIR) -lftprintf
VM_INC = -I$(HEADERS_DIR) \
			-I$(LIBFT_INC) \
			-I$(FT_PRINTF_INC)

LIBFT = $(LIBFT_DIR)libft.a
LIBFT_DIR = ./libft/
LIBFT_INC = $(LIBFT_DIR)inc/

FT_PRINTF = $(FT_PRINTF_DIR)libftprintf.a
FT_PRINTF_DIR = ./ft_printf/
FT_PRINTF_INC = $(FT_PRINTF_DIR)

HEADERS_DIR = ./includes/

VM_HEADERS_L = \
			op.h \
			vm.h 
VM_HEADERS = $(addprefix $(HEADERS_DIR), $(VM_HEADERS_L))

ASM_HEADERS_L = \
			asm.h \
			op.h
ASM_HEADERS = $(addprefix $(HEADERS_DIR), $(ASM_HEADERS_L))

VM_SRC_DIR = ./src_vm/
VM_SRC_LIST = check_to_die.c corewar.c free_vm.c ft_error.c \
			init_game.c parse_champion.c parser.c player.c \
			printing.c step.c utils1.c \
			virtual_machine.c \
			ft_drow.c ft_start_stop_drow.c ft_drow_staf.c \
			ft_color_select.c ft_vm_drow.c \
			ft_car.c ft_car_no.c ft_frame.c \
			ft_key.c ft_logo.c ft_win.c
VM_SRCS = $(addprefix $(VM_SRC_DIR), $(VM_SRC_LIST))

ASM_SRC_DIR = ./src_asm/
ASM_SRC_LIST = args_checker.c args_patterns.c asm.c \
			asm_parser.c byte_op.c check_name.c check_opname.c \
			converter.c errors.c ft_read_until_ch.c get_type.c \
			is_labelinst.c letter_check.c memory_hero.c memory_op.c \
			memory_vldop.c operations.c parse_inst.c read_arguments.c \
			translator.c ft_countch.c ft_strnewcp.c ft_str_white_trim.c \
			ft_strjoinchar.c dis_dec.c dis_get.c dis_mng.c dis_print.c \
			dis_type.c error_func.c
ASM_SRCS = $(addprefix $(ASM_SRC_DIR), $(ASM_SRC_LIST))

VM_OP_SRC_DIR = $(VM_SRC_DIR)operations/
VM_OP_SRC_LIST = op_add.c op_aff.c op_and.c op_fork.c op_ld.c op_ldi.c\
				op_lfork.c op_live.c op_lld.c op_lldi.c op_or.c op_st.c\
				op_sti.c op_sub.c op_xor.c op_zjmp.c op_utils.c
VM_OP_SRCS = $(addprefix $(VM_OP_SRC_DIR), $(VM_OP_SRC_LIST))

OBJS_DIR = ./objects/

VM_OBJS_DIR = $(OBJS_DIR)vm/
VM_OBJS_LIST = $(patsubst %.c, %.o, $(VM_SRC_LIST))
VM_OBJS	= $(addprefix $(VM_OBJS_DIR), $(VM_OBJS_LIST))

ASM_OBJS_DIR = $(OBJS_DIR)asm/
ASM_OBJS_LIST = $(patsubst %.c, %.o, $(ASM_SRC_LIST))
ASM_OBJS	= $(addprefix $(ASM_OBJS_DIR), $(ASM_OBJS_LIST))

VM_OP_OBJS_DIR = $(OBJS_DIR)operations/
VM_OP_OBJS_LIST = $(patsubst %.c, %.o, $(VM_OP_SRC_LIST))
VM_OP_OBJS	= $(addprefix $(VM_OP_OBJS_DIR), $(VM_OP_OBJS_LIST))

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

.PHONY: all clean fclean re

all: $(VM_NAME) $(ASM_NAME)

$(VM_NAME): $(FT_PRINTF) $(VM_OBJS_DIR) $(VM_OP_OBJS_DIR) $(VM_OBJS) $(VM_OP_OBJS)
	@$(CC) $(FLAGS) $(WROWFL) $(VM_LIB) $(VM_INC) $(VM_OBJS) $(VM_OP_OBJS) -o $(VM_NAME)
	@echo "\n$(VM_NAME): $(GREEN)object files were created$(RESET)"
	@echo "$(VM_NAME): $(GREEN)$(VM_NAME) was created$(RESET)"

$(ASM_NAME): $(FT_PRINTF) $(ASM_OBJS_DIR) $(ASM_OBJS)
	@$(CC) $(FLAGS) $(VM_LIB) $(VM_INC) $(ASM_OBJS) -o $(ASM_NAME)
	@echo "\n$(ASM_NAME): $(GREEN)object files were created$(RESET)"
	@echo "$(ASM_NAME): $(GREEN)$(ASM_NAME) was created$(RESET)"

$(ASM_OBJS_DIR):
	@mkdir -p $(ASM_OBJS_DIR)
	@echo "$(ASM_NAME): $(GREEN)$(ASM_OBJS_DIR) was created$(RESET)"

$(ASM_OBJS_DIR)%.o : $(ASM_SRC_DIR)%.c $(ASM_HEADERS)
	@$(CC) $(FLAGS) -c $(VM_INC) $< -o $@
	@echo "$(GREEN).$(RESET)\c"

$(VM_OBJS_DIR):
	@mkdir -p $(VM_OBJS_DIR)
	@echo "$(VM_NAME): $(GREEN)$(VM_OBJS_DIR) was created$(RESET)"

$(VM_OBJS_DIR)%.o : $(VM_SRC_DIR)%.c $(VM_HEADERS)
	@$(CC) $(FLAGS) -c $(VM_INC) $< -o $@
	@echo "$(GREEN).$(RESET)\c"

$(VM_OP_OBJS_DIR):
	@mkdir -p $(VM_OP_OBJS_DIR)
	@echo "$(VM_NAME): $(GREEN)$(VM_OP_OBJS_DIR) was created$(RESET)"

$(VM_OP_OBJS_DIR)%.o : $(VM_OP_SRC_DIR)%.c $(VM_HEADERS)
	@$(CC) $(FLAGS) -c $(VM_INC) $< -o $@
	@echo "$(GREEN).$(RESET)\c"

$(FT_PRINTF):
	@echo "$(VM_NAME): $(GREEN)Creating $(FT_PRINTF)...$(RESET)"
	@$(MAKE) -sC $(FT_PRINTF_DIR)

clean:
	@$(MAKE) -sC $(FT_PRINTF_DIR) clean
	@rm -rf $(OBJS_DIR)
	@echo "$(VM_NAME): $(RED)$(OBJS_DIR) was deleted$(RESET)"
	@echo "$(VM_NAME): $(RED)object files were deleted$(RESET)"
	@echo "$(ASM_NAME): $(RED)$(OBJS_DIR) was deleted$(RESET)"
	@echo "$(ASM_NAME): $(RED)object files were deleted$(RESET)"

fclean: clean
	@$(MAKE) -sC $(FT_PRINTF_DIR) fclean
	@echo "$(VM_NAME): $(RED)$(FT_PRINTF) was deleted$(RESET)"
	@rm -f $(VM_NAME)
	@echo "$(ASM_NAME): $(RED)$(ASM_NAME) was deleted$(RESET)"
	@rm -f $(ASM_NAME)
	@echo "$(ASM_NAME): $(RED)$(ASM_NAME) was deleted$(RESET)"

re:
	@$(MAKE) fclean
	@$(MAKE) all
