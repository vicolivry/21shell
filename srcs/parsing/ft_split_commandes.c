/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_split_commandes.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/11 10:11:49 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/03 14:43:31 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**	Retourne une liste chainee avec les differents commande, path, env, fd..
*/

/*
**	Fonction annexe de ft_split_commandes
*/

static int		ft_init_parsing(t_ins **new, char **line, t_struct **data)
{
	char	*tmp;
	int		len;

	tmp = NULL;
	if (ft_nefaitrien(line) == 1)
	{
		(*data)->code_erreur = 258;
        ft_strdel(line);
		return (1);
	}
	len = ft_strlen(*line);
	tmp = ft_strdup(*line);
	if (tmp[len - 1] == ';')
	{
		ft_strdel(line);
		*line = ft_strsub(tmp, 0, len - 1);
	}
	ft_strdel(&tmp);
	if (!(*new = ft_init_ins()))
	{
		*new = clear_ins(*new);
		(*data)->code_erreur = 258;
		return (1);
	}
	return (0);
}

/*
**	Parse en fonction des ;
**	Parse en fonction des pipes et redirections
**	Verifie si les commandes existe, sont accessibles
*/

t_ins			*ft_split_commandes(char **line, t_struct *data)
{
	t_ins	*new_ins;
	t_ins	*cpy;
	char	*tmp;

	cpy = NULL;
	tmp = NULL;
	new_ins = NULL;
	if (*line == NULL || ft_init_parsing(&new_ins, line, &data) == 1)
		return (NULL);
	new_ins = ft_split_pvirgule(line, new_ins, 0, 0);
	cpy = new_ins;
	if (check_error_inlinesplit(&cpy) == 1)
	{
		cpy = clear_ins(cpy);
		return (NULL);
	}
	while (cpy)
	{
		tmp = ft_strdup(cpy->str);
		cpy->cmd = ft_split_cmd(tmp, data);
		cpy = cpy->next;
		ft_strdel(&tmp);
	}
	return (new_ins);
}
