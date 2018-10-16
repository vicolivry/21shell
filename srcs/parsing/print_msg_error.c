/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print_msg_error.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/11 13:43:49 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/16 14:53:09 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**	Fonction pour imprimer des msg d'erreur
*/

void		print_msg_error(char *str, int i)
{
	ft_putstr_fd("21sh: ", 2);
	if (i == 1)
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
	else if (i == 2)
	{
		ft_putstr_fd("syntax error near unexpected token `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\"\n", 2);
	}
	else if (i == 3)
	{
		ft_putstr_fd("command not found: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\n", 2);
	}
}
