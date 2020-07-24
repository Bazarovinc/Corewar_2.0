/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamaris <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 14:32:21 by ddamaris          #+#    #+#             */
/*   Updated: 2020/07/23 13:51:14 by ctelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

int8_t	get_byte(t_vm *vm, int32_t pc, int32_t step)
{
	return (vm->arena[address_norming(pc + step)]);
}

int32_t				address_norming(int32_t pntr)
{
	return ((pntr < 0) ? ((pntr % MEM_SIZE) + MEM_SIZE) :
			(pntr % MEM_SIZE));
}

static int	is_positive_number(char *string)
{
	int	l;
	char 	*str;

	str = string;
	l = ft_strlen(str);
	if (l <= 11 && ((*str >= '0' && *str <= '9') ||
					(*str == '+' && *(str + 1) != '\0')))
	{
		str++;
		while (*str)
		{
			if (!(*str >= '0' && *str <= '9'))
				return (0);
			str++;
		}
	}
	else
		return (0);
	return (1);
}

int			ft_strtoint(char *str)
{
	long	num;
	char	*s;

	s = str;
	num = 0;
	if (is_positive_number(str))
	{
		if (*s == '+')
			s++;
		while (*s)
			num = num * 10 + (*s++ - '0');
		if (num >= 0 && num <= 2147483647)
			return ((int) num);
	}
	else
		return (-1);
}

int			file_is_cor(char *str, t_vm *vm)
{
	char 	*ext;

	ext = &str[strlen(str) - 4];
	if (!ft_strcmp(ext, ".cor"))
		return (1);
	else
	{
		error_func("r-", "ERROR: Incorrect name of champion file", vm);
		return (0);
	}
}