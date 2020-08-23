/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamaris <ddamaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 15:19:33 by ddamaris          #+#    #+#             */
/*   Updated: 2020/07/23 13:51:15 by ctelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strnew(size_t size)
{
	char *sn;

	if (size + 1 == 0)
		return (NULL);
	sn = (char *)malloc(sizeof(char) * size + 1);
	if (sn)
		ft_bzero(sn, size + 1);
	return (sn);
}

char	*ft_increase_str(char *s)
{
	char	*dst;
	int		i;
	int		l;

	l = ft_strlen(s) + 1;
	dst = (char *)malloc(sizeof(char) * (l + 1));
	dst[0] = '1';
	i = 0;
	while (++i < l)
		dst[i] = s[i - 1];
	free(s);
	return (dst);
}
