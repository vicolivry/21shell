/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_check_arg_invalid.c                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/20 11:13:22 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/07/20 15:57:14 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**	Compare la commande avec les builtins et renvoie vrai ou faux
*/

static int		compare_builtins(char **builtins, t_cmd *cmd)
{
	int		i;
	int		z;

	i = 0;
	z = 0;
	while (builtins[i])
	{
		z = ft_strcmp(builtins[i], cmd->tab_cmd[0]);
		if (z == 0)
			return (0);
		i++;
	}
	return (1);
}

/*
**	Verifis si on a les droits et si la commandes existe
*/

int			ft_check_arg_invalid(t_struct *data, t_cmd *cmd)
{
	if (cmd == NULL)
		return (1);
	if ((cmd->rep == NULL && cmd->op_redir == 0)
	&& compare_builtins(data->builtins, cmd) == 1)
	{
		basic_error("commande not found: ", cmd->tab_cmd[0]);
		data->code_erreur = 127;
		return (1);
	}
	if (cmd->rep != NULL && ft_access_rep(cmd->rep) != 0)
	{
		basic_error("permission denied: ", cmd->tab_cmd[0]);
		data->code_erreur = 126;
		return (1);
	}
	return (0);
}
