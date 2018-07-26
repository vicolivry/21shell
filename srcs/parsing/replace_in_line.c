/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   clear_line.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/26 14:57:37 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/07/18 09:56:22 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**  remplace ~, - et $ dans line
*/

static int		insert_in_str(t_struct *data, char **str, int i)
{
	char	*tmp;
	char	*new;
	int		j;

	tmp = NULL;
	if (!(new = ft_strdup(*str)))
		return (1);
	j = i;
	while (new[j] && (new[j] != ' ' || new[j] != '\t'))
		j++;
	ft_strdel(&new);
	if (!(new = ft_strsub(*str, i, j)))
		return (1);
	if (new[0] == '~')
		tmp = ft_insert_home(data, str, i, j - i);
	else if (new[0] == '$')
		tmp = ft_insert_dollar(data, str, i, j - i);
	else if (new[0] == '-')
		tmp = ft_insert_moins(data, str, i, j - i);
	if (ft_replace_word(str, new, tmp) == 0)
		return (0);
	return (1);
}

static int		replace_line(char **line, char *str)
{
	ft_strdel(line);
	if (!(*line = ft_strdup(str)))
		return (1);
	return (0);
}

int				replace_in_line(t_struct *data, char **line)
{
	char	*tmp;
	int		i;
	int		quote;
	int		dquote;

	tmp = NULL;
	i = 0;
	quote = 0;
	dquote = 0;
	if (!(tmp = ft_strdup(*line)))
		return (1);
	while (tmp[i])
	{
		if (tmp[i] == '\'' || tmp[i] == '\"')
		{
			quote = (tmp[i] == '\'' && quote == 0) ? 1 : 0;
			quote = (tmp[i] == '\'' && quote == 1) ? 0 : 1;
			dquote = (tmp[i] == '\"' && dquote == 0) ? 1 : 0;
			dquote = (tmp[i] == '\"' && dquote == 1) ? 0 : 1;
		}
		else if ((tmp[i] == '~' || tmp[i] == '-' || tmp[i] == '$')
				&& (quote == 0 && dquote == 0))
			insert_in_str(data, &tmp, i);
		i++;
	}
	replace_line(line, tmp);
	ft_strdel(&tmp);
	return (0);
}
