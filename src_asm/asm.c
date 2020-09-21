/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 14:44:05 by dheredat          #+#    #+#             */
/*   Updated: 2020/09/21 11:39:08 by ctelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static void	show_usage(char *name)
{
	write(1, "Usage: ", 8);
	write(1, name, ft_strlen(name));
	write(1, " <sourcefile.s>\n", 17);
	exit(0);
}

static int	ac_checker(int ac, char **av)
{
	if (ac > 2)
		return (ac - 1);
	else if (ac == 1)
		show_usage(av[0]);
	else if (ac == 2)
		return (1);
	return (-1);
}

int			main(int ac, char **av)
{
	t_hero	*hero;
	int		fd;
	int		arg;
	char	*file;

	arg = ac_checker(ac, av);
	if (arg == -1)
		show_usage(av[0]);
	if ((fd = open(av[arg], O_RDONLY)) <= 0)
		ft_quit(-1, 0);
	file = ft_strnewncp(av[arg], ft_strlen(av[arg]));
	hero = init_hero();
	read_file(fd, &hero);
	close(fd);
	translator(hero, file);
	del_hero(&hero);
	return (0);
}
