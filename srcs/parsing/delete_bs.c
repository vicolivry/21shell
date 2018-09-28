/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   delete_bs.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/05 11:29:57 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/05 16:11:54 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

static int		return_i(char *str, int i)
{
	if (str[i] == '\'')
	{
		while (str[i] || str[i] != '\'')
			i++;
	}
	else if (str[i] == '\"')
	{
		while (str[i] || str[i] != '\"')
			i++;
	}
	return (i);
}

static int		check_before_after(char **str, int i)
{
	char	*tmp;

	tmp = NULL;
	if (i == 0 || i == ft_strlen(*str) - 1)
	{
		if (i == 0)
			tmp = ft_strsub(*str, 1, ft_strlen(*str) - 1);
		else
			tmp = ft_strsub(*str, 0, ft_strlen(*str) - 1);
		if (tmp == NULL)
			return (1);
		ft_strdel(str);
		if (!(*str = ft_strdup(tmp)))
			return (1);
		ft_strdel(&tmp);
		return (2);
	}
	return (0);
}

static int		delete_char(char **str, int i)
{
	char	*tmp;
	char	*tmp2;

	tmp = NULL;
	tmp2 = NULL;
	if (check_before_after(str, i) > 1)
		return (1);
	if (!(tmp = ft_strsub(*str, 0, i)))
		return (1);
	if (!(tmp2 = ft_strsub(*str, i + 1, ft_strlen(*str) - (i + 1))))
		return (1);
	ft_strdel(str);
	if (!(*str = ft_strjoin(tmp, tmp2)))
		return (1);
	ft_strdel(&tmp);
	ft_strdel(&tmp2);
	return (0);
}


/*
**	Si dollar apres \ on met $MACHIN entre cote
*/

static int		clear_bs_suite(char **line, int i)
{
	char	*tmp;
	char	*tmp2;

	tmp = NULL;
	tmp2 = NULL;
	if (!(tmp = ft_strdup(*line)))
		return (1);
	if (tmp[i + 1] == '$')
	{
		// a voir
		//return (0);
		// end
		tmp[i] = '\"';
		i++;
		while (tmp[i] && tmp[i] != ' ' && tmp[i] != '\t')
			i++;
		tmp2 = ft_strsub(tmp, 0, i);
		ft_strdel(&tmp);
		tmp = ft_strsub(*line, i, ft_strlen(*line) - i);
		ft_strdel(line);
		*line = ft_strjoin(tmp2, "\"");
		ft_strdel(&tmp2);
		tmp2 = ft_strjoin(*line, tmp);
		ft_strdel(line);
		*line = ft_strdup(tmp2);
		ft_strdel(&tmp);
		ft_strdel(&tmp2);
	}
	else
		delete_char(line, i);
	ft_strdel(&tmp);
	return (0);
}

static int		clear_bs(char **line, int i)
{
	char	*str;

	str = NULL;
	if (!(str = ft_strdup(*line)))
		return (1);
	if (str == NULL || i >= ft_strlen(str))
	{
		ft_strdel(&str);
		return (0);
	}
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			i = return_i(str, i + 1);
		else if (str[i] == '\\')
		{
			clear_bs_suite(line, i);
			ft_strdel(&str);
			if (i < ft_strlen(*line) - 1)
				clear_bs(line, i + 1);
			return (0);
		}
		i++;
	}
	ft_strdel(&str);
	return (0);
}

/*
**	Clear \
*/

int				delete_bs(char **line)
{
	char	*tmp;

	tmp = NULL;
	// a delete
	printf("(%s) LINE = %s\n", __func__ ,*line);
	if (!(*line))
		return (1);
	if (ft_strlen(*line) <= 1)
		return (0);
	if (ft_strstr(*line, "\\") == NULL)
		return (0);
	clear_bs(line, 0);
	// a delete
	printf("LINE = %s\n", *line);
	return (0);
}
