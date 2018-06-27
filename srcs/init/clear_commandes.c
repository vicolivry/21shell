/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   clear_commandes.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/11 10:47:46 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/13 12:21:50 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

t_cmd		*clear_commandes(t_cmd *start)
{
	t_cmd	*clear;
	t_cmd	*cpy;

	clear = start;
	cpy = NULL;
	while (clear)
	{
		ft_strdel(&clear->rep);
		clear->tab_cmd = ft_del_tab(clear->tab_cmd);
		clear->env = ft_del_tab(clear->env);
		cpy = clear;
		clear = clear->next;
		free(cpy);
		cpy = NULL;
	}
	free(clear);
	clear = NULL;
	return (NULL);
}
