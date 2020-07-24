/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_vm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctelma <ctelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 15:31:15 by ctelma            #+#    #+#             */
/*   Updated: 2020/07/23 13:51:14 by ctelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void free_players(t_vm *vm)
{
	int i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (vm->players[i])
		{
			if (vm->players[i]->name)
				free(vm->players[i]->name);
			if (vm->players[i]->comment)
				free(vm->players[i]->comment);
			if (vm->players[i]->code)
				free(vm->players[i]->code);
			free(vm->players[i]);
		}
		i++;
	}
}

static void free_cursor(t_vm *vm)
{
	t_cursor	*cursor;
	t_cursor	*delete;

	cursor = vm->cursors;
	while (cursor)
	{
		delete = cursor;
		cursor = cursor->next;
		ft_memdel((void **)&delete);
	}
	vm->cursors = NULL;
}

void		free_vm(t_vm *vm)
{
	free_players(vm);
	free_cursor(vm);
	free(vm);
}