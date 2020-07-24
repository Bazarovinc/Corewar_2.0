/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lld.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctelma <ctelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 21:23:20 by ctelma            #+#    #+#             */
/*   Updated: 2020/07/23 13:51:15 by ctelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	print_lld(t_cursor *cursor, int32_t value, int32_t r_id)
{
	ft_printf("%s", cursor->player->color);
	ft_printf("cursor of %10s executes operation: ", cursor->player->name);
	ft_printf("lld %d r%d\n", value, r_id);
	ft_printf("%s", NC);
}

void				op_lld(t_vm *vm, t_cursor *cursor)
{
	int32_t	value;
	int32_t	r_id;

	cursor->step += 2;
	value = get_op_arg(vm, cursor, 1, false);
	cursor->carry = !value;
	r_id = get_byte(vm, cursor->pc, cursor->step);
	cursor->reg[r_id - 1] = value;
	cursor->step += 1;
	if (vm->stat_fl)
		print_lld(cursor, value, r_id);
}
