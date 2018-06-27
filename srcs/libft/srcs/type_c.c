/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   type_c.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/15 13:21:29 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/03/15 18:20:18 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static void	ft_width_unicode(t_format *fmt, intmax_t varg)
{
	if (varg <= 0x7FF && varg >= 0x7F)
		fmt->w--;
	else if (varg <= 0xFFFF && varg >= 0x7F)
		fmt->w -= 2;
	else if (varg <= 0x1FFFFF && varg >= 0x7F)
		fmt->w -= 3;
}

void		ft_type_c(t_format *fmt, va_list *va, int *ret)
{
	intmax_t	varg;

	fmt->l = fmt->t == 'C' ? 'l' : fmt->l;
	varg = fmt->t == '%' ? '%' : d_size(va, fmt);
	varg = fmt->mod != ' ' ? fmt->mod : varg;
	ft_width_unicode(fmt, varg);
	*ret += fmt->minus && fmt->l == 'l' ? ft_putwchar(varg) : 0;
	*ret += fmt->minus && fmt->l != 'l' ? ft_putchar(varg) : 0;
	while (fmt->w-- > 1)
		*ret += fmt->zero ? ft_putchar('0') : ft_putchar(' ');
	*ret += !fmt->minus && fmt->l == 'l' ? ft_putwchar(varg) : 0;
	*ret += !fmt->minus && fmt->l != 'l' ? ft_putchar(varg) : 0;
}
