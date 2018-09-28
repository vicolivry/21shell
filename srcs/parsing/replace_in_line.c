/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   replace_in_line.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/22 11:40:00 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/05 16:11:52 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**  remplace ~ et $ dans line
**	Appeler dans check_validity
*/

static int		insert_str_suite(char **str, char *tmp, int i, int l)
{
	char	*new;
	char	*tmp2;

	new = NULL;
	tmp2 = NULL;
	if (!str || !tmp)
		return (-1);
	new = ft_strsub(*str, i, l);
	ft_replace_word(str, new, tmp);
	ft_strdel(&new);
	return (ft_strlen(tmp));
}

static int		insert_in_str(t_struct *data, char **str, int i)
{
	char	*tmp;
	char	*new;
	int		len;
	int		ret;

	tmp = NULL;
	new = NULL;
	len = 1;
	ret = 1;
	// a delete ?
	if (i > 0 && *str[i] == '$' && *str[i - 1] == '\\')
	{
		printf("(%s) HERE\n", __func__);
		return (-1);
	}
	// end
	if (!(new = ft_strsub(*str, i, ft_strlen(*str) - i)))
		return (1);
	if (new[0] == '~')
		tmp = ft_return_home(data);
	else if (new[0] == '$')
	{
		while (new[len] >= 65 && new[len] <= 90)
			len++;
		if (len > 1)
			tmp = ft_return_dollar(data, new, len);
	}
	ft_strdel(&new);
	if ((ret = insert_str_suite(str, tmp, i, len)) == -1)
		return (-1);
	ft_strdel(&tmp);
	return (ret - 1);
}

static int		return_i_quote(char *tmp, int i, char c)
{
	if (!tmp)
		return (0);
	while (tmp[i] != c)
	{
		i++;
	}
	return (i);
}

static int		replace_in_line_deux(t_struct *data, char **str, int i)
{
	char	*tmp;

	if (!(tmp = ft_strdup(*str)))
		return (1);
	while (tmp[i])
	{
		if (tmp[i] == '\'')
			i = return_i_quote(tmp, i + 1, '\'');
		else if (tmp[i] == '\"')
			i = return_i_quote(tmp, i + 1, '\"');
		else if (tmp[i] == '~' || tmp[i] == '$')
			i = insert_in_str(data, str, i);
		if (i == -1)
		{
			ft_strdel(&tmp);
			return (-1);
		}
		i++;
	}
	ft_strdel(&tmp);
	return (0);
}

int				replace_in_line(t_struct *data, char **line)
{
	char	*tmp;
	int		ret;

	tmp = NULL;
	ret = 0;
	// test
	printf("(%s) line = %s\n", __func__, *line);
	if (line == NULL || ft_strlen(*line) < 1)
	{
		ft_strdel(line);
		return (1);
	}
	if ((ft_strstr(*line, "~") == NULL && ft_strstr(*line, "-") == NULL &&
	ft_strstr(*line, "$") == NULL) || check_regex_classic(data, line) == 0)
		return (0);
	tmp = ft_strdup(*line);
	if (replace_in_line_deux(data, &tmp, 0) == -1)
		ret = -1;
	replace_line(line, tmp);
	ft_strdel(&tmp);
	// test
	printf("line = %s\n", *line);
	if (ret == -1)
		return (0);
	if ((ft_strstr(*line, "~") != NULL || ft_strstr(*line, "$") != NULL) &&
	ft_strstr(*line, "\"") == NULL && ft_strstr(*line, "\'") == NULL)
		replace_in_line(data, line);
	return (ret);
}
