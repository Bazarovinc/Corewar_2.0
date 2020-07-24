/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_champion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamaris <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 11:27:21 by ddamaris          #+#    #+#             */
/*   Updated: 2020/07/23 13:51:15 by ctelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

unsigned char	*read_str(int fd, size_t len, t_vm *vm)
{
	size_t			size;
	unsigned char	*tmp;

	tmp = (unsigned char *)ft_strnew(len);
	size = read(fd, tmp, len);
	if (size == -1)
	{
		free (tmp);
		error_func("r-", "ERROR: Can't open champion file", vm);
	}
	if (size < len)
	{
		free(tmp);
		error_func("r-", "ERROR: Invalid champion file", vm);
	}
	return (tmp);
}

static void		check_zero(int fd, t_vm *vm)
{
	char		*str;

	str = read_str(fd, 4, vm);
	if (!(str[0] == 0 && str[1] == 0 && str[2] == 0 && str[3] == 0))
	{
		free(str);
		error_func("r-", "ERROR: No null control bytes", vm);
	}
}
static int 			parse_code_size(int fd, t_vm *vm)
{
	unsigned char	*str;
	int32_t			res;

	res = 0;
	str = read_str(fd, 4, vm);
	res = str[3] + str[2] * 256 + str[1] * 65536 + str[0] * 16777216;
	if (res > CHAMP_MAX_SIZE)
		error_func("r-", "ERROR: Invalid code size", vm);
	return (res);
}

void				parse_champion(int fd, t_player *player, t_vm *vm)
{
	unsigned char	*str;

	str = read_str(fd, 4, vm);
	if (!(str[0] == 0 && str[1] == 234 && str[2] == 131 && str[3] == 243))
	{
		free(str);
		error_func("r-", "ERROR: Invalid magic header", vm);
	}
	player->name = read_str(fd, PROG_NAME_LENGTH, vm);
	check_zero(fd, vm);
	player->code_size = parse_code_size(fd, vm);
	player->comment = read_str(fd, COMMENT_LENGTH, vm);
	check_zero(fd, vm);
	player->code = read_str(fd, player->code_size, vm);
}
