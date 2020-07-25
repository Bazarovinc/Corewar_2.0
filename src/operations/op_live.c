/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctelma <ctelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 21:23:10 by ctelma            #+#    #+#             */
/*   Updated: 2020/07/24 16:10:27 by ctelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

static void			print_live(t_cursor *cursor, t_player *player, int id)
{
	ft_printf("%s", cursor->player->color);
	ft_printf("cursor of %10s executes operation: ", cursor->player->name);
	if (player)
		ft_printf("live %d (%s)\n", id, player->name);
	else
		ft_printf("live %d (NULL)\n", id);
	ft_printf("%s", NC);
}

void	print_live_msg(t_player *player)
{
	ft_printf("%s", player->color);
	ft_printf("Player %d (%s) is said to be alive\n",
			player->id, player->name);
	ft_printf("%s", NC);
}

void				op_live(t_vm *vm, t_cursor *cursor)
{
	int		player_id;
	t_player	*player;

	player = NULL;
	cursor->step += 1;
	player_id = (get_op_arg(vm, cursor, 1, false));
	cursor->last_live_cycle = vm->cur_cycle;
	player = NULL;
	if (player_id <= -1 && player_id >= -MAX_PLAYERS &&
		(player = vm->players[FT_ABS(player_id) - 1]))
	{
//		player = vm->players[FT_ABS(player_id) - 1];
		player->last_live_cycle = vm->cur_cycle;
		player->curr_lives_num++;
		vm->lives_num++;
		vm->last_alive = player;
/*		if (vm->vs)
		{
			vm->vs->map[cursor->pc].wait_cycles_live = CYCLE_TO_WAIT;
			vm->vs->map[cursor->pc].player_live = player;
		}*/
		if (vm->alive_fl)
			print_live_msg(player);
	}
	if (vm->stat_fl)
		print_live(cursor, player, player_id);
}
