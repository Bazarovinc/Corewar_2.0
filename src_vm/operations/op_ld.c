/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctelma <ctelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 21:22:49 by ctelma            #+#    #+#             */
/*   Updated: 2020/09/21 11:39:09 by ctelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

static void	print_ld(t_cursor *cursor, int32_t value, int32_t r_id)
{
	ft_printf("%s", cursor->player->color);
	ft_printf("cursor %4d of %10s executes:\t", cursor->id,
		cursor->player->name);
	ft_printf("ld %d r%d\n", value, r_id);
	ft_printf("%s", NC);
}

void		op_ld(t_vm *vm, t_cursor *cursor)
{
	int32_t	value;
	int32_t	r_id;

	cursor->step += 2;
	value = get_op_arg(vm, cursor, 1, true);
	cursor->carry = !value;
	r_id = get_byte(vm, cursor->pc, cursor->step);
	cursor->reg[r_id - 1] = value;
	cursor->step += 1;
	if (vm->stat_fl)
		print_ld(cursor, value, r_id);
}
