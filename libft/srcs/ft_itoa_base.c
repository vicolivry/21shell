/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_itoa_base.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/05 17:57:32 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/01/29 16:43:13 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_itoa_base(intmax_t n, int base)
{
	static char	list[] = "0123456789abcdef";
	uintmax_t	temp;
	int			digits;
	int			neg;
	char		*output;

	neg = (n < 0 && base == 10 ? 1 : 0);
	temp = n < 0 ? -n : n;
	digits = 1;
	while (temp /= base)
		digits++;
	output = ft_strnew(digits + neg);
	temp = n < 0 ? -n : n;
	while (digits--)
	{
		output[digits + neg] = list[temp % base];
		temp /= base;
	}
	output[0] = neg ? '-' : output[0];
	return (output);
}
