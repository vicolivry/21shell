/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putendl_fd.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/03 11:52:56 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/01/15 14:42:05 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int	ft_putendl_fd(char const *s, int fd)
{
	int ret;

	ret = 0;
	if (s != NULL)
	{
		ret += ft_putstr_fd(s, fd);
		ret += ft_putwchar_fd('\n', fd);
	}
	return (ret);
}
