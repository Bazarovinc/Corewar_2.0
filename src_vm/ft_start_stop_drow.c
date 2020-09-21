/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start_stop_drow.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gerenfor <gerenfor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 15:33:41 by gerenfor          #+#    #+#             */
/*   Updated: 2020/09/21 11:39:08 by ctelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	init_colors(void)
{
	start_color();
	init_color(COLOR_GREY, 500, 500, 500);
	init_pair(P0, COLOR_GREY, COLOR_BLACK);
	init_pair(P1, COLOR_RED, COLOR_BLACK);
	init_pair(P2, COLOR_GREEN, COLOR_BLACK);
	init_pair(P3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(P4, COLOR_CYAN, COLOR_BLACK);
	init_pair(P0W, COLOR_WHITE, COLOR_GREY);
	init_pair(P1W, COLOR_WHITE, COLOR_RED);
	init_pair(P2W, COLOR_WHITE, COLOR_GREEN);
	init_pair(P3W, COLOR_WHITE, COLOR_YELLOW);
	init_pair(P4W, COLOR_WHITE, COLOR_CYAN);
}

void	rebild(t_vm *vm)
{
	int		i;

	i = 0;
	while (i < MEM_SIZE)
	{
		vm->vis.old_arena[i] = vm->arena[i];
		vm->vis.cur_name[i] = vm->cur_name[i];
		i++;
	}
}

void	ft_player_print(int row, int col, t_vm *vm)
{
	int			i;
	t_player	*player;

	i = 0;
	mvwprintw(stdscr, row - 10, col / 2, "Introducing contestants...");
	while (i < MAX_PLAYERS)
	{
		player = vm->players[i];
		if (player)
		{
			attron(COLOR_PAIR(player->id + 1));
			mvwprintw(stdscr, row - 9 + i, col / 2,
				"* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
				player->id, player->code_size, player->name, player->comment);
		}
		i++;
		refresh();
		stop_color();
	}
}

void	ft_flash(int col, int row, int k)
{
	int		i;
	int		j;

	i = 10;
	while (i < row - 20)
	{
		j = 30;
		while (j < col - 30)
		{
			move(i, j);
			if ((i + j + k) % 5 == 0)
				attron(COLOR_PAIR(P0));
			if ((i + j + k) % 5 == 1)
				attron(COLOR_PAIR(P1));
			if ((i + j + k) % 5 == 2)
				attron(COLOR_PAIR(P2));
			if ((i + j + k) % 5 == 3)
				attron(COLOR_PAIR(P3));
			if ((i + j + k) % 5 == 4)
				attron(COLOR_PAIR(P4));
			addch(97 | A_ALTCHARSET);
			j++;
		}
		i++;
	}
}
