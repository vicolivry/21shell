/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exit_status.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/21 13:54:47 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/16 14:45:32 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**	Return l'etat de la derniere commande
*/

int		exit_status(int status)
{
	int		code;

	code = 0;
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		code = WTERMSIG(status);
		if (code == 11)
			ft_putstr_fd("Segmentation fault: 11\n", 2);
		else if (code == 6)
			ft_putstr_fd("Abort: 6\n", 2);
		else if (code == 13)
			ft_putstr_fd("Broken pipe: 13\n", 2);
		return (code + 128);
	}
	else if (WIFSTOPPED(status))
	{
		ft_putstr_fd("Process stopped\n", 2);
	}
	return (0);
}
