/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamaris <ddamaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 15:19:33 by ddamaris          #+#    #+#             */
/*   Updated: 2020/09/22 22:17:47 by ctelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <math.h>
# include <float.h>
# include "../libft/inc/libft.h"

# define MAG "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"
# define YELLOW "\033[0;33m"
# define GREEN "\033[0;32m"
# define RED "\033[0;31m"
# define NC "\033[0m"

typedef	struct	s_struct
{
	va_list			ap;
	char			minus;
	char			hash;
	char			zero;
	int				fd;
	int				width;
	int				prec;
	int				hl;
	int				p;
	char			f_type;
	int				base;
	int				size;
	int				len;
	char			sign;
	char			zj;
}				t_struct;

typedef	struct	s_f_struct
{
	char		*m;
	int			ex;
	int			i;
}				t_f_struct;

int				ft_printf(const char *format, ...);
size_t			ft_strlen_k(const char *s);
char			*ft_increase_str(char *s);
int				ft_prn_str(const char *s, int fd);
int				ft_parse(const char *str, t_struct *f_lst);
int				ft_work_out(t_struct *f_lst);
char			*ft_ftoa(t_struct *f_lst, long double *dp, char *s);
char			*f_to_str(t_struct *f_lst, long double nb, char *s);
char			*f_short(t_struct *f_lst, char *s, int l, long double n);
char			*f_long(t_struct *f_lst, char *s, int l, long double n);
void			f_init(t_f_struct *fl, long double f);
char			*f_final(char *s1, char *s2, t_f_struct *fl, int pr);
char			*str_sum(char *res, char *s2);
char			*str_sum_fraction(char *res, char *s2);
char			*str_exp(char *tmp, t_f_struct *fl);
char			*str_div(char *tmp, t_f_struct *fl);
int				is_flag(const char *format, t_struct *f_lst);
int				is_lh(const char *format, t_struct *f_lst);
int				is_prec(const char *f, t_struct *f_lst);
int				is_number(const char *s, t_struct *f_lst);
void			init_flst(t_struct *f_lst);
int				work_out_char(t_struct *f_lst);
int				work_out_any_char(t_struct *f_lst);
int				work_out_str(t_struct *f_lst);
int				work_out_digit(t_struct *f_lst);
int				work_out_uxo(t_struct *f_lst);
int				cap_o_u_work_out(t_struct *f_lst);
int				work_out_f(t_struct *f_lst);
int				len_digit(t_struct *f_lst, long long nb);
int				len_digit_u(t_struct *f_lst, unsigned long long nb);
int				len_number(long long nb, int base);
int				len_number_u(unsigned long long nb, int base);
int				print_before(t_struct *f_lst, long long d);
int				print_before_u(t_struct *f_lst, unsigned long long d);
int				print_f(t_struct *f_lst, char *d);
int				print_digit(t_struct *f_lst, long long d);
int				print_digit_u(t_struct *f_lst, unsigned long long d);
int				print_if_hash(t_struct *f_lst, unsigned long long d);
char			*round_f(char *s);
char			*str_transform(char *src, int l);
int				digit_distribution(t_struct *f_lst);

#endif
