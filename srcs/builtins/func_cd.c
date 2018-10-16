/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   func_cd.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <yoginet@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/15 13:21:57 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/15 11:17:14 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**	Change directory
**	~ // - // $ > traiter dans parsing
*/

static int	change_directory(t_struct *data, t_cmd *lst, char *newpath)
{
	if (newpath != NULL)
	{
		if (chdir(newpath) == -1)
		{
			ft_putstr_fd("cd: no such file or directory: ", 2);
			ft_putstr_fd(newpath, 2);
			ft_putstr_fd("\n", 2);
			return (1);
		}
		actualise_env(data, newpath);
	}
	else
	{
		if (chdir(lst->tab_cmd[1]) == -1)
		{
			ft_putstr_fd("cd: no such file or directory: ", 2);
			ft_putstr_fd(lst->tab_cmd[1], 2);
			ft_putstr_fd("\n", 2);
			return (1);
		}
		actualise_env(data, lst->tab_cmd[1]);
	}
	return (0);
}

static int	pwd_replace(t_struct *data, t_cmd *lst)
{
	char	*pwd;
	char	*tmp;
	int		i;

	pwd = NULL;
	tmp = NULL;
	i = 0;
	tmp = ft_check_infos(data->env, "PWD=");
	pwd = ft_strsub(tmp, 4, ft_strlen(tmp) - 4);
	ft_strdel(&tmp);
	if (ft_strstr(pwd, lst->tab_cmd[1]) == NULL)
	{
		ft_putstr_fd("cd: string not in pwd: ", 2);
		ft_putstr_fd(lst->tab_cmd[1], 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	else
	{
		if (ft_replace_word(&pwd, lst->tab_cmd[1], lst->tab_cmd[2]) == 1)
			return (1);
	}
	change_directory(data, lst, pwd);
	ft_strdel(&pwd);
	return (0);
}

static int	check_error_cd(char **tabargv)
{
	int i;

	i = 0;
	while (tabargv[i])
		i++;
	if (i > 3)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (EXIT_FAILURE);
	}
	if (i == 3)
		return (2);
	return (EXIT_SUCCESS);
}

static int	cd_minus(t_struct *data, t_cmd *lst)
{
	change_directory(data, lst, lst->tab_cmd[1]);
	return (0);
}

int			func_cd(t_struct *data, t_cmd *lst)
{
	int mode;

	mode = 0;
	if (!data || !lst)
		return (EXIT_FAILURE);
	if ((mode = check_error_cd(lst->tab_cmd)) == 1)
		return (EXIT_FAILURE);
	if (mode == 2)
		pwd_replace(data, lst);
	else
	{
		if (lst->tab_cmd[1] == NULL)
			change_directory(data, lst, data->home);
		else if (!ft_strcmp(lst->tab_cmd[1], "-"))
		{
			ft_strdel(&lst->tab_cmd[1]);
			lst->tab_cmd[1] = ft_strdup(data->oldpwd);
			cd_minus(data, lst);
		}
		else
			change_directory(data, lst, NULL);
	}
	ft_strdel(&data->pwd);
	data->pwd = ft_return_pwd();
	return (EXIT_SUCCESS);
}
