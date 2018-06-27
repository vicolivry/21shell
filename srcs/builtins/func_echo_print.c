/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   func_echo_print.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/11 14:02:38 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/13 12:18:12 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**	Print char or go to print special char
*/

static int		ft_print_echo_suite(char *str, int i, int len, int quote)
{
	if ((str[i] == '\'' || str[i] == '\"') && quote == 1)
		ft_putchar(str[i]);
	else if ((str[i] == '\\') && quote == 1)
	{
		ft_print_special(str, i, len);
		return (2);
	}
	else if (str[i] > 31)
		ft_putchar(str[i]);
	return (1);
}

/*
**	print env or string and epur ' & "
*/

static int		ft_quote_zero(char *str, int i, t_struct *data)
{
	if (str[i] == '\'')
		data->char_echo = ft_strdup("\'");
	else if (str[i] == '\"')
		data->char_echo = ft_strdup("\"");
	return (1);
}

static int		ft_quote_one(char *str, int i, t_struct *data)
{
	if (str[i] == data->char_echo[0])
	{
		ft_strdel(&data->char_echo);
		return (0);
	}
	else
		ft_putchar(str[i]);
	return (1);
}

void			ft_print_echo(char *str, t_struct *data, size_t len)
{
	int		quote;
	int		i;

	quote = 0;
	i = 0;
	len = ft_strlen(str);
	while (str[i])
	{
		if ((str[i] == '\"' || str[i] == '\'') && quote == 0)
			quote = ft_quote_zero(str, i, data);
		else if ((str[i] == '\"' || str[i] == '\'') && quote == 1)
			quote = ft_quote_one(str, i, data);
		else
		{
			if (str[i] == '$')
				i += ft_search_env(str, i, data, 0);
			else
			{
				i += ft_print_echo_suite(str, i, (int)len, quote);
				data->option_echo = 0;
			}
			i--;
		}
		i++;
	}
}
