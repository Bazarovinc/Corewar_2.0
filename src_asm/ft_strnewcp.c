/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnewcp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 16:30:09 by dheredat          #+#    #+#             */
/*   Updated: 2020/09/21 11:39:08 by ctelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

char	*ft_strnewncp(const char *str, size_t len)
{
	size_t	i;
	char	*res;

	i = 0;
	if (!(res = ft_strnew(len + 1)))
		return (NULL);
	while (i < len && str[i])
	{
		res[i] = str[i];
		i++;
	}
	if (i != len)
	{
		ft_strdel(&res);
		return (NULL);
	}
	return (res);
}
