/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   func_setenv.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <yoginet@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/15 13:22:35 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/13 12:20:46 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

static int		ft_check_setenv(char *line)
{
	char	**tabl;
	int		ret;

	tabl = NULL;
	ret = 0;
	if (ft_strstr(line, "=") == NULL)
		ret = 1;
	if (ft_strlen(line) < 8)
		ret = 1;
	tabl = ft_strsplit(line, ' ');
	if (ft_len_tab(tabl) != 2)
		ret = 1;
	tabl = ft_del_tab(tabl);
	if (ret == 1)
	{
		ft_putstr_fd("setenv: Invalid format\n", 2);
		return (1);
	}
	return (0);
}

static char		*ft_valid_env(char *line)
{
	char	*str;
	int		i;
	int		q;

	if (ft_check_setenv(line) == 1)
		return (NULL);
	str = ft_strsub(line, 7, ft_strlen(line) - 7);
	i = 0;
	q = 0;
	while (q == 0 && i < ft_strlen(str))
	{
		if (str[i] == '=')
			q = 1;
		else
			str[i] = ft_toupper(str[i]);
		i++;
	}
	return (str);
}

static char		**ft_existe_or_not(t_struct *data, char **str)
{
	char	*tmp;
	int		i;
	int		j;

	tmp = ft_strdup(*str);
	i = 0;
	j = 0;
	while (tmp[i] != '=')
		i++;
	while (data->env[j])
	{
		if (ft_strncmp(data->env[j], tmp, i) == 0)
		{
			ft_strdel(&data->env[j]);
			data->env[j] = ft_strdup(tmp);
			ft_strdel(&tmp);
			ft_strdel(str);
			return (data->env);
		}
		j++;
	}
	ft_strdel(&tmp);
	return (data->env);
}

char			**func_setenv(char **line, t_struct *data)
{
	int		i;
	char	**tmp;
	char	*str;

	i = 0;
	if ((str = ft_valid_env(*line)) == NULL)
		return (data->env);
	data->env = ft_existe_or_not(data, &str);
	if (str == NULL || data->env == NULL)
		return (data->env);
	while (data->env[i])
		i++;
	if (!(tmp = (char **)malloc(sizeof(char *) * (i + 2))))
		return (NULL);
	i = 0;
	while (data->env[i])
	{
		tmp[i] = ft_strdup(data->env[i]);
		i++;
	}
	tmp[i] = ft_strdup(str);
	tmp[i + 1] = NULL;
	ft_del_tab(data->env);
	ft_strdel(&str);
	return (tmp);
}
