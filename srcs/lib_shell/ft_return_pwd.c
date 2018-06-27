/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_return_pwd.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/06 10:58:38 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/13 12:01:18 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

char		*ft_return_pwd(void)
{
	char	*buf;

	buf = ft_strnew(512);
	buf = getcwd(buf, 512);
	return (buf);
}
