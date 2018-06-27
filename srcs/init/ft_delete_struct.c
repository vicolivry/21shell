/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_delete_struct.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/15 13:57:17 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/13 12:22:07 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**	Delete struct ans datas
*/

void			ft_delete_struct(t_struct *data)
{
	ft_strdel(&data->path);
	ft_strdel(&data->pwd);
	ft_strdel(&data->oldpwd);
	ft_strdel(&data->home);
	ft_strdel(&data->charfound);
	ft_strdel(&data->current_path);
	ft_strdel(&data->prompt);
	ft_strdel(&data->prompt_current);
	ft_strdel(&data->char_echo);
	data->tab_path = ft_del_tab(data->tab_path);
	data->env = ft_del_tab(data->env);
	data->builtins = ft_del_tab(data->builtins);
	data->env_tmp = ft_del_tab(data->env_tmp);
	free(data);
	data = NULL;
}
