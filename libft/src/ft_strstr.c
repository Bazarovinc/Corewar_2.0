/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 16:27:18 by dheredat          #+#    #+#             */
/*   Updated: 2020/09/22 22:17:48 by ctelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	char	*p_hays;
	char	*p_need;
	int		i;
	int		j;

	p_hays = (char*)haystack;
	p_need = (char*)needle;
	if (!(*(p_need)))
		return (p_hays);
	i = 0;
	while (*(p_hays + i))
	{
		j = 0;
		while (*(p_hays + i + j) == *(p_need + j))
		{
			if (!(*(p_need + ++j)))
				return (p_hays + i);
		}
		i++;
	}
	return (NULL);
}
