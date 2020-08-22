/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_win.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gerenfor <gerenfor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 15:33:41 by gerenfor          #+#    #+#             */
/*   Updated: 2020/07/23 13:51:14 by gerenfor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_player	*ft_comment(t_vm *vm)
{
	int			i;
	t_player	*player;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (vm->players[i])
		{
			if (vm->players[i]->id == vm->last_alive->id)
				player = vm->players[i];
		}
		i++;
	}
	return (player);
}

void		ft_winner(t_vm *vm)
{
	int			col;
	int			row;
	t_player	*player;
	int			key;

	player = ft_comment(vm);
	clear();
	key = -1;
	while (key != 10)
	{
		key = getch();
		ft_clear(vm);
		draw_frame(vm);
		getmaxyx(stdscr, row, col);
		attron(COLOR_PAIR(vm->last_alive->id + 1));
		mvwprintw(stdscr, row / 2, col / 2, "Contestant %d, \"%s\", has won !",
						vm->last_alive->id, vm->last_alive->name);
		mvwprintw(stdscr, row / 2 + 1, col / 2, "%s", player->comment);
		mvwprintw(stdscr, row / 2 + 2, col / 2, "press enter to exit");
		stop_color();
		refresh();
	}
}
