/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   chose_rep.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/26 13:40:50 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/30 13:05:20 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

int				ft_search_opnext(char *str, int i)
{
	int		len;

	len = ft_strlen(str);
	if (i < len)
	{
		if (str[i] == '<' && str[i + 1] == '<')
			return (5);
		if (str[i] == '>' && str[i + 1] == '>')
			return (3);
		if (str[i] == '>' && str[i + 1] == '&')
			return (9);
	}
	if (str[i] == '|')
		return (1);
	else if (str[i] == '>')
		return (2);
	else if (str[i] == '<')
		return (4);
	else if (str[i] == '&')
		return (4);
	return (0);
}

static int		read_path(char *rep, char *name)
{
	DIR				*dir;
	struct dirent	*fl;
	int				ret;

	ret = 1;
	if ((dir = opendir(rep)) == NULL)
		return (1);
	while ((fl = readdir(dir)) != NULL)
	{
		if (ft_strcmp(fl->d_name, name) == 0)
			ret = 0;
	}
	if (closedir(dir) == -1)
		return (1);
	return (ret);
}

static char		*good_name(char *s1, char *s2)
{
	char		*new;
	char		*tmp;

	new = NULL;
	tmp = NULL;
	if (!(tmp = ft_strjoin(s1, "/")))
		return (NULL);
	if (!(new = ft_strjoin(tmp, s2)))
		return (NULL);
	ft_strdel(&tmp);
	return (new);
}

static int		chose_rep_provisoire(t_cmd **new, char **tmp, int i)
{
	char	*tmp2;
	char	**env_p;

	tmp2 = NULL;
	env_p = NULL;
	i = 0;
	if ((*new)->env == NULL)
		return (0);
	tmp2 = ft_check_infos((*new)->env, "PATH=");
	*tmp = ft_strsub(tmp2, 5, ft_strlen(tmp2) - 5);
	env_p = ft_strsplit(*tmp, ':');
	ft_strdel(tmp);
	ft_strdel(&tmp2);
	while (env_p[i])
	{
		if (read_path(env_p[i], (*new)->tab_cmd[0]) == 0)
		{
			(*new)->rep = good_name(env_p[i], (*new)->tab_cmd[0]);
			env_p = ft_del_tab(env_p);
			return (0);
		}
		i++;
	}
	env_p = ft_del_tab(env_p);
	return (0);
}

int				chose_rep(t_struct *data, t_cmd **new, int provisoire)
{
	char		*tmp;

	tmp = NULL;
	if (provisoire == 1)
	{
		chose_rep_provisoire(new, &tmp, 0);
		ft_strdel(&tmp);
		return (0);
	}
	tmp = ft_return_path((*new)->tab_cmd[0]);
	if (ft_strstr((*new)->tab_cmd[0], "./") != NULL)
		(*new)->rep = ft_strdup((*new)->tab_cmd[0]);
	else if (ft_dir_exist(tmp) == 1)
		(*new)->rep = ft_strdup((*new)->tab_cmd[0]);
	else
		(*new)->rep = ft_search_path((*new)->tab_cmd[0], data);
	ft_strdel(&tmp);
	return (0);
}
