/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   type_x.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/23 12:13:10 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/03/15 18:21:04 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static void	print_x(int *ret, t_format *fmt, char *str)
{
	if (ft_strcmp(str, "0") && fmt->hash)
	{
		*ret += fmt->t == 'X' ? ft_putstr("0X") : 0;
		*ret += fmt->t == 'x' ? ft_putstr("0x") : 0;
	}
	fmt->t = ' ';
}

static void	follow_x_pos(t_format *fmt, char *str, int len, int *ret)
{
	if (fmt->w_val && fmt->p_val)
	{
		while (fmt->w-- && fmt->w >= fmt->p && fmt->w >= len)
			*ret += ft_putchar(' ');
		print_x(ret, fmt, str);
		while (fmt->p-- && fmt->p >= len)
			*ret += ft_putchar('0');
	}
	else
		print_x(ret, fmt, str);
	*ret += !ft_strcmp(str, "0") && fmt->p <= 0 && fmt->p_val
		? 0 : ft_putstr(str);
}

static void	ft_type_x_pos(t_format *fmt, char *str, int len, int *ret)
{
	if (fmt->w_val && !fmt->p_val)
	{
		while (!fmt->zero && fmt->w-- > len && fmt->w)
			*ret += ft_putchar(' ');
		print_x(ret, fmt, str);
		while (fmt->w-- > len && fmt->w && fmt->zero)
			*ret += ft_putchar('0');
	}
	else if (!fmt->w_val && fmt->p_val)
	{
		print_x(ret, fmt, str);
		while (fmt->p-- > len && fmt->p)
			*ret += ft_putchar('0');
	}
	else
	{
		follow_x_pos(fmt, str, len, ret);
		return ;
	}
	*ret += !ft_strcmp(str, "0") && fmt->p <= 0 && fmt->p_val
		? 0 : ft_putstr(str);
}

static void	ft_type_x_neg(t_format *fmt, char *str, int len, int *ret)
{
	*ret += fmt->plus && !fmt->neg ? ft_putchar('+') : 0;
	if (fmt->p)
	{
		*ret += fmt->neg ? ft_putchar('-') : 0;
		while (fmt->p-- > len && fmt->p)
		{
			*ret += ft_putchar('0');
			fmt->w--;
		}
	}
	print_x(ret, fmt, str);
	*ret += !ft_strcmp(str, "0") && fmt->p <= 0 && fmt->p_val
		? 0 : ft_putstr(str);
	if (fmt->w)
		while (fmt->w-- > len && fmt->w)
			*ret += ft_putchar(' ');
}

void		ft_type_x(t_format *fmt, va_list *va, int *ret)
{
	char		*str;
	int			len;
	uintmax_t	varg;
	int			i;

	i = 0;
	varg = u_size(va, fmt);
	str = ft_uitoa_base(varg, 16);
	if (fmt->t == 'X')
		while (str[i])
		{
			str[i] = ft_toupper(str[i]);
			i++;
		}
	len = ft_strlen(str);
	len += fmt->hash && varg != 0 && fmt->p <= 0 ? 2 : 0;
	len = !ft_strcmp(str, "0") ? 0 : len;
	fmt->w -= fmt->hash && fmt->p <= fmt->w && fmt->p_val ? 2 : 0;
	if (!fmt->minus)
		ft_type_x_pos(fmt, str, len, ret);
	else
		ft_type_x_neg(fmt, str, len, ret);
	free(str);
}
