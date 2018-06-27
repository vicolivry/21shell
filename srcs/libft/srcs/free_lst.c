/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   free_lst.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/15 12:45:35 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/05/15 12:47:39 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "./libft.h"

void	free_lst(t_list *lst)
{
	t_list	*tmp;
	t_list	*tmp2;

	tmp = lst;
	while (tmp)
	{
		tmp2 = tmp->next;
		ft_memdel((void**)&tmp->content);
		ft_memdel((void**)&tmp);
		tmp = tmp2;
	}
}
