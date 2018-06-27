/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putwchar_fd.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/03 10:37:15 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/01/15 14:52:42 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include <wchar.h>

int	ft_putwchar_fd(wchar_t c, int fd)
{
	int	i;

	i = 0;
	if (c <= 0x7F)
		i += ft_putchar_fd(c, fd);
	else if (c <= 0x7FF)
	{
		i += ft_putchar_fd(((c >> 6) | 0xC0), fd);
		i += ft_putchar_fd(((c & 0x3F) | 0x80), fd);
	}
	else if (c <= 0xFFFF)
	{
		i += ft_putchar_fd(((c >> 12) | 0xE0), fd);
		i += ft_putchar_fd(((c >> 6) & 0x3F) | 0x80, fd);
		i += ft_putchar_fd(((c & 0x3F) | 0x80), fd);
	}
	else if (c <= 0x1FFFFF)
	{
		i += ft_putchar_fd(((c >> 18) | 0xF0), fd);
		i += ft_putchar_fd(((c >> 12) & 0x3F) | 0x80, fd);
		i += ft_putchar_fd(((c >> 6) & 0x3F) | 0x80, fd);
		i += ft_putchar_fd(((c & 0x3F) | 0x80), fd);
	}
	return (i);
}
