/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gerenfor <gerenfor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 15:33:41 by gerenfor          #+#    #+#             */
/*   Updated: 2020/09/21 11:39:08 by ctelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_key_a(int key, t_vm *vm)
{
	if (key == 109)
	{
		if (vm->vis.mode == 0)
			vm->vis.mode = 1;
		else
			vm->vis.mode = 0;
	}
	if (key == 105)
	{
		if (vm->vis.ign == 0)
			vm->vis.ign = 1;
		else
			vm->vis.ign = 0;
	}
	if (key == 113)
	{
		vm->vis_fl = 2;
		clear();
	}
}

void	ft_key_b(int key, t_vm *vm)
{
	if (key == 61 && vm->vis.mode == 0)
		vm->vis.speed = vm->vis.speed - 100;
	if (vm->vis.speed < 0)
		vm->vis.speed = 0;
	if (key == 45 && vm->vis.mode == 0)
		vm->vis.speed = vm->vis.speed + 100;
	if (key == 119)
		vm->vis.step = vm->vis.step + 10;
	if (key == 115)
		vm->vis.step = vm->vis.step - 10;
	if (vm->vis.step < 0)
		vm->vis.step = 0;
}

int		ft_key_use(t_vm *vm)
{
	int key;
	int time;

	time = 0;
	while (time <= vm->vis.speed)
	{
		key = getch();
		if (vm->vis.mode == 1)
			time += vm->vis.speed;
		else
			napms(1);
		time++;
		ft_key_a(key, vm);
		ft_key_b(key, vm);
		if (key != 113 && key != 109 && key != 32)
			key = -1;
		if (vm->vis.mode != 1 && key == -1)
			key = 0;
	}
	return (key);
}
