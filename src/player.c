/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamaris <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 16:32:21 by ddamaris          #+#    #+#             */
/*   Updated: 2020/07/23 13:51:14 by ctelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static t_player	*init_player(t_vm  *vm)
{
	t_player	*player;

	if (!(player = (t_player *)ft_memalloc(sizeof(t_player))))
		error_func("r-", "ERROR: Memory allocation error", vm);
	player->id = 0;
	player->name = NULL;
	player->comment = NULL;
	player->code_size = 0;
	player->code = NULL;
	player->last_live_cycle = 0;
	player->curr_lives_num = 0;
	player->prev_lives_num = 0;
	player->pc = 0;
	player->next = NULL;
	return (player);
}

static void	put_player(t_player *player, t_vm *vm)
{
	int		i;

	i = 0;
	while (vm->players[i])
		i++;
	player->id = i + 1;
	vm->players[i] = player;
}

void		*add_player(char *filename, int id, t_vm *vm)
{
	t_player	*player;
	t_player 	*tmp;
	int			fd;

	if ((fd = open(filename, O_RDONLY)) < 0)
		error_func("r-", "ERROR: Can't open file with champion", vm);
	player = init_player(vm);
	player->id = id;
	parse_champion(fd, player, vm);
	if (id)
	{
		if (!vm->players[id - 1])
			vm->players[id - 1] = player;
		else
		{
			tmp = vm->players[id - 1];
			vm->players[id - 1] = player;
			put_player(tmp, vm);
		}
	}
	else
		put_player(player, vm);
	vm->players_num++;
}
