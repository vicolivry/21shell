/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   search_redirection_fd.c                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/10 14:27:41 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/27 12:13:50 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

int				search_fd(char *str, int i)
{
	if (str == NULL)
		return (1);
	if (i == 0 || i < 2 || i + 1 == ft_strlen(str) || str[i] != '>')
		return (1);
	if (ft_isdigit(str[i - 1]) == 1)
	{
		return (str[i - 1] - 48);
	}
	return (1);
}
