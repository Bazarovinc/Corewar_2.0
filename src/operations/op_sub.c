/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctelma <ctelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 21:23:51 by ctelma            #+#    #+#             */
/*   Updated: 2020/07/23 13:51:15 by ctelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	print_sub(t_cursor *cursor, int32_t r1_id, int32_t r2_id,
						int32_t r3_id)
{
	ft_printf("%s", cursor->player->color);
	ft_printf("cursor of %10s executes operation: ", cursor->player->name);
	ft_printf("sub r%d r%d r%d\n", r1_id, r2_id, r3_id);
	ft_printf("%s", NC);
}

void		op_sub(t_vm *vm, t_cursor *cursor)
{
	int32_t	r1_id;
	int32_t	r2_id;
	int32_t	r3_id;
	int32_t	value;

	cursor->step += 2;
	r1_id = get_byte(vm, cursor->pc, cursor->step);
	cursor->step += 1;
	r2_id = get_byte(vm, cursor->pc, cursor->step);
	cursor->step += 1;
	value = cursor->reg[r1_id - 1] - cursor->reg[r2_id - 1];
	cursor->carry = !value;
	r3_id = get_byte(vm, cursor->pc, cursor->step);
	cursor->reg[r3_id - 1] = value;
	cursor->step += 1;
	if (vm->stat_fl)
		print_sub(cursor, r1_id, r2_id, r3_id);
}
