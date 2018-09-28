/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_print_tab.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/26 11:42:26 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/27 13:27:49 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**	Print tab
*/

void		ft_print_tab(char **tabl)
{
	int		i;

	i = 0;
	if (tabl == NULL)
		return ;
	while (tabl[i])
	{
		ft_putendl(tabl[i]);
		i++;
	}
}

/*
**	Print tab for env
*/

static int	its_ok(char *str, char **tabl, int i)
{
	int		len;

	len = 0;
	while (tabl[i])
	{
		len = 0;
		while (str[len] != '=' && str[len])
			len++;
		if (ft_strncmp(str, tabl[i], len) == 0)
			return (1);
		i++;
	}
	return (0);
}

void		ft_print_tab_spe(char **env, char **tabl, int i)
{
	int		j;

	j = 0;
	if (!(env) || !(tabl))
		return ;
	while (env[j])
	{
		if (its_ok(env[j], tabl, i) == 0)
			ft_putendl(env[j]);
		j++;
	}
}
