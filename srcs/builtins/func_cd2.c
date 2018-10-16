/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   func_cd2.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/08 11:48:06 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/08 15:00:00 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

int	actualise_env(t_struct *data, char *newpath)
{
	int i;

	i = 0;
	ft_strdel(&data->oldpwd);
	data->oldpwd = ft_strdup(data->pwd);
	ft_strdel(&data->pwd);
	data->pwd = ft_strdup(newpath);
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], "PWD=", 4) == 0)
		{
			ft_strdel(&data->env[i]);
			data->env[i] = ft_strjoin("PWD=", data->pwd);
		}
		if (ft_strncmp(data->env[i], "OLDPWD=", 7) == 0)
		{
			ft_strdel(&data->env[i]);
			data->env[i] = ft_strjoin("OLDPWD=", data->oldpwd);
		}
		i++;
	}
	return (0);
}
