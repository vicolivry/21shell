/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_uitoa_base.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/10 19:18:47 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/02/01 14:51:35 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_uitoa_base(uintmax_t n, int base)
{
	static char	list[] = "0123456789abcdef";
	uintmax_t	temp;
	int			digits;
	char		*output;

	temp = n;
	digits = 1;
	while (temp /= base)
		digits++;
	output = ft_strnew(digits);
	temp = n;
	while (digits--)
	{
		output[digits] = list[temp % base];
		temp /= base;
	}
	return (output);
}
