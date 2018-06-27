/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putwchar.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/28 17:45:15 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/01/15 14:19:55 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include <wchar.h>

int	ft_putwchar(wchar_t c)
{
	int	i;

	i = 0;
	if (c <= 0x7F)
		i += ft_putchar(c);
	else if (c <= 0x7FF)
	{
		i += ft_putchar((c >> 6) | 0xC0);
		i += ft_putchar((c & 0x3F) | 0x80);
	}
	else if (c <= 0xFFFF)
	{
		i += ft_putchar((c >> 12) | 0xE0);
		i += ft_putchar(((c >> 6) & 0x3F) | 0x80);
		i += ft_putchar((c & 0x3F) | 0x80);
	}
	else if (c <= 0x1FFFFF)
	{
		i += ft_putchar((c >> 18) | 0xF0);
		i += ft_putchar(((c >> 12) & 0x3F) | 0x80);
		i += ft_putchar(((c >> 6) & 0x3F) | 0x80);
		i += ft_putchar((c & 0x3F) | 0x80);
	}
	return (i);
}
