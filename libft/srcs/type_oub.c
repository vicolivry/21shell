/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   type_oub.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/23 12:23:12 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/03/15 18:20:36 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static void	ft_type_oub_pos(t_format *fmt, char *str, int len, int *ret)
{
	if (fmt->w && !fmt->p)
		while (fmt->w-- > len && fmt->w)
			*ret += fmt->zero ? ft_putchar('0') : ft_putchar(' ');
	else if (!fmt->w && fmt->p)
	{
		*ret += fmt->neg ? ft_putchar('-') : 0;
		while (fmt->p-- > len && fmt->p)
			*ret += ft_putchar('0');
	}
	else if (fmt->w && fmt->p)
	{
		while (fmt->w-- && fmt->w >= len && fmt->w >= fmt->p)
			*ret += ft_putchar(' ');
		while (fmt->p-- && fmt->p >= len)
			*ret += ft_putchar('0');
	}
	*ret += (fmt->t == 'o' || fmt->t == 'O') &&
		fmt->hash ? ft_putchar('0') : 0;
	*ret += !ft_strcmp(str, "0") && fmt->p == 0 && fmt->p_val
		? 0 : ft_putstr(str);
}

static void	ft_type_oub_neg(t_format *fmt, char *str, int len, int *ret)
{
	*ret += fmt->plus && !fmt->neg ? ft_putchar('+') : 0;
	if (fmt->p_val)
	{
		*ret += fmt->neg ? ft_putchar('-') : 0;
		while (fmt->p-- > len && fmt->p)
		{
			*ret += ft_putchar('0');
			fmt->w--;
		}
	}
	*ret += (fmt->t == 'o' || fmt->t == 'O') &&
		fmt->hash ? ft_putchar('0') : 0;
	*ret += !ft_strcmp(str, "0") && fmt->p == 0 && fmt->p_val
		&& (fmt->t == 'o' || fmt->t == 'O') ? 0 : ft_putstr(str);
	if (fmt->w_val)
		while (fmt->w-- > len && fmt->w)
			*ret += ft_putchar(' ');
}

void		ft_type_oub(t_format *fmt, va_list *va, int *ret)
{
	char		*str;
	int			len;
	uintmax_t	varg;

	fmt->l = fmt->t == 'O' || fmt->t == 'U' ? 'l' : fmt->l;
	varg = u_size(va, fmt);
	str = fmt->t == 'o' || fmt->t == 'O' ? ft_uitoa_base(varg, 8) : 0;
	str = fmt->t == 'u' || fmt->t == 'U' ? ft_uitoa_base(varg, 10) : str;
	str = fmt->t == 'b' ? ft_uitoa_base(varg, 2) : str;
	len = ft_strlen(str);
	len += fmt->hash && (fmt->t == 'o' || fmt->t == 'O') ? 1 : 0;
	fmt->w += varg == 0 && fmt->p_val ? 1 : 0;
	if (varg == 0 && !fmt->p_val)
		*ret += ft_putchar('0');
	else if (!fmt->minus)
		ft_type_oub_pos(fmt, str, len, ret);
	else
		ft_type_oub_neg(fmt, str, len, ret);
	free(str);
}
