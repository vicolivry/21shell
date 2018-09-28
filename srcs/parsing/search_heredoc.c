/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   search_heredoc.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/28 11:34:39 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/30 10:03:01 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

static int	ft_return_heredoc(char *str, char **tmp, int i, int opt)
{
	int		j;
	int		len;

	j = i;
	len = ft_strlen(str) - 1;
	while (str[i] == ' ')
		i++;
	while (str[i])
	{
		if (opt == 1 && (i == len || (str[i] == ' ' || str[i] == '|' ||
	str[i] == '>' || str[i] == '<')))
		{
			*tmp = ft_strsub(str, j, i - j + 1);
			return (i);
		}
		if (opt == 2 && (i == len || (str[i] == '>' && str[i + 1] == '>')))
		{
			*tmp = ft_strsub(str, j, i - j + 1);
			return (i);
		}
		i++;
	}
	return (len + 1);
}

static char	**heredoc_simple(char *str, int i, int *j)
{
	char	*tmp;
	char	**new;

	tmp = NULL;
	new = NULL;
	*j = ft_return_heredoc(str, &tmp, i, 1);
	if (tmp == NULL)
		return (NULL);
	if (!(new = (char **)malloc(sizeof(char *) * 2)))
		return (NULL);
	new[0] = ft_strdup(tmp);
	new[1] = NULL;
	ft_strdel(&tmp);
	return (new);
}

static char	**heredoc_yg(char *str, int i, int *j)
{
	char	*tmp;
	char	**new;

	tmp = NULL;
	new = NULL;
	*j = ft_return_heredoc(str, &tmp, i, 2);
	new = ft_strsplit(tmp, ' ');
	ft_strdel(&tmp);
	return (new);
}

int			search_heredoc(t_cmd **lst, char *str, int i, int j)
{
	char	*tmp;

	tmp = NULL;
	if (!lst || !str)
		return (-1);
	if ((*lst)->op_next == 4)
		(*lst)->heredoc = heredoc_simple(str, i, &j);
	else if ((*lst)->op_next == 5)
		(*lst)->heredoc = heredoc_yg(str, i + 1, &j);
	ft_strdel(&tmp);
	return (j);
}
