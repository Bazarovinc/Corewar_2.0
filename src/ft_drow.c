/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_drow.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gerenfor <gerenfor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 15:33:41 by gerenfor          #+#    #+#             */
/*   Updated: 2020/07/23 13:51:14 by gerenfor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		find_ctd(t_vm *vm)
{
	int			i;
	u_int8_t	*master;
	u_int8_t	*slave;

	master = vm->cur_name;
	slave = vm->vis.cur_name;
	i = 0;
	while (i < MEM_SIZE)
	{
		if (master[i] != slave[i])
			return (1);
		i++;
	}
	return (0);
}

void	ft_clear(t_vm *vm)
{
	int	row;
	int	col;

	getmaxyx(stdscr, row, col);
	if (vm->vis.col != col || vm->vis.row != row)
	{
		clear();
		vm->vis.col = col;
		vm->vis.row = row;
	}
}

int		drow_arena_body(int row, int col, t_vm *vm)
{
	int	i;
	int	j;
	int	k;

	i = 2;
	k = 0;
	while (i < row - 2 && k < MEM_SIZE)
	{
		j = col - (((col - 2) / 3) * 3);
		while (j < col - 3 && k < MEM_SIZE)
		{
			ft_start_color(vm, k, i, j);
			mvwprintw(stdscr, i, j, "%02X", vm->arena[k]);
			refresh();
			stop_color();
			k++;
			j += 4;
		}
		i++;
	}
	return (k);
}

int		start_or_go(t_vm *vm)
{
	if ((int)(vm->cur_cycle) < vm->vis.last + vm->vis.step)
		return (1);
	car_move(vm);
	zero_cars(vm->vis.cars, vm);
	recars(vm->vis.cars, vm);
	vm->vis.ctd = find_ctd(vm);
	if (vm->vis.ign == 0)
		vm->vis.car_mo = car_check(vm->vis.cars, vm);
	else
		vm->vis.car_mo = 0;
	if (vm->vis.ctd == 0 && vm->vis.car_mo == 0 && vm->vis.start == 0)
		return (1);
	return (0);
}

void	drow_arena(t_vm *vm)
{
	int	col;
	int	row;
	int	k;
	int	key;

	if (start_or_go(vm))
		return ;
	key = -1;
	while (key < 0)
	{
		getmaxyx(stdscr, row, col);
		ft_clear(vm);
		draw_frame(vm);
		col -= vm->vis.add;
		row -= vm->vis.line;
		k = drow_arena_body(row, col, vm);
		drow_more(k, vm);
		key = ft_key_use(vm);
		refresh();
		vm->vis.start = 0;
	}
	if (vm->vis.ctd == 1)
		rebild(vm);
	vm->vis.last = vm->cur_cycle;
}
