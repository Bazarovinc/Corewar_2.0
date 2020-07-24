/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamaris <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 14:32:21 by ddamaris          #+#    #+#             */
/*   Updated: 2020/07/23 13:51:14 by ctelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

void		colorise_players(t_vm *vm)
{
	int		i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (vm->players[i])
		{
			if (i == 0)
				vm->players[i]->color = CYAN;
			if (i == 1)
				vm->players[i]->color = GREEN;
			if (i == 2)
				vm->players[i]->color = WHITE;
			if (i == 3)
				vm->players[i]->color = MAG;
		}
		i++;
	}
}

static void	parse_dump_flag(char **argv, t_vm *vm)
{
	int	num;

	num = 0;
	if ((num = ft_strtoint(*argv + 1)) >= 0)
		vm->dump_fl = num;
	else
		error_func("r-", "ERROR: Wrong argument for -dump", vm);
}

static int		parse_n_flag(char **argv, t_vm *vm)
{
	int id;

	id = 0;
	if ((id = ft_strtoint(*argv)) > 0 && id <= MAX_PLAYERS)
	{
		if (ft_strcmp(*(argv + 1), ".cor"))
			add_player(*(argv + 1), id, vm);
	}
	else
		error_func("r-", "ERROR: Wrong argument for -n", vm);
	return (1);
}

void 	parser(t_vm *vm, char **argv)
{
	argv++;
	while (*argv)
	{
		if (!ft_strcmp(*argv, "-dump"))
			parse_dump_flag(++argv, vm);
		else if (!ft_strcmp(*argv, "-n") && parse_n_flag(++argv, vm))
			argv++;
		else if (!ft_strcmp(*argv, "-visu"))
			vm->vis_fl = 1;
		else if (!ft_strcmp(*argv, "-aff"))
			vm->aff_fl = 1;
		else if (!ft_strcmp(*argv, "-stat"))
			vm->stat_fl = 1;
		else if (!ft_strcmp(*argv, "-alive"))
			vm->alive_fl = 1;
		else if (file_is_cor(*argv, vm))
			add_player(*argv, 0, vm);
		argv++;
	}
	if (vm->players_num > MAX_PLAYERS || vm->players_num == 0)
		error_func("r-", "ERROR: Wrong number of champions", vm);
	colorise_players(vm);
}