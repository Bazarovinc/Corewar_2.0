/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctelma <ctelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 21:24:11 by ctelma            #+#    #+#             */
/*   Updated: 2020/07/23 13:51:15 by ctelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	print_zjmp(t_cursor *cursor, int32_t addr)
{
	ft_printf("%s", cursor->player->color);
	ft_printf("cursor of %10s executes operation: ", cursor->player->name);
	ft_printf("zjmp %d %s\n", addr, (cursor->carry) ? "OK" : "FAILED");
	ft_printf("%s", NC);
}

void				op_zjmp(t_vm *vm, t_cursor *cursor)
{
	int32_t addr;

	cursor->step += 1;
	addr = get_op_arg(vm, cursor, 1, true);
	if (cursor->carry)
	{
//		if (vm->vs)
//		clear_cursor(vm, cursor);
		cursor->pc = address_norming(cursor->pc + (addr % IDX_MOD));
//		if (vm->vs)
//			draw_cursor(vm, cursor);
		cursor->step = 0;
	}
	if (vm->stat_fl)
		print_zjmp(cursor, addr);
}
