/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   hash_path.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/20 13:59:22 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/10 12:59:56 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**  Source : http://www.cse.yorku.ca/~oz/hash.html (adapter)
**  Taux de collisions : 282 / 1589 (17,74 %)
*/

static int		hash_compression(int sizemax, long hash)
{
	while (hash > (sizemax * 2))
		hash = (hash / 3) + (hash % 13) - 1;
	while (hash > (sizemax - 1))
		hash = (hash / 3) - (hash % 13) + 1;
	if (hash < 0)
		hash *= -1;
	return ((int)hash);
}

long			ft_calcul_hash(char *str, int sizemax)
{
	int		i;
	long	hash;

	i = 0;
	hash = 0;
	while ((i = *str++))
		hash = i + (hash << 6) + (hash << 16) - hash;
	if (hash < 0)
		hash *= -1;
	if (sizemax == 0 || hash < sizemax)
		return (hash);
	else
	{
		while (hash > sizemax)
			hash = hash_compression(sizemax, (long)hash);
	}
	return (hash);
}

/*
**  Creation de la table :
**  On compte le nombre de fichier, on malloc la size * 3
**  On insert les hashs dans la table
*/

int				ft_create_table_hash(t_struct **data)
{
	int		count;

	count = ft_work_in_tab((*data)->tab_path, &ft_count);
	if (count == -1)
		return (-1);
	count *= 3;
	(*data)->tab_hash = create_tab_hash(count);
	if (ft_rforhash(count, (*data)->tab_path, (*data)->tab_hash,
	&ft_calcul_hash) == 0)
		return (count);
	return (-1);
}

/*
**	Allocation de la table et initialisation de celle ci
*/

long			**create_tab_hash(int size)
{
	long	**tabl;
	int		i;

	tabl = NULL;
	i = 0;
	tabl = (long **)malloc(sizeof(long *) * size);
	if (!(tabl))
		return (0);
	while (i < size)
	{
		tabl[i] = (long *)malloc(sizeof(long) * 3);
		tabl[i][0] = 0;
		tabl[i][1] = 0;
		tabl[i][2] = 0;
		i++;
	}
	return (tabl);
}

long			**delete_tab_hash(long **tabh, int size)
{
	int			i;
	t_infos		*clear;

	i = 0;
	clear = NULL;
	if (tabh == NULL)
		return (NULL);
	while (i < size)
	{
		if (tabh[i][0] != 0)
		{
			clear = (t_infos *)tabh[i][1];
			clear = clear_infos(clear);
		}
		free(tabh[i]);
		tabh[i] = NULL;
		i++;
	}
	free(tabh);
	tabh = NULL;
	return (NULL);
}
