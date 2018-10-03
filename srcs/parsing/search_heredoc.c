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

/*
** cat << test auteur
** on va jusqu'a test et si il reste des arguments, on les passes en parametre de la fonction
*/

static int	len_heredoc(char *str)
{
	int		i;
	int		len;

	i = 0;
	if (!str)
		return (0);
	len = ft_strlen(str);
	while (str[i] && i != len)
	{
		if (str[i] == '<' && str[i + 1] == '<')
		{
			i += 2;
			if (str[i] == ' ')
			{
				while (str[i] == ' ' || str[i] == '\t')
					i++;
			}
			while (str[i] && (str[i] != ' ' || str[i] != '\t'))
				i++;
			return (i);
		}
		i++;
	}
	return (i);
}

// A proteger

static int	add_params(t_cmd **lst, char *str, int j)
{
	char	*tmp;
	char	**tabl;
	int		i;

	tmp = NULL;
	tabl = NULL;
	i = 0;
	tmp = ft_strsub(str, j, ft_strlen(str) - j);
	tabl = ft_strsplit(str, ' ');
	while (tabl[i])
	{
		increase_tab(&(*lst)->tab_cmd);
		(*lst)->tab_cmd[i + 1] = ft_strdup(tabl[i]);
		i++;
	}
	ft_strdel(&tmp);
	tabl = ft_del_tab(tabl);
	return (0);
}

int			search_heredoc(t_cmd **lst, char *str, int i, int j)
{
	if (!lst || !str)
		return (-1);
	if ((*lst)->op_next == 4)
		(*lst)->heredoc = heredoc_simple(str, i, &j);
	else if ((*lst)->op_next == 5)
	{
		(*lst)->line = ft_strdup(str);
		(*lst)->heredoc_str = heredoc();
		j = len_heredoc(str);
		add_params(lst, str, j);
	}
	change_prompt(&g_info, 0);
	ft_strdel(&(*lst)->line);
	return (j);
}
