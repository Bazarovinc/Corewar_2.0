/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctelma <ctelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 21:24:11 by ctelma            #+#    #+#             */
/*   Updated: 2020/09/21 11:39:09 by ctelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

static void	print_zjmp(t_cursor *cursor, int32_t addr)
{
	ft_printf("%s", cursor->player->color);
	ft_printf("cursor %4d of %10s executes:\t", cursor->id,
		cursor->player->name);
	ft_printf("zjmp %d %s\n", addr, (cursor->carry) ? "OK" : "FAILED");
	ft_printf("%s", NC);
}

void		op_zjmp(t_vm *vm, t_cursor *cursor)
{
	int32_t	addr;

	cursor->step += 1;
	addr = get_op_arg(vm, cursor, 1, true);
	if (cursor->carry)
	{
		cursor->pc = address_norming(cursor->pc + (addr % IDX_MOD));
		cursor->step = 0;
	}
	if (vm->stat_fl)
		print_zjmp(cursor, addr);
}
