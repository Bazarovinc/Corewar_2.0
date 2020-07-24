/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_machine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamaris <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 12:34:21 by ddamaris          #+#    #+#             */
/*   Updated: 2020/07/22 21:16:05 by ctelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		update_cursor(t_cursor *cursor)
{
	cursor->pc += cursor->step;
	cursor->pc = address_norming(cursor->pc);
	cursor->step = 0;
	ft_bzero(cursor->args_types, 3);
}

static int		check_args(t_cursor *cursor, t_op *op, t_vm *vm)
{
	int32_t		i;
	int32_t		step;
	int8_t		reg;

	i = 0;
	step = (op->args_types_code) ? 2 : 1;
	while (i < op->args_num)
	{
		if (!(cursor->args_types[i] & op->args_types[i]))
			return (0);
		if (cursor->args_types[i] == T_REG)
		{
			reg = vm->arena[cursor->pc + step];
			if (reg < 1 || reg > REG_NUMBER)
				return (0);
		}
		step += step_over_arg(cursor->args_types[i], op);
		i++;
	}
	return (1);
}

static void 	parse_args_types(t_cursor *cursor, t_op *op, t_vm *vm)
{
	int8_t		args_types_code;

	if (op->args_types_code)
	{
		args_types_code = vm->arena[cursor->pc + 1];
		if (op->args_num >= 1)
			cursor->args_types[0] = (args_types_code & 0xC0) >> 6;
		if (op->args_num >= 2)
			cursor->args_types[1] = (args_types_code & 0x30) >> 4;
		if (op->args_num >= 3)
			cursor->args_types[2] = (args_types_code & 0xC) >> 2;
	}
	else
		cursor->args_types[0] = op->args_types[0];
}

static void		do_operation(t_cursor *cursor, t_vm *vm)
{
	t_op *op;

	update_cycles_to_exec(cursor, vm);
	if (cursor->cycles_to_exec == 0)
	{
		cursor->op_code = vm->arena[cursor->pc];
		op = NULL;
		if (cursor->op_code >= 0x01 && cursor->op_code <= 0x10)
		{
			op = &op_tab[cursor->op_code - 1];
//			ft_printf("Operation %s\tCursor player name - %s\n", op->name, cursor->player->name);
			parse_args_types(cursor, op, vm);
			if (check_args(cursor, op, vm))
				op->func(vm, cursor);
			else
				cursor->step += calc_step(cursor, op);
		}
		else
			cursor->step = 1;
		update_cursor(cursor);
	}
}

void			run_vm(t_vm *vm)
{
	t_cursor	*cursor;

	while (vm->cursors_num)
	{
//		ft_printf("\n\t\tNumber of cycles %d\t\n\n", vm->cur_cycle);
		if (vm->dump_fl == vm->cur_cycle)
			print_dump(vm->arena, vm);
		cursor = vm->cursors;
		while (cursor)
		{
			do_operation(cursor, vm);
			cursor = cursor->next;
		}
		if (vm->cycles_to_die == vm->cycles_after_check
			|| vm->cycles_to_die <= 0)
			check_and_delete(vm);
		vm->cur_cycle++;
		vm->cycles_after_check++;
	}
//	if (vm->stat_fl)
//		ft_printf("\n\t\tNumber of cycles %d\t\n\n", vm->cur_cycle);
}
