/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_delete_struct.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/15 13:57:17 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/10 12:58:23 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**	Delete struct ans datas
*/

int			ft_delete_struct(t_struct **data)
{
	int		ret;

	ret = (*data)->code_erreur;
	(*data)->tab_hash = delete_tab_hash((*data)->tab_hash, (*data)->sizemax);
	(*data)->tab_path = ft_del_tab((*data)->tab_path);
	(*data)->env = ft_del_tab((*data)->env);
	(*data)->builtins = ft_del_tab((*data)->builtins);
	(*data)->env_tmp = ft_del_tab((*data)->env_tmp);
	ft_strdel(&(*data)->path);
	ft_strdel(&(*data)->pwd);
	ft_strdel(&(*data)->oldpwd);
	ft_strdel(&(*data)->home);
	ft_strdel(&(*data)->charfound);
	ft_strdel(&(*data)->current_path);
	ft_strdel(&(*data)->prompt);
	ft_strdel(&(*data)->prompt_current);
	ft_strdel(&(*data)->char_echo);
	(*data)->commandes = clear_ins((*data)->commandes);
	free(*data);
	*data = NULL;
	return (ret);
}
