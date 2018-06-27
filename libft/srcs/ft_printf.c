/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/09 12:13:47 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/03/15 18:19:39 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *format, ...)
{
	va_list		va;
	t_format	param;
	int			ret;

	ret = 0;
	va_start(va, format);
	while (*format)
	{
		while (*format != '%' && *format)
			ret += ft_putchar(*format++);
		if (*format == '%')
		{
			if (!ft_strcmp(format, "%"))
				return (0);
			param = ft_parse(&format, &va);
			ft_modify(param, &va, &ret);
			format++;
		}
	}
	va_end(va);
	return (ret);
}
