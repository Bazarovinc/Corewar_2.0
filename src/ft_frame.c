/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_frame.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gerenfor <gerenfor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 15:33:41 by gerenfor          #+#    #+#             */
/*   Updated: 2020/07/23 13:51:14 by gerenfor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_frame_side(int i, int j, t_vm *vm)
{
	int	col;
	int	row;

	getmaxyx(stdscr, row, col);
	if (i == 0 && j == col - 1 - vm->vis.add)
		waddch(stdscr, 119 | A_ALTCHARSET);
	else if (i == 0 && j == col - 1)
		waddch(stdscr, 107 | A_ALTCHARSET);
	else if (i == row - 1 && j == 0)
		waddch(stdscr, 109 | A_ALTCHARSET);
	else if (i == row - 1 - vm->vis.line && j == col - 1 - vm->vis.add)
		waddch(stdscr, 118 | A_ALTCHARSET);
	else if (i == row - 1 && j == col - 1)
		waddch(stdscr, 106 | A_ALTCHARSET);
	else if (i == row - 1 - vm->vis.line && j == 0)
		waddch(stdscr, 116 | A_ALTCHARSET);
	else if (i == row - 1 - vm->vis.line && j == col - 1)
		waddch(stdscr, 117 | A_ALTCHARSET);
	else if (i == 0 || i == row - 1 || i == row - 1 - vm->vis.line)
		waddch(stdscr, 113 | A_ALTCHARSET);
	else if (j == 0 || j == col - 1)
		waddch(stdscr, 120 | A_ALTCHARSET);
	else if (j == col - 1 - vm->vis.add && i < row - 1 - vm->vis.line)
		waddch(stdscr, 120 | A_ALTCHARSET);
}

void	draw_frame(t_vm *vm)
{
	int	i;
	int	j;
	int	col;
	int	row;

	getmaxyx(stdscr, row, col);
	i = 0;
	while (i < row)
	{
		j = 0;
		while (j < col)
		{
			move(i, j);
			if (i == 0 && j == 0)
				waddch(stdscr, 108 | A_ALTCHARSET);
			else
				ft_frame_side(i, j, vm);
			j++;
		}
		i++;
	}
}
