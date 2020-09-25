/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctelma <ctelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 20:09:17 by ctelma            #+#    #+#             */
/*   Updated: 2020/09/24 21:30:29 by ctelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

static void	print_aff(t_cursor *cursor, char value)
{
	ft_printf("%s", cursor->player->color);
	ft_printf("cursor %4d of %10s executes:\t", cursor->id,
			cursor->player->name);
	ft_printf("aff %c\n", value);
	ft_printf("%s", NC);
}

void		op_aff(t_vm *vm, t_cursor *cursor)
{
	int32_t	r_id;
	int32_t	value;

	cursor->step += 2;
	r_id = get_byte(vm, cursor->pc, cursor->step);
	value = cursor->reg[r_id - 1];
	cursor->step += 1;
	if (vm->aff_fl && vm->vis_fl == 0)
		ft_printf("Aff: %c\n", (char)value);
	if (vm->stat_fl && vm->vis_fl == 0)
		print_aff(cursor, (char)value);
}
