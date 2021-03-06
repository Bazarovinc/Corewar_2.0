/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lfork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctelma <ctelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 21:23:05 by ctelma            #+#    #+#             */
/*   Updated: 2020/09/21 11:39:09 by ctelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

static void	print_lfork(t_cursor *cursor, int32_t addr)
{
	ft_printf("%s", cursor->player->color);
	ft_printf("cursor %4d of %10s executes:\t", cursor->id,
		cursor->player->name);
	ft_printf("lfork %d (%d)\n", addr, cursor->pc + addr);
	ft_printf("%s", NC);
}

void		op_lfork(t_vm *vm, t_cursor *cursor)
{
	int32_t	addr;

	cursor->step += 1;
	addr = get_op_arg(vm, cursor, 1, true);
	duplicate_cursor(cursor, addr, vm);
	if (vm->stat_fl)
		print_lfork(cursor, addr);
}
