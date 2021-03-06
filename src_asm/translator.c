/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translator.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 14:48:01 by dheredat          #+#    #+#             */
/*   Updated: 2020/09/21 00:59:46 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void				write_label(char *l)
{
	write(ERRSTREAM, "No such label ", 15);
	write(ERRSTREAM, l, ft_strlen(l));
	write(ERRSTREAM, "\n", 1);
}

int					get_args(t_op *op)
{
	int i;
	int j;

	i = 0;
	while (i < 3 && op->args[i])
	{
		j = 0;
		if (op->args[i][j] == 'r')
		{
			op->nargs[i] = atoli(op->args[i] + j + 1);
			++i;
			continue ;
		}
		if (op->args[i] && op->args[i][j] == '%')
			++j;
		if (op->args[i] && op->args[i][j] == ':')
			op->curlabels[i] = op->args[i] + j + 1;
		else
			op->nargs[i] = atoli(op->args[i] + j);
		++i;
	}
	return (0);
}

int					get_types(t_op *op, t_hero *hero)
{
	int				i;
	unsigned char	type;
	unsigned int	offset;

	i = -1;
	type = 0;
	offset = 64;
	while (++i < 3)
	{
		if (op->types[i] == T_REG)
			type |= offset;
		else if (op->types[i] == T_DIR)
			type |= offset * 2;
		else if (op->types[i] == T_IND)
		{
			type |= offset;
			type |= offset * 2;
		}
		offset /= 2 * 2;
	}
	hero->excode[hero->p++] = type;
	return (1);
}

static unsigned int	index_count(t_hero *hero)
{
	unsigned int	bcsz;
	int				i;
	t_op			*beg;

	beg = hero->op;
	i = 0;
	bcsz = 0;
	while (beg)
	{
		bcsz += beg->bytes;
		beg->idop = ++i;
		beg = beg->next;
	}
	return (bcsz);
}

int					translator(t_hero *hero, char *fn)
{
	unsigned char	bc[2192];
	t_op			*beg;
	unsigned int	i;

	i = -1;
	while (++i < 2192)
		bc[i] = 0;
	i = 0;
	hero->p = 0;
	hero->bt_cd_sz = index_count(hero);
	if (!(hero->excode = (unsigned char*)malloc(sizeof(char) * hero->bt_cd_sz)))
		error_func("r-", "Error! Malloc error.");
	while (i < hero->bt_cd_sz)
		hero->excode[i++] = 0;
	beg = hero->op;
	while (beg)
	{
		if (!(op_code(beg, hero)))
			error_func("r-", "Error! Postprocess error.");
		beg = beg->next;
	}
	write_filler(bc, hero, hero->bt_cd_sz, fn);
	return (0);
}
