/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctelma <ctelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 21:24:00 by ctelma            #+#    #+#             */
/*   Updated: 2020/07/23 13:51:15 by ctelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int32_t		bytecode_to_int32(u_int8_t *arena, int32_t addr, int32_t size)
{
	int32_t	res;
	int32_t	address;
	char	sign;
	int		i;

	res = 0;
	sign = (char)(arena[address_norming(addr)] & 0x80);
	i = 0;
	while (size)
	{
		address = address_norming(addr + size - 1);
		if (sign)
			res += (arena[address] ^ 0xFF) << (i++ * 8);
		else
			res += arena[address] << (i++ * 8);
		size--;
	}
	if (sign)
		res = ~(res);
	return (res);
}

void		int32_to_bytecode(u_int8_t *arena, int32_t addr, int32_t value,
						int32_t size)
{
	int8_t	i;
	int32_t	address;

	i = 0;
	while (size)
	{
		address = address_norming(addr + size - 1);
		arena[address] = (u_int8_t)((value >> i) & 0xFF);
		i += 8;
		size--;
	}
}

int32_t		get_op_arg(t_vm *vm, t_cursor *cursor, u_int8_t index, char mod)
{
	t_op		*op;
	int32_t		value;
	int32_t		addr;

	op = &op_tab[cursor->op_code - 1];
	value = 0;
	if (cursor->args_types[index - 1] == T_REG)
		value = cursor->reg[get_byte(vm, cursor->pc, cursor->step) - 1];
	else if (cursor->args_types[index - 1] == T_DIR)
		value = bytecode_to_int32(vm->arena,
					cursor->pc + cursor->step, op->t_dir_size);
	else if (cursor->args_types[index - 1] == T_IND)
	{
		addr = bytecode_to_int32(vm->arena,
					cursor->pc + cursor->step, IND_SIZE);
		value = bytecode_to_int32(vm->arena,
					cursor->pc + (mod ? (addr % IDX_MOD) : addr),	DIR_SIZE);
	}
	cursor->step += step_over_arg(cursor->args_types[index - 1], op);
	return (value);
}

void	duplicate_cursor(t_cursor *cursor, int32_t addr, t_vm *vm)
{
	int			i;

	addr = address_norming(cursor->pc + addr);
	add_cursor(cursor->player, addr, vm);
	i = 0;
	while (i < REG_NUMBER)
	{
		vm->cursors->reg[i] = cursor->reg[i];
		i++;
	}
	vm->cursors->carry = cursor->carry;
	vm->cursors->last_live_cycle = cursor->last_live_cycle;
}

/*void		update_map(t_vm *vm, t_cursor *cursor, int32_t addr, int32_t size)
{
	int32_t value;

	value = ((cursor->player->id - 1) % MAX_PLAYER_ID) + 1;
	while (size)
	{
		vm->vs->map[calc_addr(addr + size - 1)].index = value;
		vm->vs->map[calc_addr(addr
								+ size - 1)].wait_cycles_store = CYCLE_TO_WAIT;
		size--;
	}
}*/
