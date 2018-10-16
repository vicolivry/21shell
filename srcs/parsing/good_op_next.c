/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   good_op_next.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/23 13:01:15 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/16 14:51:52 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**  Retourne le code du bon operateur
*/

int					good_op_next(t_cmd **lst, char *str, int i)
{
	int		ret;

	ret = 0;
	if (i >= ft_strlen(str))
		return (1);
	if (str[i] == '|' && (str[i + 1] != '|' && str[i + 1] != '\0'))
		(*lst)->op_next = 1;
	else if (str[i] == '>' && str[i + 1] != '>' && str[i + 1] != '&')
		(*lst)->op_next = 2;
	else if ((str[i] == '>' || str[i] == '<') && str[i + 1] == '&')
		(*lst)->op_next = 9;
	else if (str[i] == '>' && str[i + 1] == '>')
		(*lst)->op_next = 3;
	else if (str[i] == '<' && str[i + 1] != '<')
		(*lst)->op_next = 4;
	else if (str[i] == '<' && str[i + 1] == '<')
		(*lst)->op_next = 5;
	else if (str[i] == '&' && str[i + 1] == '&')
		(*lst)->op_next = 7;
	else if (str[i] == '|' && str[i + 1] == '|')
		(*lst)->op_next = 8;
	return (0);
}

/*
** Si redirection et apres pipe, change code operateur
*/

void				verifie_op(t_cmd **lst, char *str, int i)
{
	if (lst == NULL || str == NULL || i > ft_strlen(str))
		return ;
	if ((*lst)->op_next == 2 || (*lst)->op_next == 3)
	{
		if (str[i] == '|')
			(*lst)->op_next = 1;
	}
}
