/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctelma <ctelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 21:23:35 by ctelma            #+#    #+#             */
/*   Updated: 2020/07/23 13:51:15 by ctelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

static void	print_st(t_cursor *cursor, int32_t r_id, int32_t addr)
{
	ft_printf("%s", cursor->player->color);
	ft_printf("cursor %4d of %10s executes:\t", cursor->id,
		cursor->player->name);
	ft_printf("st r%d r%d\n", r_id, addr);
	ft_printf("%s", NC);
}

static void	arg_ind_st(t_cursor *cursor, int32_t value, int32_t r_id, t_vm *vm)
{
	int32_t	addr;

	addr = bytecode_to_int32(vm->arena,
			cursor->pc + cursor->step, IND_SIZE);
	int32_to_bytecode(vm->arena, cursor->pc + (addr % IDX_MOD),
					  value, DIR_SIZE);
	if (vm->stat_fl)
	{
		ft_printf("%s", cursor->player->color);
		ft_printf("cursor %4d of %10s executes:\t", cursor->id,
				  cursor->player->name);
		ft_printf("st r%d %d\n", r_id, addr);
		ft_printf("%s", NC);
	}
	cursor->step += IND_SIZE;
}

void		op_st(t_vm *vm, t_cursor *cursor)
{
	int32_t	r_id;
	int32_t	value;
	int32_t	addr;

	cursor->step += 2;
	r_id = get_byte(vm, cursor->pc, cursor->step);
	cursor->step += 1;
	value = cursor->reg[r_id - 1];
	if (cursor->args_types[1] == REG_CODE)
	{
		addr = get_byte(vm, cursor->pc, cursor->step);
		cursor->reg[addr - 1] = value;
		cursor->step += 1;
		if (vm->stat_fl)
			print_st(cursor, r_id, addr);
	}
	else
		arg_ind_st(cursor, value, r_id, vm);
}
