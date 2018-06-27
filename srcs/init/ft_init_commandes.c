/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_init_commandes.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/11 10:17:46 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/13 12:22:42 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

t_cmd			*ft_init_commandes(void)
{
	t_cmd	*new;

	new = NULL;
	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (new == NULL)
		return (NULL);
	new->rep = NULL;
	new->tab_cmd = NULL;
	new->env = NULL;
	new->next = NULL;
	return (new);
}
