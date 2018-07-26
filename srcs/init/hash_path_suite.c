/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   hash_path_suite.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/20 13:59:22 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/07/23 16:13:47 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**	On compte le nombre de fichier a mettre dans la table
*/

int			ft_count(char *path)
{
	DIR				*dir;
	struct dirent	*fl;
	int				i;

	i = 0;
	if (!(dir = opendir(path)))
		return (EXIT_FAILURE);
	while ((fl = readdir(dir)))
		i++;
	closedir(dir);
	return (i);
}

/*
**  Applique une fonction sur l'ensemble du tableau envoyer en parametre
**  Retourne la sommes total
*/

int			ft_work_in_tab(char **tabl, int (*ft)(char *))
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (tabl[i])
	{
		count += (*ft)(tabl[i]);
		i++;
	}
	return (count);
}

/*
**  Boucle liste chainee pour inserer les donnees lors d'une collision
*/

int			ft_insert_collision(t_infos **start, char *tabp, char *str)
{
	while ((*start)->next)
		*start = (*start)->next;
	(*start)->next = init_infos(tabp, str);
	return (0);
}

/*
**	Insert hash dans struct t_infos
*/

int			ft_insert_hash(char *str, int hash, long **tabh, char *tabp)
{
	t_infos		*infos;

	infos = NULL;
	if (tabh[hash][0] == 0)
	{
		tabh[hash][0] = hash;
		infos = init_infos(tabp, str);
		tabh[hash][1] = (long)infos;
	}
	else
	{
		infos = (t_infos *)tabh[hash][1];
		ft_insert_collision(&infos, tabp, str);
	}
	return (0);
}

/*
** Read target (**tab) pour inserer le hash et repertoire
*/

int			ft_rforhash(int s, char **tabp, long **tabh, long (*f)(char *, int))
{
	int				i;
	DIR				*dir;
	struct dirent	*fl;
	long			hash;

	i = 0;
	while (tabp[i])
	{
		if (!(dir = opendir(tabp[i])))
			return (EXIT_FAILURE);
		while ((fl = readdir(dir)))
		{
			hash = 0;
			if (ft_strcmp(fl->d_name, ".") != 0 ||
	ft_strcmp(fl->d_name, "..") != 0)
			{
				hash = (*f)(fl->d_name, s);
				ft_insert_hash(fl->d_name, hash, tabh, tabp[i]);
			}
		}
		closedir(dir);
		i++;
	}
	return (EXIT_SUCCESS);
}
