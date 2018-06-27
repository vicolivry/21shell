/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lst_dup.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/03 16:46:56 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/05/03 16:54:50 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "./libft.h"

t_list	*lst_dup(t_list *lst1)
{
	t_list	*tmp;
	t_list	*tmp2;
	t_list	*lst2;

	lst2 = ft_lstnew(NULL, 0);
	tmp = lst1;
	tmp2 = lst2;
	while (tmp->next)
	{
		tmp2->content = ft_strdup(tmp->content);
		tmp = tmp->next;
		tmp2->next = ft_lstnew(NULL, 0);
		tmp2 = tmp2->next;
	}
	return (lst2);
}
