/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ac_parse_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/27 17:30:43 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/28 15:02:56 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

static char	*letters(char *line, t_info *info, char *tmp, int len)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (i < len)
	{
		tmp[i] = line[i];
		i++;
	}
	tmp[i] = 0;
	while (i < ft_strlen(line))
	{
		info->letters[j] = line[i];
		j++;
		i++;
	}
	ft_strdel(&line);
	line = ft_strdup(tmp);
	ft_strdel(&tmp);
	return (line);
}

static char	*get_letters(char *line, t_info *info)
{
	char	*tmp;
	int		len;

	len = ft_strlen(line) - 1;
	tmp = NULL;
	if (line == NULL || !ft_strcmp(line, ""))
		return (NULL);
	if (!ft_strchr(line, '/'))
	{
		info->letters = ft_strdup(line);
		return (line);
	}
	if (last_char(line) == '/')
		return (line);
	while (line[len - 1] != '/')
		len--;
	if (!(tmp = malloc(len)))
		return (NULL);
	if (!(info->letters = malloc(ft_strlen(line) - len)))
		return (NULL);
	return (letters(line, info, tmp, len));
}

char		*get_last_word(char *line, t_info *info)
{
	char	**table;
	t_list	*lst;
	t_list	*tmp;

	if (line == NULL || !ft_strcmp(line, ""))
		return (NULL);
	if ((table = ft_strsplit(line, ' ')) == NULL)
		return (NULL);
	lst = tab_to_lst(table);
	tmp = lst;
	while (tmp->next->next != NULL)
		tmp = tmp->next;
	ft_strdel(&line);
	line = ft_strdup(tmp->content);
	free_lst(lst);
	line = get_letters(line, info);
	return (line);
}
