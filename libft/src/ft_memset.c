/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 17:22:19 by dheredat          #+#    #+#             */
/*   Updated: 2020/09/22 22:17:47 by ctelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*bb;
	unsigned char	cc;

	i = 0;
	bb = (unsigned char*)b;
	cc = (unsigned char)c;
	while (i < len)
	{
		bb[i] = cc;
		i++;
	}
	return (b);
}
