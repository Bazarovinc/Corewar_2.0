/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 16:24:32 by dheredat          #+#    #+#             */
/*   Updated: 2020/09/22 22:17:48 by ctelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *dst, const char *src)
{
	unsigned char	*p_dst;
	unsigned char	*p_src;
	int				i;

	p_dst = (unsigned char*)dst;
	p_src = (unsigned char*)src;
	i = 0;
	while (*(p_src + i))
	{
		*(p_dst + i) = *(p_src + i);
		i++;
	}
	*(p_dst + i) = *(p_src + i);
	return (dst);
}
