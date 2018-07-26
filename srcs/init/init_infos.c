/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init_infos.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/25 11:15:29 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/25 11:18:34 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

t_infos			*init_infos(char *rep, char *name)
{
	t_infos		*new;
	char		*tmp;

	new = NULL;
	tmp = NULL;
	new = (t_infos *)malloc(sizeof(t_infos));
	if (!(new))
		return (NULL);
	new->rep = ft_strdup(rep);
	new->name = ft_strdup(name);
	tmp = ft_strjoin(rep, "/");
	new->repname = ft_strjoin(tmp, name);
	ft_strdel(&tmp);
	new->next = NULL;
	return (new);
}

t_infos			*clear_infos(t_infos *start)
{
	t_infos		*cpy;
	t_infos		*clear;

	if (start == NULL)
		return (NULL);
	clear = start;
	cpy = NULL;
	while (clear)
	{
		ft_strdel(&clear->rep);
		ft_strdel(&clear->name);
		ft_strdel(&clear->repname);
		cpy = clear;
		clear = clear->next;
		free(cpy);
		cpy = NULL;
	}
	free(clear);
	clear = NULL;
	return (NULL);
}
