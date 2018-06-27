/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   type_p.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/29 15:57:55 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/03/15 18:20:43 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static void	follow_p_pos(t_format *fmt, char *str, int len, int *ret)
{
	if (fmt->w_val && fmt->p_val)
	{
		while (fmt->w-- && fmt->w >= fmt->p && fmt->w >= len)
			*ret += ft_putchar(' ');
		*ret += ft_putstr("0x");
		while (fmt->p-- && fmt->p >= len)
			*ret += ft_putchar('0');
	}
	else
		*ret += ft_putstr("0x");
	*ret += !ft_strcmp(str, "0") && fmt->p <= 0 && fmt->p_val
		? 0 : ft_putstr(str);
}

static void	ft_type_p_pos(t_format *fmt, char *str, int len, int *ret)
{
	if (fmt->w_val && !fmt->p_val)
	{
		while (!fmt->zero && fmt->w-- > len && fmt->w)
			*ret += ft_putchar(' ');
		*ret += ft_putstr("0x");
		while (fmt->w-- > len && fmt->w && fmt->zero)
			*ret += ft_putchar('0');
	}
	else if (!fmt->w_val && fmt->p_val)
	{
		*ret += ft_putstr("0x");
		while (fmt->p-- > len && fmt->p)
			*ret += ft_putchar('0');
	}
	else
	{
		follow_p_pos(fmt, str, len, ret);
		return ;
	}
	*ret += !ft_strcmp(str, "0") && fmt->p <= 0 && fmt->p_val
		? 0 : ft_putstr(str);
}

static void	ft_type_p_neg(t_format *fmt, char *str, int len, int *ret)
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
	*ret += ft_putstr("0x");
	*ret += !ft_strcmp(str, "0") && fmt->p <= 0 && fmt->p_val
		? 0 : ft_putstr(str);
	if (fmt->w)
		while (fmt->w-- > len && fmt->w)
			*ret += ft_putchar(' ');
}

void		ft_type_p(t_format *fmt, va_list *va, int *ret)
{
	char		*str;
	int			len;
	uintmax_t	varg;
	int			i;

	i = 0;
	fmt->l = 'l';
	varg = u_size(va, fmt);
	str = ft_uitoa_base(varg, 16);
	if (fmt->t == 'X')
		while (str[i])
		{
			str[i] = ft_toupper(str[i]);
			i++;
		}
	len = ft_strlen(str);
	len += varg != 0 && fmt->p <= 0 ? 2 : 0;
	len = !ft_strcmp(str, "0") ? 0 : len;
	fmt->p += !ft_strcmp(str, "0") && fmt->p > 0 ? 1 : 0;
	fmt->w -= (fmt->p <= fmt->w && fmt->p_val) || !varg ? 2 : 0;
	if (!fmt->minus)
		ft_type_p_pos(fmt, str, len, ret);
	else
		ft_type_p_neg(fmt, str, len, ret);
	free(str);
}
