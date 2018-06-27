/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tab_to_lst.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/03 17:30:05 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/05/04 13:22:48 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "./libft.h"

t_list	*tab_to_lst(char **tab)
{
	t_list	*ret;
	t_list	*tmp;
	int		i;

	i = 0;
	if (!tab[0])
		return (NULL);
	ret = ft_lstnew(NULL, 0);
	tmp = ret;
	while (tab[i])
	{
		tmp->content = ft_strdup(tab[i]);
		tmp->next = ft_lstnew(NULL, 0);
		tmp = tmp->next;
		i++;
	}
	return (ret);
}
