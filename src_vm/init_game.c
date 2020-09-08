/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamaris <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 22:09:21 by ddamaris          #+#    #+#             */
/*   Updated: 2020/07/24 16:10:27 by ctelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

void			update_cycles_to_exec(t_cursor *cursor, t_vm *vm)
{
	if (cursor->cycles_to_exec == 0)
	{
		cursor->op_code = vm->arena[cursor->pc];
		if (vm->arena[cursor->pc] >= 0x01 && vm->arena[cursor->pc] <= 0x10)
			cursor->cycles_to_exec = g_op_tab[cursor->op_code - 1].cycles;
	}
	if (cursor->cycles_to_exec > 0)
		cursor->cycles_to_exec--;
}

void			init_cursor(t_player *player, t_cursor *cursor, int32_t pc)
{
	cursor->carry = 0;
	cursor->op_code = 0;
	cursor->last_live_cycle = 0;
	cursor->cycles_to_exec = 0;
	cursor->pc = pc;
	cursor->step = 0;
	cursor->reg[0] = -(player->id);
	cursor->player = player;
	cursor->next = NULL;
}

void			add_cursor(t_player *player, int32_t pc, t_vm *vm)
{
	t_cursor	*cursor;

	cursor = NULL;
	if (!(cursor = (t_cursor *)malloc(sizeof(t_cursor))))
		error_func("r-", "ERROR: Memory allocation error", vm);
	init_cursor(player, cursor, pc);
	if (!vm->cursors)
		vm->cursors = cursor;
	else
	{
		cursor->next = vm->cursors;
		vm->cursors = cursor;
	}
	vm->cur_id++;
	vm->cursors->id = vm->cur_id;
	vm->cursors_num++;
}

void			init_cursors(t_vm *vm)
{
	int			i;

	i = MAX_PLAYERS - 1;
	while (i >= 0)
	{
		if (vm->players[i])
			add_cursor(vm->players[i], vm->players[i]->pc, vm);
		i--;
	}
	vm->last_alive = vm->cursors->player;
}

void			init_arena(t_vm *vm)
{
	int			i;
	int32_t		pc;

	i = 0;
	pc = 0;
	while (i < MAX_PLAYERS)
	{
		if (vm->players[i])
		{
			ft_memcpy(&(vm->arena[pc]), vm->players[i]->code,
					(vm->players[i]->code_size));
			vm->players[i]->pc = pc;
			fill_cor_name(vm->players[i]->code_size, pc, vm->players[i], vm);
			pc += MEM_SIZE / vm->players_num;
		}
		i++;
	}
}
