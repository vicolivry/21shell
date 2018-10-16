/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   delete_back_slash.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/03 12:51:18 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/03 13:50:00 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

static int	check_char(char *line, int i)
{
	int		len;

	len = 0;
	if (line == NULL)
		return (0);
	len = ft_strlen(line);
	if (line[i] == '\\')
	{
		if (len > i)
		{
			if (line[i + 1] == '\\')
				return (0);
		}
		return (1);
	}
	return (0);
}

static char	*delete_bs_suite(char *line, int i)
{
	char	*tmp;
	char	*tmp2;
	char	*ret;

	tmp = NULL;
	tmp2 = NULL;
	ret = NULL;
	if (!(tmp = ft_strsub(line, 0, i)))
		return (NULL);
	if (!(tmp2 = ft_strsub(line, i + 1, ft_strlen(line) - (i + 1))))
		return (NULL);
	ret = ft_strjoin(tmp, tmp2);
	ft_strdel(&tmp);
	ft_strdel(&tmp2);
	return (ret);
}

static char	*delete_bs(char *line, int i)
{
	char	*ret;

	ret = NULL;
	while (line[i])
	{
		i = echap_quote(line, i, 0);
		if (check_char(line, i) == 1)
		{
			if (i == 0)
				ret = ft_strsub(line, 1, ft_strlen(line) - 1);
			else if (i == ft_strlen(line))
				ret = ft_strsub(line, 0, ft_strlen(line) - 1);
			else
				ret = delete_bs_suite(line, i);
			return (ret);
		}
		i++;
	}
	return (NULL);
}

int			delete_back_slash(char **line)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	if (ft_strstr(*line, "\\") == NULL)
		return (0);
	tmp = delete_bs(*line, i);
	if (tmp != NULL)
	{
		ft_strdel(line);
		*line = ft_strdup(tmp);
	}
	ft_strdel(&tmp);
	return (0);
}
