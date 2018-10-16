/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   search_redirection_fd.c                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/10 14:27:41 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/08 10:52:59 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

int				search_fd(char *str, int i)
{
	if (str == NULL)
		return (1);
	if (str[i] == '>')
		i--;
	if (str[i] == '>')
		i--;
	if (ft_isdigit(str[i]) == 1)
	{
		return (str[i] - 48);
	}
	return (1);
}
