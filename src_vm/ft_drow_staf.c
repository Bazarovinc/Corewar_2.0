/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_drow_staf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gerenfor <gerenfor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 15:33:41 by gerenfor          #+#    #+#             */
/*   Updated: 2020/09/21 11:39:08 by ctelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_drow_car_pl(int col, t_vm *vm)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < MAX_PLAYERS)
	{
		if (vm->vis.cars_play[i] != 0)
		{
			color_select(0, i + 1);
			mvwprintw(stdscr, 6 + j, col + 2, "Player %i has %4i cars",
							i + 1, vm->vis.cars_play[i]);
			stop_color();
			j++;
		}
		i++;
	}
	while (j < MAX_PLAYERS)
	{
		mvwprintw(stdscr, 6 + j, col + 2, "                         ");
		j++;
	}
}

void	drow_static(int row, int col, t_vm *vm)
{
	mvwprintw(stdscr, 2, col + 2, "cycles_to_die = %i", vm->cycles_to_die);
	mvwprintw(stdscr, 3, col + 2, "cur_cycle = %i", vm->cur_cycle);
	mvwprintw(stdscr, 4, col + 2, "cycles_after_check = %i",
						vm->cycles_after_check);
	mvwprintw(stdscr, 5, col + 2, "alive per check = %i", vm->lives_num);
	mvwprintw(stdscr, row, 2, "\"q\" - exit visual mod");
	mvwprintw(stdscr, row + 1, 100, "\"w\" - more cycles before next drow");
	mvwprintw(stdscr, row + 2, 100, "\"s\" - less cycles before next drow");
	mvwprintw(stdscr, row + 1, 28, "\"m\" - change mode");
	mvwprintw(stdscr, row + 1, 70, "\"i\" - change mode");
	ft_drow_car_pl(col, vm);
	if (vm->vis.ign == 0)
		mvwprintw(stdscr, row, 70, "all changes  mode");
	else
		mvwprintw(stdscr, row, 70, "rewrite only mode");
}

void	drow_text(int row, int col, t_vm *vm)
{
	drow_static(row, col, vm);
	if (vm->vis.mode == 0)
	{
		mvwprintw(stdscr, row + 1, 2, "\"+\" - more speed");
		mvwprintw(stdscr, row + 2, 2, "\"-\" - less speed");
		mvwprintw(stdscr, row, 28, "avto mode");
		if (vm->vis.speed == 0)
			mvwprintw(stdscr, row + 3, 2, "unlimited speed         ");
		else
			mvwprintw(stdscr, row + 3, 2, "speed 1/%i fps          ",
									vm->vis.speed);
	}
	if (vm->vis.mode == 1)
	{
		mvwprintw(stdscr, row + 1, 2, "                  ");
		mvwprintw(stdscr, row + 2, 2, "                  ");
		mvwprintw(stdscr, row, 28, "step mode");
		mvwprintw(stdscr, row + 3, 2, "press space for new step");
	}
	if (vm->vis.step < 2)
		mvwprintw(stdscr, row, 100, "show all changes                        ");
	else
		mvwprintw(stdscr, row, 100, "show changes after more then %4i steps",
									vm->vis.step);
}

void	drow_more(int k, t_vm *vm)
{
	int	i;
	int	j;
	int	row;
	int	col;

	getmaxyx(stdscr, row, col);
	col -= vm->vis.add;
	row -= vm->vis.line;
	i = row - 2;
	if (k < MEM_SIZE)
	{
		if (col % 2 == 0)
			j = 2;
		else
			j = 3;
		while (j < col - 3)
		{
			move(i, j);
			waddch(stdscr, 46 | A_ALTCHARSET);
			j++;
		}
	}
	drow_text(row, col, vm);
}
