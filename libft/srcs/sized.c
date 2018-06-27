/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sized.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/25 14:52:12 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/03/15 18:20:11 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

intmax_t	d_size(va_list *ap, t_format *fmt)
{
	intmax_t nbr;

	nbr = 0;
	if (fmt->l == 'H')
		nbr = (char)va_arg(*ap, int);
	else if (fmt->l == 'h')
		nbr = (short)va_arg(*ap, int);
	else if (fmt->l == 'l')
		nbr = va_arg(*ap, long);
	else if (fmt->l == 'L')
		nbr = va_arg(*ap, long long);
	else if (fmt->l == 'j')
		nbr = va_arg(*ap, intmax_t);
	else if (fmt->l == 'z')
		nbr = va_arg(*ap, size_t);
	else
		nbr = va_arg(*ap, int);
	return (nbr);
}

uintmax_t	u_size(va_list *ap, t_format *fmt)
{
	uintmax_t nbr;

	nbr = 0;
	if (fmt->l == 'H')
		nbr = (unsigned char)va_arg(*ap, int);
	else if (fmt->l == 'h')
		nbr = (unsigned short)va_arg(*ap, int);
	else if (fmt->l == 'l')
		nbr = va_arg(*ap, unsigned long);
	else if (fmt->l == 'L')
		nbr = va_arg(*ap, unsigned long long);
	else if (fmt->l == 'j')
		nbr = va_arg(*ap, uintmax_t);
	else if (fmt->l == 'z')
		nbr = va_arg(*ap, size_t);
	else
		nbr = va_arg(*ap, unsigned int);
	return (nbr);
}
