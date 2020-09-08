/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_car_no.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gerenfor <gerenfor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 15:33:41 by gerenfor          #+#    #+#             */
/*   Updated: 2020/07/23 13:51:14 by gerenfor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	zero_cars(u_int8_t *cars, t_vm *vm)
{
	int i;

	i = 0;
	while (i < MEM_SIZE)
	{
		cars[i] = 0;
		i++;
	}
	i = 0;
	while (i < MAX_PLAYERS)
	{
		vm->vis.cars_play[i] = 0;
		i++;
	}
}

void	recars(u_int8_t *cars, t_vm *vm)
{
	t_cursor *tmp;

	if (vm->cursors != NULL)
	{
		tmp = vm->cursors;
		while (tmp != NULL)
		{
			vm->vis.cars_play[tmp->player->id - 1] =
				vm->vis.cars_play[tmp->player->id - 1] + 1;
			cars[tmp->pc] = tmp->player->id;
			tmp = tmp->next;
		}
	}
}

int		car_count(u_int8_t *cars)
{
	int	i;
	int	car_q;

	i = 0;
	car_q = 0;
	while (i < MEM_SIZE)
	{
		car_q = car_q + cars[i];
		i++;
	}
	return (car_q);
}

void	car_move(t_vm *vm)
{
	u_int8_t	*master;
	u_int8_t	*slave;
	int			i;

	master = vm->vis.cars;
	slave = vm->vis.old_cars;
	i = 0;
	while (i < MEM_SIZE)
	{
		slave[i] = master[i];
		i++;
	}
}

int		car_check(u_int8_t *cars, t_vm *vm)
{
	int			i;
	int			dif;
	u_int8_t	*old_cars;

	old_cars = vm->vis.old_cars;
	i = 0;
	dif = 0;
	while (i < MEM_SIZE && dif == 0)
	{
		if (cars[i] != old_cars[i])
			dif = 1;
		i++;
	}
	return (dif);
}
