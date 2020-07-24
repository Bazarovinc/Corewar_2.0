/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazhni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 17:49:17 by ablizniu          #+#    #+#             */
/*   Updated: 2020/07/23 13:51:15 by ctelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	print_fork(t_cursor *cursor, int32_t addr)
{
	ft_printf("%s", cursor->player->color);
	ft_printf("cursor of %10s executes operation: fork ", cursor->player->name);
	ft_printf("%d (%d)\n", addr,	cursor->pc + addr % IDX_MOD);
	ft_printf("%s", NC);
}

void				op_fork(t_vm *vm, t_cursor *cursor)
{
	int32_t		addr;
	//t_cursor	*new;

	cursor->step += 1;
	addr = get_op_arg(vm, cursor, 1, true);
	duplicate_cursor(cursor, addr % IDX_MOD, vm);
	if (vm->stat_fl)
		print_fork(cursor, addr);
}
