/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ac_init_slct.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/27 17:49:41 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/27 17:50:22 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

static int	contains_letters(char *name, char *letters)
{
	int	i;

	i = 0;
	if (!letters)
		return (1);
	else 
	while (letters[i])
	{
		if (name[i] != letters[i])
			return (0);
		i++;
	}
	return (1);
}

t_slct	*init_slct(char *line, t_info *info)
{
	t_slct			*root;
	struct dirent	*dp;
	DIR				*dirp;

	if (!line || !ft_strchr(line, '/'))
		line = ft_strdup(".");
	if (!(root = root_slct()))
		return (NULL);
	if ((dirp = opendir(line)) != NULL)
	{
		while ((dp = readdir(dirp)) != NULL)
			if (dp->d_name[0] != '.' && contains_letters(dp->d_name, info->letters))
				ac_add_queue(root, dp);
		closedir(dirp);
	}
	else
	{
		ft_strdel(&line);
		return (NULL);
	}
	ft_strdel(&line);
	if (root->next != root)
		return (root);
	else
		return (NULL);
}
