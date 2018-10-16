/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   search_regex_invalid.c                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/17 10:26:53 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/11 10:53:48 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**  return 1 -> error
**  return 0 -> ok
*/

static char		**init_tab_error(void)
{
	char		**tabl;

	tabl = NULL;
	if (!(tabl = (char **)malloc(sizeof(char *) * 9)))
		return (NULL);
	tabl[0] = ft_strdup(">>>");
	tabl[1] = ft_strdup("<>");
	tabl[2] = ft_strdup(">|");
	tabl[3] = ft_strdup("<|");
	tabl[4] = ft_strdup("|>");
	tabl[5] = ft_strdup("|<");
	tabl[6] = ft_strdup("><");
	tabl[7] = NULL;
	tabl[8] = NULL;
	return (tabl);
}

static void		error_parsing(char *str, int i)
{
	ft_putstr_fd("21sh: parse error near `", 2);
	ft_putchar_fd(str[i], 2);
	ft_putstr_fd("'\n", 2);
}

static int		test_string(char *line, char **tabl, int i)
{
	int		j;
	int		x;
	int		quit;

	j = 0;
	x = 0;
	while (tabl[j])
	{
		i = 0;
		quit = 0;
		while (line[i] && quit == 0)
		{
			i = echap_quote(line, i, 0);
			if (ft_strlen(line) <= ft_strlen(tabl[j]) + i)
				quit = 1;
			else if (ft_strncmp(line + i, tabl[j], ft_strlen(tabl[j])) == 0)
			{
				error_parsing(line, i);
				return (1);
			}
			i++;
		}
		j++;
	}
	return (0);
}

int				search_regex_invalid(char *line)
{
	int		i;
	char	**tab_error;

	i = 0;
	tab_error = NULL;
	if (!line)
		return (1);
	if (!(tab_error = init_tab_error()))
		return (1);
	if (test_string(line, tab_error, i) == 1)
	{
		tab_error = ft_del_tab(tab_error);
		return (1);
	}
	tab_error = ft_del_tab(tab_error);
	return (0);
}
