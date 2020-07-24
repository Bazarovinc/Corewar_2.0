/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_and.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctelma <ctelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 21:22:39 by ctelma            #+#    #+#             */
/*   Updated: 2020/07/23 13:51:16 by ctelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "vm.h"

static void	print_and(t_cursor *cursor, int32_t v1, int32_t v2,
						int32_t r_id)
{
	ft_printf("%s", cursor->player->color);
	ft_printf("cursor of %10s executes operation: and ", cursor->player->name);
	ft_printf("%d %d r%d\n", v1, v2, r_id);
	ft_printf("%s", NC);
}

void				op_and(t_vm *vm, t_cursor *cursor)
{
	int32_t	value_1;
	int32_t	value_2;
	int32_t	value;
	int32_t	r_id;

	cursor->step += 1;
	value_1 = get_op_arg(vm, cursor, 1, true);
	value_2 = get_op_arg(vm, cursor, 2, true);
	value = value_1 & value_2;
	cursor->carry = !value;
	r_id = get_byte(vm, cursor->pc, cursor->step);
	cursor->reg[r_id - 1] = value;
	cursor->step += 1;
	if (vm->stat_fl)
		print_and(cursor, value_1, value_2, r_id);
}
