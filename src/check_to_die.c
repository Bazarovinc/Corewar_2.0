/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_to_die.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamaris <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 17:20:21 by ddamaris          #+#    #+#             */
/*   Updated: 2020/07/25 12:51:41 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

static void		print_cycle_to_die(t_vm *vm)
{
	ft_printf("%s", YELLOW);
	if (vm->checks_num == MAX_CHECKS)
	{
		ft_printf("Cycle_to_die reduced to %d because number of checks ",
				  vm->cycles_to_die);
		ft_printf("(%d) reached MAX_CHECKS(%d)\n", vm->checks_num, MAX_CHECKS);
	}
	else if (vm->lives_num >= NBR_LIVE)
	{
		ft_printf("Cycle_to_die reduced to %d because number of lives ",
				  vm->cycles_to_die);
		ft_printf("(%d) exceed NBR_LIVE(%d)\n", vm->lives_num, NBR_LIVE);
	}
	ft_printf("%s", NC);
//	ft_printf("Press Enter\n");
//	while (getchar() != '\n')
//		;
}

static void		reset_lives_nums(t_vm *vm)
{
	int32_t		i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (vm->players[i])
		{
			vm->players[i]->prev_lives_num = vm->players[i]->curr_lives_num;
			vm->players[i]->curr_lives_num = 0;
		}
		i++;
	}
	vm->lives_num = 0;
}

static void		delete_cursor(t_cursor *cursor, t_vm *vm)
{
	t_cursor	*prev;

	prev = vm->cursors;
	if (prev == cursor)
		vm->cursors = prev->next;
	else
	{
		while (prev && prev->next != cursor)
			prev = prev->next;
		if (prev)
			prev->next = cursor->next;
	}
	if (vm->stat_fl)
		ft_printf("%sCursor %d of %s %sis dead%s\n",
			cursor->player->color, cursor->id, cursor->player->name, RED, NC);
	if (cursor)
	{
		cursor->player = NULL;
		cursor->next = NULL;
		free(cursor);
		cursor = NULL;
		vm->cursors_num--;
	}
}

void			check_and_delete(t_vm *vm)
{
	t_cursor	*cursor;
	t_cursor	*to_die;

	vm->checks_num++;
	cursor = vm->cursors;
	if (vm->cycles_to_die <= 0 && vm->stat_fl)
		ft_printf("%sCycle to die = %d, All champions must die%s\n", RED,
				  vm->cycles_to_die, NC);
	while (cursor)
	{
		to_die = cursor;
		cursor = cursor->next;
		if (vm->cycles_to_die <= 0 ||
		(int)(vm->cur_cycle - to_die->last_live_cycle) >= vm->cycles_to_die)
			delete_cursor(to_die, vm);
	}
	if (vm->checks_num == MAX_CHECKS || vm->lives_num >= NBR_LIVE)
	{
		vm->cycles_to_die -= CYCLE_DELTA;
		if (vm->stat_fl)
			print_cycle_to_die(vm);
		vm->checks_num = 0;
	}
	reset_lives_nums(vm);
	vm->cycles_after_check = 0;
}
