/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctelma <ctelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 21:23:40 by ctelma            #+#    #+#             */
/*   Updated: 2020/09/21 11:39:09 by ctelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

static void	print_sti(t_cursor *cursor, int32_t r_id, int32_t addr_1,
						int32_t addr_2)
{
	ft_printf("%s", cursor->player->color);
	ft_printf("cursor %4d of %10s executes:\t", cursor->id,
		cursor->player->name);
	ft_printf("sti r%d %d %d", r_id, addr_1, addr_2);
	ft_printf("\t -> store to %d + %d = %d (with pc and mod %d)\n",
				addr_1, addr_2, addr_1 + addr_2,
				cursor->pc + ((addr_1 + addr_2) % IDX_MOD));
	ft_printf("%s", NC);
}

void		op_sti(t_vm *vm, t_cursor *cursor)
{
	int32_t	r_id;
	int32_t	value;
	int32_t	addr_1;
	int32_t	addr_2;

	cursor->step += 2;
	r_id = get_byte(vm, cursor->pc, cursor->step);
	cursor->step += 1;
	value = cursor->reg[r_id - 1];
	addr_1 = get_op_arg(vm, cursor, 2, true);
	addr_2 = get_op_arg(vm, cursor, 3, true);
	int32_to_bytecode(vm->arena,
			(cursor->pc + ((addr_1 + addr_2) % IDX_MOD)), value, DIR_SIZE);
	fill_cor_name(4, cursor->pc + ((addr_1 + addr_2) % IDX_MOD),
		cursor->player, vm);
	if (vm->stat_fl)
		print_sti(cursor, r_id, addr_1, addr_2);
}
