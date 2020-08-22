/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vm_drow.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gerenfor <gerenfor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 15:33:41 by gerenfor          #+#    #+#             */
/*   Updated: 2020/07/23 13:51:14 by gerenfor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_end_drow(t_vm *vm)
{
	if (vm->vis_fl != 0)
		ft_winner(vm);
	if (vm->vis_fl != 0)
		stop_drow();
}

void	ft_go_drow(t_vm *vm)
{
	if (vm->vis_fl == 1)
		drow_arena(vm);
	if (vm->vis_fl == 2)
	{
		ft_clear(vm);
		draw_frame(vm);
		mvwprintw(stdscr, vm->vis.row / 2, vm->vis.col / 2, "Please wait...");
		refresh();
	}
}
