/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init_struct.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/06 10:39:16 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/07/23 16:16:19 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

static char		**init_env_null(void)
{
	char	**env;
	char	*pwd;

	env = NULL;
	pwd = NULL;
	if (!((char **)malloc(sizeof(char *) * 2)))
		return (NULL);
	if (!(pwd = ft_return_pwd()))
	{
		env = ft_del_tab(env);
		return (NULL);
	}
	env[0] = ft_strjoin("PWD=", pwd);
	env[1] = NULL;
	return (env);
}

static char		**init_env(char **env)
{
	char	**tab_env;

	tab_env = NULL;
	if (!(tab_env = ft_duplicate_tab(env)))
		return (NULL);
	return (tab_env);
}

static void		init_base(t_struct **data)
{
	char	*tmp;

	tmp = ft_check_infos((*data)->env, "PATH=");
	(*data)->pwd = ft_strsub(tmp, 4, ft_strlen(tmp) - 4);
	ft_strdel(&tmp);
	(*data)->oldpwd = ft_strdup((*data)->pwd);
	tmp = ft_check_infos((*data)->env, "HOME=");
	(*data)->home = ft_strsub(tmp, 5, ft_strlen(tmp) - 5);
	ft_strdel(&tmp);
	(*data)->charfound = NULL;
	(*data)->current_path = ft_strdup((*data)->pwd);
	(*data)->prompt = ft_strdup("$> ");
	(*data)->prompt_current = NULL;
	(*data)->char_echo = NULL;
	(*data)->tab_hash = 0;
	(*data)->tab_path = NULL;
	(*data)->builtins = NULL;
	(*data)->env_tmp = NULL;
	(*data)->option_echo = 0;
	(*data)->option_i_env = 0;
	(*data)->code_erreur = 0;
	(*data)->pid = getpid();
	(*data)->sizemax = ft_load_path(data);
}

t_struct		*init_struct(char **env)
{
	t_struct	*data;

	data = (t_struct *)malloc(sizeof(t_struct));
	if (env == NULL)
		data->env = init_env_null();
	else
		data->env = init_env(env);
	init_base(&data);
	data->builtins = ft_initialise_builtins();
	data->commandes = NULL;
	if (data->sizemax == -1)
	{
		ft_delete_struct(&data);
		return (NULL);
	}
	return (data);
}
