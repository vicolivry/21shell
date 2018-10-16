/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   insert_options_cmd.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/08 11:20:35 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/08 11:23:16 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

static int			inser_options_norm(char ***new, int *len_1, int *len_2)
{
	(*new)[*len_1 + *len_2] = NULL;
	(*new)[*len_1 + *len_2 - 1] = NULL;
	*len_1 = 0;
	*len_2 = 1;
	return (0);
}

char				**insert_option_cmd(char **tab_cmd, char **new_tab,
		int len_1, int len_2)
{
	char	**new;

	new = NULL;
	if (tab_cmd == NULL || new_tab == NULL)
		return (NULL);
	len_1 = ft_len_tab(tab_cmd);
	len_2 = ft_len_tab(new_tab);
	if (!(new = (char **)malloc(sizeof(char *) * (len_1 + len_2 + 1))))
		return (NULL);
	inser_options_norm(&new, &len_1, &len_2);
	while (tab_cmd[len_1])
	{
		if (!(new[len_1] = ft_strdup(tab_cmd[len_1])))
			new[len_1] = NULL;
		len_1++;
	}
	while (new_tab[len_2])
	{
		if (!(new[len_1] = ft_strdup(new_tab[len_2])))
			new[len_1] = NULL;
		len_1++;
		len_2++;
	}
	return (new);
}
