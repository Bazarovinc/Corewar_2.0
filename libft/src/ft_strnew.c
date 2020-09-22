/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamaris <ddamaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 15:19:33 by ddamaris          #+#    #+#             */
/*   Updated: 2020/09/22 22:17:48 by ctelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
