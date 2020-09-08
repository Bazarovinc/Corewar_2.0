/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_logo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gerenfor <gerenfor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 15:33:41 by gerenfor          #+#    #+#             */
/*   Updated: 2020/07/23 13:51:14 by gerenfor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_logo(t_vm *vm)
{
	int	k;
	int	key;
	int	col;
	int	row;

	k = 0;
	key = -1;
	while (key != 32)
	{
		ft_clear(vm);
		getmaxyx(stdscr, row, col);
		key = getch();
		ft_flash(col, row, k);
		stop_color();
		ft_player_print(row, col, vm);
		if (k % 7 != 0)
			mvwprintw(stdscr, row - 3, (col / 2) - 13,
					"Press space bar to start.");
		else
			mvwprintw(stdscr, row - 3, (col / 2) - 13,
					"                         ");
		mvwprintw(stdscr, 9, (col / 2) - 5, "COREWAR_21");
		if (k++ > 10)
			k = 0;
	}
}

void	ft_start_logo(t_vm *vm)
{
	int	col;
	int	row;
	int	lol;

	lol = 0;
	while (lol < MEM_SIZE)
	{
		clear();
		getmaxyx(stdscr, row, col);
		lol = (col - vm->vis.add - 4) * (row - vm->vis.line - 3) / 4;
		mvwprintw(stdscr, row / 2, col / 2 - 15,
				"Window size is not big enough.");
		mvwprintw(stdscr, (row / 2) + 1, col / 2 - 21,
				"Make the window larger or the font smaller.");
		refresh();
	}
	ft_logo(vm);
	clear();
}

void	start_drow(t_vm *vm)
{
	int row;
	int col;

	rebild(vm);
	zero_cars(vm->vis.old_cars, vm);
	zero_cars(vm->vis.cars, vm);
	getmaxyx(stdscr, row, col);
	vm->vis.start = 1;
	vm->vis.row = row;
	vm->vis.col = col;
	vm->vis.add = 30;
	vm->vis.line = 5;
	vm->vis.mode = 1;
	vm->vis.speed = 500;
	vm->vis.ign = 0;
	vm->vis.car_mo = 1;
	vm->vis.last = 0;
	vm->vis.step = 0;
	initscr();
	noecho();
	curs_set(0);
	timeout(0);
	init_colors();
	ft_start_logo(vm);
}

void	stop_drow(void)
{
	echo();
	curs_set(1);
	clear();
	refresh();
	resetty();
	endwin();
}
