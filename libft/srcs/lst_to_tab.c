/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lst_to_tab.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/03 17:40:06 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/05/03 17:47:46 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "./libft.h"

char	**lst_to_tab(t_list *lst)
{
	char	**tab;
	t_list	*tmp;
	int		i;

	i = 0;
	tab = NULL;
	tmp = lst;
	while (tmp->next)
	{
		i++;
		tmp = tmp->next;
	}
	if (!(tab = malloc(sizeof(char*) * (i + 1))))
		return (NULL);
	tmp = lst;
	i = 0;
	while (tmp->next)
	{
		tab[i] = ft_strdup(tmp->content);
		tmp = tmp->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
