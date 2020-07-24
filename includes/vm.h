/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctelma <ctelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 19:15:32 by ctelma            #+#    #+#             */
/*   Updated: 2020/07/23 13:51:15 by ctelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef VM_H
# define VM_H

# include "../libft/inc/libft.h"
# include "../ft_printf/ft_printf.h"
# include <stdbool.h>
# include <stdlib.h>
# include "op.h"
# include <fcntl.h>

# define INDEX(X)		((X) - 1)
# define FT_ABS(X) (((X) < 0) ? (-(X)) : (X))

# define OP_CODE_LEN	1
# define ARGS_CODE_LEN	1
# define REG_LEN		1

# define LIVE_LOG			1
# define CYCLE_LOG			2
# define OP_LOG				4
# define DEATH_LOG			8
# define PC_MOVEMENT_LOG	16

/*
typedef enum
{
	True,
	False
}	t_bool;
*/
typedef struct			s_player
{
	int					id;
	unsigned char		*name;
	unsigned char		*comment;
	char				*color;
	size_t				code_size;
	unsigned char		*code;
	size_t				last_live_cycle;
	size_t				curr_lives_num;
	size_t				prev_lives_num;
	int32_t				pc;
	struct s_player		*next;
}						t_player;
/*
static int8_t			arg_code[3] = {
		T_REG,
		T_DIR,
		T_IND
};
*/
typedef struct			s_cursor
{
	int					carry;
	unsigned char		op_code;
	size_t				last_live_cycle;
	unsigned int		cycles_to_exec;
	unsigned char		args_types[3];
	int32_t				pc;
	unsigned int		step;
	int32_t				reg[REG_NUMBER];
	t_player			*player;
	struct s_cursor		*next;
}						t_cursor;

typedef struct			s_vm
{
	u_int8_t			arena[MEM_SIZE];
	t_player			*players[MAX_PLAYERS];
	int					players_num;
	t_player			*last_alive;
	t_cursor			*cursors;
	size_t				cursors_num;
	size_t				lives_num;
	size_t				cur_cycle;
	int					cycles_to_die;
	size_t				cycles_after_check;
	size_t				checks_num;
	int 				vis_fl;
	int 				stat_fl;
	int 				alive_fl;
	size_t 				dump_fl;
	int					aff_fl;
}						t_vm;

typedef struct			s_op
{
	char				*name;
	int8_t				code;
	int8_t				args_num;
	int8_t				args_types_code;
	int8_t				args_types[3];
	char				modify_carry;
	int8_t				t_dir_size;
	unsigned int		cycles;
	void				(*func)(t_vm *, t_cursor *);
}						t_op;


void					print_introducing(t_vm *vm);
void					print_usage(t_vm *vm);
//void					print_error(char *error, t_vm *vm);
void					print_dump(u_int8_t *arena, t_vm *vm);
void					print_winner(t_vm *vm);
int						file_is_cor(char *str, t_vm *vm);
void					parser(t_vm *vm, char **argv);
int						ft_strtoint(char *str);
void					parse_champion(int fd, t_player *player, t_vm *vm);
unsigned char			*read_str(int fd, size_t len, t_vm *vm);
void					*add_player(char *filename, int id, t_vm *vm);
void					init_cursors(t_vm *vm);
void					init_arena(t_vm *vm);
void					init_cursor(t_player *player, t_cursor *cursor,
							int32_t pc);
void					update_cycles_to_exec(t_cursor *cursor, t_vm *vm);
void					add_cursor(t_player *player, int32_t pc, t_vm *vm);
void					run_vm(t_vm *vm);
int						step_over_arg(int8_t arg_type, t_op *op);
int32_t					calc_step(t_cursor *cursor, t_op *op);
int32_t					address_norming(int32_t addr);
void					check_and_delete(t_vm *vm);
int8_t					get_byte(t_vm *vm, int32_t pc, int32_t step);
void					free_vm(t_vm *vm);
void					error_func(char *clr, char *str, t_vm *vm);

/*
** Operations
*/
int32_t		            bytecode_to_int32(u_int8_t *arena, int32_t addr,
							int32_t size);
void					int32_to_bytecode(u_int8_t *arena, int32_t addr,
							int32_t value, int32_t size);
int32_t                 get_op_arg(t_vm *vm, t_cursor *cursor,
							u_int8_t index, char mod);
void					duplicate_cursor(t_cursor *cursor, int32_t addr,
											t_vm *vm);
void					op_live(t_vm *vm, t_cursor *cursor);
void                    op_add(t_vm *vm, t_cursor *cursor);
void                    op_aff(t_vm *vm, t_cursor *cursor);
void					op_and(t_vm *vm, t_cursor *cursor);
void					op_ldi(t_vm *vm, t_cursor *cursor);
void                    op_ld(t_vm *vm, t_cursor *cursor);
void                    op_fork(t_vm *vm, t_cursor *cursor);
void					op_lfork(t_vm *vm, t_cursor *cursor);
void					op_lld(t_vm *vm, t_cursor *cursor);
void					op_lldi(t_vm *vm, t_cursor *cursor);
void					op_or(t_vm *vm, t_cursor *cursor);
void					op_st(t_vm *vm, t_cursor *cursor);
void					op_sti(t_vm *vm, t_cursor *cursor);
void					op_sub(t_vm *vm, t_cursor *cursor);
void					op_xor(t_vm *vm, t_cursor *cursor);
void					op_zjmp(t_vm *vm, t_cursor *cursor);

static t_op				op_tab[16] = {
		{
				.name = "live",
				.code = 0x01,
				.args_num = 1,
				.args_types_code = 0,
				.args_types = {T_DIR, 0, 0},
				.modify_carry = false,
				.t_dir_size = 4,
				.cycles = 10,
				.func = &op_live
		},
		{
				.name = "ld",
				.code = 0x02,
				.args_num = 2,
				.args_types_code = 1,
				.args_types = {T_DIR | T_IND, T_REG, 0},
				.modify_carry = true,
				.t_dir_size = 4,
				.cycles = 5,
				.func = &op_ld

		},
		{
				.name = "st",
				.code = 0x03,
				.args_num = 2,
				.args_types_code = 1,
				.args_types = {T_REG, T_REG | T_IND, 0},
				.modify_carry = false,
				.t_dir_size = 4,
				.cycles = 5,
				.func = &op_st
		},
		{
				.name = "add",
				.code = 0x04,
				.args_num = 3,
				.args_types_code = 1,
				.args_types = {T_REG, T_REG, T_REG},
				.modify_carry = true,
				.t_dir_size = 4,
				.cycles = 10,
				.func = &op_add
		},
		{
				.name = "sub",
				.code = 0x05,
				.args_num = 3,
				.args_types_code = 1,
				.args_types = {T_REG, T_REG, T_REG},
				.modify_carry = true,
				.t_dir_size = 4,
				.cycles = 10,
				.func = &op_sub
		},
		{
				.name = "and",
				.code = 0x06,
				.args_num = 3,
				.args_types_code = 1,
				.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
				.modify_carry = true,
				.t_dir_size = 4,
				.cycles = 6,
				.func = &op_and
		},
		{
				.name = "or",
				.code = 0x07,
				.args_num = 3,
				.args_types_code = 1,
				.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
				.modify_carry = true,
				.t_dir_size = 4,
				.cycles = 6,
				.func = &op_or
		},
		{
				.name = "xor",
				.code = 0x08,
				.args_num = 3,
				.args_types_code = 1,
				.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
				.modify_carry = true,
				.t_dir_size = 4,
				.cycles = 6,
				.func = &op_xor
		},
		{
				.name = "zjmp",
				.code = 0x09,
				.args_num = 1,
				.args_types_code = 0,
				.args_types = {T_DIR, 0, 0},
				.modify_carry = false,
				.t_dir_size = 2,
				.cycles = 20,
				.func = &op_zjmp
		},
		{
				.name = "ldi",
				.code = 0x0A,
				.args_num = 3,
				.args_types_code = 1,
				.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG},
				.modify_carry = false,
				.t_dir_size = 2,
				.cycles = 25,
				.func = &op_ldi
		},
		{
				.name = "sti",
				.code = 0x0B,
				.args_num = 3,
				.args_types_code = 1,
				.args_types = {T_REG, T_REG | T_DIR | T_IND, T_REG | T_DIR},
				.modify_carry = false,
				.t_dir_size = 2,
				.cycles = 25,
				.func = &op_sti
		},
		{
				.name = "fork",
				.code = 0x0C,
				.args_num = 1,
				.args_types_code = 0,
				.args_types = {T_DIR, 0, 0},
				.modify_carry = false,
				.t_dir_size = 2,
				.cycles = 800,
				.func = &op_fork
		},
		{
				.name = "lld",
				.code = 0x0D,
				.args_num = 2,
				.args_types_code = 1,
				.args_types = {T_DIR | T_IND, T_REG, 0},
				.modify_carry = true,
				.t_dir_size = 4,
				.cycles = 10,
				.func = &op_lld
		},
		{
				.name = "lldi",
				.code = 0x0E,
				.args_num = 3,
				.args_types_code = 1,
				.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG},
				.modify_carry = true,
				.t_dir_size = 2,
				.cycles = 50,
				.func = &op_lldi
		},
		{
				.name = "lfork",
				.code = 0x0F,
				.args_num = 1,
				.args_types_code = 0,
				.args_types = {T_DIR, 0, 0},
				.modify_carry = false,
				.t_dir_size = 2,
				.cycles = 1000,
				.func = &op_lfork
		},
		{
				.name = "aff",
				.code = 0x10,
				.args_num = 1,
				.args_types_code = 1,
				.args_types = {T_REG, 0, 0},
				.modify_carry = false,
				.t_dir_size = 4,
				.cycles = 2,
				.func = &op_aff
		}
};

#endif
