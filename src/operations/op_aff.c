/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctelma <ctelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 20:09:17 by ctelma            #+#    #+#             */
/*   Updated: 2020/07/23 13:51:15 by ctelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	print_aff(t_cursor *cursor, char value)
{
	ft_printf("%s", cursor->player->color);
	ft_printf("cursor of %10s executes operation: ", cursor->player->name);
	ft_printf("aff %c\n", value);
	ft_printf("%s", NC);
}


void	op_aff(t_vm *vm, t_cursor *cursor)
{
    int32_t	r_id;
    int32_t	value;

    cursor->step += 2;
    r_id = get_byte(vm, cursor->pc, cursor->step);
    value = cursor->reg[r_id - 1];
    cursor->step += 1;
    if (vm->aff_fl)
        ft_printf("Aff: %c\n", (char)value);
    if (vm->stat_fl)
    	print_aff(cursor, (char)value);
/*	if (vm->vs)
    {
        vm->vs->aff_symbol = (char)value;
        vm->vs->aff_player = cursor->player;
    }*/
}