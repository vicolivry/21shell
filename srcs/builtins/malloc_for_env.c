/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   malloc_for_env.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/27 16:26:33 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/11 16:31:31 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

char			**malloc_for_env_deux(t_struct **data, t_cmd **lst, int i)
{
	char		**new;
	int			len;
	int			x;

	new = NULL;
	len = 0;
	x = 0;
	while ((*data)->env[len])
		len++;
	len += (i + 1);
	if (!(new = (char **)malloc(sizeof(char *) * len)))
		return (NULL);
	new[len - 1] = NULL;
	if (malloc_for_env_suite(&new, *data, *lst, 1) == 1)
	{
		new = ft_del_tab(new);
		return (NULL);
	}
	new[len - 1] = NULL;
	return (new);
}

char			**malloc_for_env(t_struct **data, t_cmd **lst, int i, int opt)
{
	char		**new;
	int			len;
	int			x;

	new = NULL;
	len = 0;
	x = 0;
	if (opt == 0)
		return (new = malloc_for_env_deux(data, lst, i));
	len = i + 1;
	if (!(new = (char **)malloc(sizeof(char *) * len)))
		return (NULL);
	new[len - 1] = NULL;
	i = 0;
	while (ft_strcmp((*lst)->tab_cmd[i], "env") == 0 ||
			ft_strcmp((*lst)->tab_cmd[i], "-i") == 0)
		i++;
	while ((*lst)->tab_cmd[i] && ft_strstr((*lst)->tab_cmd[i], "=") != NULL)
	{
		new[x] = ft_strdup((*lst)->tab_cmd[i]);
		i++;
		x++;
	}
	new[x] = NULL;
	return (new);
}
