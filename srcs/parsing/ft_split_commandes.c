/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_split_commandes.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/11 10:11:49 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/07/24 10:26:44 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**	Tous le parsing de line est fait ici
**	Retourne une liste chainee avec les differents commande, path, env, fd..
**
**	Difference entre && et ;
**	&& -> si la premiere commande echoue, la 2eme ne se fait pas
**	; -> si la premiere commande echoue, la 2 eme se fait
*/

/*
**	Fonction annexe de ft_split_commandes
*/

static int		ft_init_parsing(t_ins **new, char **line)
{
	char	*tmp;
	int		len;

	tmp = NULL;
	if (ft_nefaitrien(line) == 1)
		return (1);
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
	if (ft_init_parsing(&new_ins, line) == 1)
		return (NULL);
	new_ins = ft_split_pvirgule(*line, new_ins);
	ft_strdel(line);
	cpy = new_ins;
	if (check_error_inlinesplit(&cpy) == 1)
	{
		cpy = clear_ins(cpy);
		return (NULL);
	}
	while (cpy)
	{
		tmp = ft_strdup(cpy->str);
		if (cpy->str != NULL)
			cpy->cmd = ft_split_cmd(tmp, data);
		cpy = cpy->next;
	}
	return (new_ins);
}
