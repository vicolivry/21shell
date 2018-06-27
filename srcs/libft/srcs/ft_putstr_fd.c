/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putstr_fd.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/03 12:10:35 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/01/23 12:27:23 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_fd(const char *s, int fd)
{
	int		ret;

	ret = 0;
	if (s != NULL)
	{
		while (*s)
		{
			ret += ft_putwchar_fd(*s, fd);
			s++;
		}
	}
	return (ret);
}
