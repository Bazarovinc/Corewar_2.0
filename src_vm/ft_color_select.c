/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color_select.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gerenfor <gerenfor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 15:33:41 by gerenfor          #+#    #+#             */
/*   Updated: 2020/07/23 13:51:14 by gerenfor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	color_select(int is_curs, int playerno)
{
	if (playerno == 0 && is_curs == 0)
		attron(COLOR_PAIR(P0));
	if (playerno == 1 && is_curs == 0)
		attron(COLOR_PAIR(P1));
	if (playerno == 2 && is_curs == 0)
		attron(COLOR_PAIR(P2));
	if (playerno == 3 && is_curs == 0)
		attron(COLOR_PAIR(P3));
	if (playerno == 4 && is_curs == 0)
		attron(COLOR_PAIR(P4));
	if (playerno == 0 && is_curs == 2)
		attron(COLOR_PAIR(P0W));
	if (playerno == 1 && is_curs == 2)
		attron(COLOR_PAIR(P1W));
	if (playerno == 2 && is_curs == 2)
		attron(COLOR_PAIR(P2W));
	if (playerno == 3 && is_curs == 2)
		attron(COLOR_PAIR(P3W));
	if (playerno == 4 && is_curs == 2)
		attron(COLOR_PAIR(P4W));
}

void	ft_start_color(t_vm *vm, int pose, int i, int j)
{
	int	is_curs;
	int	playerno;

	is_curs = 0;
	if (vm->vis.cars[pose] != 0)
		is_curs = 1;
	if (is_curs == 1)
	{
		if (vm->vis.cars[pose] != vm->vis.old_cars[pose])
			is_curs = 2;
		else
			is_curs = 0;
		playerno = vm->vis.cars[pose];
		color_select(is_curs, playerno);
		drow_car(i, j);
		stop_color();
		is_curs = 0;
	}
	else
		ft_uncar(i, j);
	if (vm->cur_name[pose] != vm->vis.cur_name[pose])
		is_curs = 2;
	playerno = vm->cur_name[pose];
	color_select(is_curs, playerno);
}

void	stop_color(void)
{
	attroff(COLOR_PAIR(P0));
	attroff(COLOR_PAIR(P1));
	attroff(COLOR_PAIR(P2));
	attroff(COLOR_PAIR(P3));
	attroff(COLOR_PAIR(P4));
	attroff(COLOR_PAIR(P0W));
	attroff(COLOR_PAIR(P1W));
	attroff(COLOR_PAIR(P2W));
	attroff(COLOR_PAIR(P3W));
	attroff(COLOR_PAIR(P4W));
}
