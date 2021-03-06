/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazhni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 17:49:17 by ablizniu          #+#    #+#             */
/*   Updated: 2020/09/21 11:39:09 by ctelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

static void	print_fork(t_cursor *cursor, int32_t addr)
{
	ft_printf("%s", cursor->player->color);
	ft_printf("cursor %4d of %10s executes:\t", cursor->id,
		cursor->player->name);
	ft_printf("fork %d (%d)\n", addr, cursor->pc + addr % IDX_MOD);
	ft_printf("%s", NC);
}

void		op_fork(t_vm *vm, t_cursor *cursor)
{
	int32_t	addr;

	cursor->step += 1;
	addr = get_op_arg(vm, cursor, 1, true);
	duplicate_cursor(cursor, addr % IDX_MOD, vm);
	if (vm->stat_fl)
		print_fork(cursor, addr);
}
