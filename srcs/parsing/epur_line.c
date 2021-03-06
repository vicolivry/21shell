/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   epur_line.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/17 15:29:32 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/16 14:49:47 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**	Supprime les espaces entre
*/

static int		clean_bet_suite(char *str, int i, char **new, char **tmp)
{
	int		q;

	q = 0;
	if (i == ft_strlen(str) || i + 1 == ft_strlen(str))
		return (1);
	if (i + 2 == ft_strlen(str))
		q = 1;
	if ((str[i] == ' ' || str[i] == '\t') && (str[i + 1] == ' ' ||
	str[i] == '\t'))
	{
		*new = ft_strsub(str, 0, i);
		*tmp = ft_strsub(str, i + 1, ft_strlen(str) - (i + 1));
		q = 1;
	}
	return (q);
}

static int		*clean_between(char **string, int i, int q)
{
	char	*tmp;
	char	*new;
	char	*str;

	tmp = NULL;
	new = NULL;
	str = ft_strdup(*string);
	while (q == 0)
	{
		i = echap_quote(str, i, 0);
		q = clean_bet_suite(str, i, &new, &tmp);
		i++;
	}
	if (new && tmp)
	{
		ft_strdel(string);
		*string = ft_strjoin(new, tmp);
	}
	ft_strdel(&tmp);
	ft_strdel(&new);
	ft_strdel(&str);
	if (i + 2 < ft_strlen(*string) && ft_strstr(*string, "  ") != NULL)
		clean_between(string, i, 0);
	return (0);
}

/*
**	Supprime les espaces inutiles
*/

int				clear_line(char **line)
{
	char	*before;
	char	*next;

	before = NULL;
	next = NULL;
	if (*line == NULL)
		return (0);
	if (ft_strstr(*line, " ") == NULL && ft_strstr(*line, "\t") == NULL)
		return (0);
	before = clean_before(*line);
	next = clean_next(before);
	ft_strdel(line);
	*line = ft_strdup(next);
	ft_strdel(&before);
	ft_strdel(&next);
	if ((ft_strstr(*line, "  ") != NULL || ft_strstr(*line, "\t ") != NULL)
	&& ft_strlen(*line) > 1)
		clean_between(line, 0, 0);
	return (0);
}
