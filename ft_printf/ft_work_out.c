/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_work_out.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamaris <ddamaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 15:19:33 by ddamaris          #+#    #+#             */
/*   Updated: 2020/07/23 13:51:15 by ctelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		cap_o_u_work_out(t_struct *f_lst)
{
	int	length;

	length = 0;
	if (f_lst->f_type == 'U')
		f_lst->hl = 4;
	length = (work_out_uxo(f_lst));
	return (length);
}

int		digit_distribution(t_struct *f_lst)
{
	int length;

	length = 0;
	if (f_lst->f_type == 'd' || f_lst->f_type == 'D' ||
		f_lst->f_type == 'i' || f_lst->f_type == 'I')
		length = (work_out_digit(f_lst));
	else if (f_lst->f_type == 'u' || f_lst->f_type == 'o' ||
		f_lst->f_type == 'x' || f_lst->f_type == 'X')
		length = (work_out_uxo(f_lst));
	else if (f_lst->f_type == 'b' || f_lst->f_type == 'B')
	{
		f_lst->base = 2;
		length = (work_out_digit(f_lst));
	}
	else if (f_lst->f_type == 'p' || f_lst->f_type == 'P')
	{
		f_lst->f_type = 'x';
		f_lst->hash = '#';
		f_lst->hl = 4;
		f_lst->p = 1;
		length = (work_out_uxo(f_lst));
	}
	if (f_lst->f_type == 'f' || f_lst->f_type == 'F')
		length = (work_out_f(f_lst));
	return (length);
}

int		ft_work_out(t_struct *f_lst)
{
	int length;

	length = 0;
	if (f_lst->f_type == 's' || f_lst->f_type == 'r')
		length = work_out_str(f_lst);
	else if (f_lst->f_type == 'c' || f_lst->f_type == 'C')
		length = work_out_char(f_lst);
	else if (f_lst->f_type == 'd' || f_lst->f_type == 'D' ||
		f_lst->f_type == 'i' || f_lst->f_type == 'I' ||
		f_lst->f_type == 'o' || f_lst->f_type == 'u' ||
		f_lst->f_type == 'x' || f_lst->f_type == 'X' ||
		f_lst->f_type == 'b' || f_lst->f_type == 'B' ||
		f_lst->f_type == 'p' || f_lst->f_type == 'P' ||
		f_lst->f_type == 'f' || f_lst->f_type == 'F')
		length = digit_distribution(f_lst);
	else if (f_lst->f_type == 'O' || f_lst->f_type == 'U')
		length = cap_o_u_work_out(f_lst);
	else if (f_lst->f_type == 'w' || f_lst->f_type == 'W')
		f_lst->fd = va_arg(f_lst->ap, int);
	else
		length = work_out_any_char(f_lst);
	return (length);
}
