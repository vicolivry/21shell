/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putnbr_fd.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/03 11:54:47 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/01/10 20:02:06 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_fd(int n, int fd)
{
	int	ret;

	ret = 0;
	if (n == -2147483648)
		ret += ft_putstr_fd("-2147483648", fd);
	else
	{
		if (n < 0)
		{
			ret += ft_putchar_fd('-', fd);
			n *= -1;
		}
		if (n >= 10)
		{
			ft_putnbr_fd(n / 10, fd);
			n %= 10;
		}
		ret += ft_putchar_fd('0' + n, fd);
	}
	return (ret);
}
