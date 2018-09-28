/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_line_vide.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/26 12:06:01 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/05 11:58:20 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

static int	suite_vide(char *str, int i)
{
	while (str[i] == ' ' || str[i] == '\"' || str[i] == '\'')
		i++;
	if (i == ft_strlen(str))
	{
		basic_error(" ", " : command not found");
		return (0);
	}
	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != ';')
			return (1);
		i++;
	}
	return (0);
}

static int	other_check(char *str, t_struct **data)
{
	if (ft_strlen(str) == 1 && str[0] == ';')
	{
		(*data)->code_erreur = 258;
		ft_putstr_fd("21sh: syntax error near unexpected token `;'\n", 2);
		return (1);
	}
	if (ft_strlen(str) == 1 && str[0] == '.')
	{
		(*data)->code_erreur = 2;
		ft_putstr_fd("21sh: .: filename argument required\n", 2);
		return (1);
	}
	return (0);
}

int			ft_check_line_vide(char *str, t_struct **data)
{
	int		i;

	i = 0;
	if (str == NULL || ft_strlen(str) == 0)
		return (0);
	if (other_check(str, data) == 1)
		return (0);
	if (ft_strstr(str, "\"") == NULL && ft_strstr(str, "\'") == NULL)
	{
		if (ft_strstr(str, ";;") != NULL)
		{
			(*data)->code_erreur = 258;
			ft_putstr_fd("21sh: syntax error near unexpected token `;;'\n", 2);
			return (0);
		}
	}
	return (suite_vide(str, i));
}
