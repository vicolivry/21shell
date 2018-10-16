/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   redirection_fd.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/23 11:22:16 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/16 14:48:01 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**	Agregateur de descripteur de fichier
*/

int			redirection_fd(t_cmd *data)
{
	if (data->stdout_cmd != 1)
		dup2(data->stdout_cmd, 1);
	if (data->stderr_cmd != 2)
		dup2(data->stderr_cmd, 2);
	return (0);
}
