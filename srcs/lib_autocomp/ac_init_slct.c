/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ac_init_slct.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/27 17:49:41 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/05 18:27:50 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

static void	fill_commands(t_slct *root, t_info *info)
{
	struct dirent	*dp;
	DIR				*dirp;
	char			**pathes;
	char			*str;
	int				i;

	i = 0;
	str = NULL;
	str = getenv("PATH");
	pathes = ft_strsplit(str, ':');
	while (pathes[i])
	{
		if ((dirp = opendir(pathes[i])) != NULL)
		{
			while ((dp = readdir(dirp)) != NULL)
				if (dp->d_name[0] != '.' &&
						contains_letters(dp->d_name, info->letters))
					ac_add_queue(root, dp);
			closedir(dirp);
		}
		ft_strdel(&pathes[i]);
		i++;
	}
	free(pathes);
}

static void	fill_dir(t_slct *root, t_info *info, char *line, char **table)
{
	struct dirent	*dp;
	DIR				*dirp;

	if (info->letters && !ft_strcmp(table[0], info->letters))
		ft_strdel(&info->letters);
	if (!line)
		line = ft_strdup("./");
	else if (line && !ft_strchr(line, '/'))
	{
		ft_strdel(&line);
		line = ft_strdup("./");
	}
	if ((dirp = opendir(line)) != NULL)
	{
		while ((dp = readdir(dirp)) != NULL)
		{
			if (dp->d_name[0] != '.' &&
					contains_letters(dp->d_name, info->letters))
				ac_add_queue(root, dp);
		}
		closedir(dirp);
	}
	if (line)
		ft_strdel(&line);
}

static int	is_cmd(char *cmd, char **pathes)
{
	struct dirent	*dp;
	DIR				*dirp;
	int				i;

	i = -1;
	while (pathes[++i])
	{
		if ((dirp = opendir(pathes[i])) != NULL)
		{
			while ((dp = readdir(dirp)) != NULL)
				if (!ft_strcmp(dp->d_name, cmd))
				{
					while (pathes[i])
						ft_strdel(&pathes[i++]);
					closedir(dirp);
					return (1);
				}
			closedir(dirp);
		}
		ft_strdel(&pathes[i]);
	}
	free(pathes);
	return (0);
}

static char	**fill_pathes(void)
{
	char			**pathes;
	char			*str;

	str = NULL;
	str = getenv("PATH");
	pathes = ft_strsplit(str, ':');
	return (pathes);
}

t_slct		*init_slct(char *line, t_info *info, t_hist *hist)
{
	t_slct			*root;
	char			**table;
	int				i;
	char			**pathes;

	i = 0;
	table = NULL;
	pathes = fill_pathes();
	if (hist->name)
		table = ft_strsplit(hist->name, ' ');
	if (!(root = root_slct()) || !line || !table)
		return (NULL);
	if (!(table[1]) && hist->name && last_char(hist->name) != ' ' &&
			last_char(hist->name) != '/')
		fill_commands(root, info);
	else if (is_cmd(table[0], pathes) || last_char(hist->name) == '/')
		fill_dir(root, info, line, table);
	free_tab(table);
	free_tab(pathes);
	if (root->next != root)
		return (root);
	else
		return (NULL);
}
