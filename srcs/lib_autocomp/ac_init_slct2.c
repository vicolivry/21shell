/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ac_init_slct2.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/28 14:21:33 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/28 14:24:37 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

void	fill_commands(t_slct *root, t_info *info)
{
	struct dirent	*dp;
	DIR				*dirp;
	char			**pathes;
	char			*str;
	int				i;

	i = 0;
	str = NULL;
	dp = NULL;
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
