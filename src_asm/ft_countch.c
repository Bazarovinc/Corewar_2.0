/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 16:36:53 by dheredat          #+#    #+#             */
/*   Updated: 2020/09/21 11:39:08 by ctelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int	ft_countch(const char *str, int c)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == c)
			res++;
		i++;
	}
	return (res);
}
