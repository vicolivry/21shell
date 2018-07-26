/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_error_parsing.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/17 10:26:53 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/07/24 11:16:37 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**	Check les cas d'erreur (line non spliter)
**	Check surtout debut de line et fin de line
*/

static void		print_msg_error(char *str, int i)
{
	ft_putstr_fd("21sh: ", 2);
	if (i == 1)
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
	else if (i == 2)
	{
		ft_putstr_fd("syntax error near unexpected token `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\"\n", 2);
	}
	else if (i == 3)
	{
		ft_putstr_fd("command not found: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\n", 2);
	}
}

static int		ft_len_un(char *str)
{
	if (str[0] == '>' || str[0] == '<')
	{
		print_msg_error(str, 1);
		return (1);
	}
	else if (str[0] == '|' || str[0] == '&' || str[0] == ';' || str[0] == '!')
	{
		print_msg_error(str, 2);
		return (1);
	}
	return (0);
}

static int		check_end_line(char *line)
{
	int		len;

	len = ft_strlen(line);
	if (line[len - 1] == '>' || line[len - 1] == '<' || line[len - 1] == '|')
	{
		print_msg_error(line + (len - 1), 2);
		return (1);
	}
	return (0);
}

static int		check_regex_invalid(char *str, int i, int j)
{
	char	*invalid;
	int		ret;

	invalid = ft_strdup("|;\"<>[]{}'!");
	ret = 0;
	while (str[i])
	{
		j = 0;
		while (invalid[j])
		{
			if (invalid[j] == str[i])
				ret = 1;
			j++;
		}
		if (ret == 1)
			ret = 0;
		else
		{
			ft_strdel(&invalid);
			return (0);
		}
		i++;
	}
	print_msg_error(str, 3);
	ft_strdel(&invalid);
	return (1);
}

int				ft_nefaitrien(char **line)
{
    if (ft_strlen(*line) == 0)
        return (1);
	else if (ft_strlen(*line) == 1)
	{
		if (ft_len_un(*line) == 1)
			return (1);
		return (0);
	}
	else if (ft_strstr(*line, "\"") == NULL && ft_strstr(*line, ";;"))
	{
		print_msg_error(*line, 2);
		return (1);
	}
	else if (check_end_line(*line) == 1)
		return (1);
	else if (check_regex_invalid(*line, 0, 0) == 1)
		return (1);
	return (0);
}
