/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamaris <ddamaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 15:19:33 by ddamaris          #+#    #+#             */
/*   Updated: 2020/09/21 11:39:08 by ctelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_strlen_k(const char *s)
{
	size_t	i;
	int		res;

	res = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] <= 31 && s[i] > 0)
			res += 3;
		else
			res++;
		i++;
	}
	return (res);
}
