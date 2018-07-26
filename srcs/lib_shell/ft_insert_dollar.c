/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_insert_dollar.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/22 11:56:35 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/07/18 09:57:58 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**  replace $ for the path and return len var env
*/

static int		ft_insert_special(t_struct *data, char **str, char **tmp, int i)
{
	int		len;
	int		ret;
	char	*tmp2;

	ret = 1;
	if (!(tmp2 = ft_strdup(*str)))
		return (1);
	len = ft_strlen(*str);
	if (i < len)
	{
		if (tmp2[i] == '$' && tmp2[i + 1] == '?')
		{
			*tmp = ft_itoa_base(data->code_erreur, 10);
			ret = 0;
		}
		else if (tmp2[i] == '$' && tmp2[i + 1] == '$')
		{
			*tmp = ft_itoa(data->pid);
			ret = 0;
		}
	}
	ft_strdel(&tmp2);
	return (ret);
}

char			*ft_insert_dollar(t_struct *data, char **str, int i, int len)
{
	char	*new;
	char	*tmp;

	new = NULL;
	tmp = NULL;
	if (ft_insert_special(data, str, &tmp, i) == 0)
		return (tmp);
	new = ft_strsub(*str, i, len);
	tmp = ft_check_infos(data->env, new + 1);
	ft_strdel(&new);
	if (tmp == NULL)
		return (NULL);
	new = ft_strsub(tmp, 5, ft_strlen(tmp) - 5);
	ft_strdel(&tmp);
	return (new);
}

char			*ft_insert_moins(t_struct *data, char **str, int i, int len)
{
	char	*new;
	char	*tmp;
	int		j;

	j = 0;
	new = NULL;
	tmp = NULL;
	(void)str;
	if (len != 1)
		return (NULL);
	if (i < 3)
		return (NULL);
	if (ft_strstr(*str, "cd -") == NULL)
		return (NULL);
	tmp = ft_check_infos(data->env, "OLDPWD=");
	if (tmp == NULL)
		return (NULL);
	new = ft_strsub(tmp, 7, ft_strlen(tmp) - 7);
	ft_strdel(&tmp);
	return (new);
}

char			*ft_insert_home(t_struct *data, char **str, int i, int len)
{
	char	*new;
	char	*tmp;

	new = NULL;
	tmp = NULL;
	(void)str;
	(void)i;
	(void)len;
	tmp = ft_check_infos(data->env, "HOME=");
	if (tmp == NULL)
		return (NULL);
	new = ft_strsub(tmp, 5, ft_strlen(tmp) - 5);
	ft_strdel(&tmp);
	return (new);
}
