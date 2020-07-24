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

#include "vm.h"

static void	print_st(t_cursor *cursor, int32_t r_id, int32_t addr)
{
	ft_printf("%s", cursor->player->color);
	ft_printf("cursor of %10s executes operation: ", cursor->player->name);
	ft_printf("st r%d %d\n", r_id, addr);
	ft_printf("%s", NC);
}
/*
inline static void	vs_st(t_vm *vm, t_cursor *cursor, int32_t addr)
{
	if (vm->vs)
		update_map(vm, cursor, cursor->pc + (addr % IDX_MOD), DIR_SIZE);
}*/

void		op_st(t_vm *vm, t_cursor *cursor)
{
	int32_t	r_id;
	int32_t	r_value;
	int32_t	addr;

	cursor->step += 2;
	r_id = get_byte(vm, cursor->pc, cursor->step);
	cursor->step += 1;
	r_value = cursor->reg[r_id - 1];
	if (cursor->args_types[1] == T_REG)
	{
		cursor->reg[r_id - 1] = r_value;
		cursor->step += 1;
	}
	else
	{
		addr = bytecode_to_int32(vm->arena,
							cursor->pc + cursor->step, IND_SIZE);
		int32_to_bytecode(vm->arena, cursor->pc + (addr % IDX_MOD),
							r_value, DIR_SIZE);
//		vs_st(vm, cursor, addr);
		cursor->step += IND_SIZE;
	}
	if (vm->stat_fl)
		print_st(cursor, r_id, addr);
}
