/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamaris <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 12:34:21 by ddamaris          #+#    #+#             */
/*   Updated: 2020/07/23 13:51:14 by ctelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		step_over_arg(int8_t arg_type, t_op *op)
{
	if (arg_type == T_REG)
		return (1);
	else if (arg_type == T_DIR)
		return (op->t_dir_size);
	else if (arg_type == T_IND)
		return (IND_SIZE);
	return (0);
}

int32_t	calc_step(t_cursor *cursor, t_op *op)
{
	int32_t		i;
	int32_t		step;

	i = 0;
	step = (op->args_types_code) ? 2 : 1;
	while (i < op_tab[cursor->op_code - 1].args_num)
	{
		step += step_over_arg(cursor->args_types[i], op);
		i++;
	}
	return (step);
}
