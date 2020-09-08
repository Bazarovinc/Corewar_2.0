/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_car.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gerenfor <gerenfor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 15:33:41 by gerenfor          #+#    #+#             */
/*   Updated: 2020/07/23 13:51:14 by gerenfor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_uncar(int i, int j)
{
	move(i, j + 2);
	waddch(stdscr, ' ');
	move(i, j - 1);
	waddch(stdscr, ' ');
}

void	drow_car(int i, int j)
{
	move(i, j + 2);
	waddch(stdscr, 117 | A_ALTCHARSET);
	move(i, j - 1);
	waddch(stdscr, 116 | A_ALTCHARSET);
}
