/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_check_arg_invalid.c                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/20 11:13:22 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/16 14:45:46 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**  Dans le cs de redirection vers un mauvais fd, on retourne une erreur
*/

static int		check_bad_fd(t_cmd *lst)
{
	if (lst == NULL)
		return (0);
	if (lst->bad_fd == 1)
		return (1);
	if (lst->stdout_cmd == -1 || lst->stderr_cmd == -1)
		return (1);
	return (0);
}

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
**	Verifie si on a les droits et si la commandes existe
*/

int				ft_check_arg_invalid(t_struct *data, t_cmd *cmd)
{
	if (cmd == NULL)
		return (1);
	if (cmd->rep == NULL && compare_builtins(data->builtins, cmd) == 1)
	{
		basic_error("commande not found: ", cmd->tab_cmd[0]);
		data->code_erreur = 127;
		return (1);
	}
	if (cmd->rep != NULL && ft_access_rep(cmd->rep, 3) != 0)
	{
		basic_error("permission denied: ", cmd->tab_cmd[0]);
		data->code_erreur = 126;
		return (1);
	}
	if (check_bad_fd(cmd) == 1)
	{
		data->code_erreur = 1;
		return (1);
	}
	return (0);
}
