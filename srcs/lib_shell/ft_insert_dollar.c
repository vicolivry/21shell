/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_insert_dollar.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/22 11:56:35 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/22 15:51:06 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**  replace $ for the path and return len var env
*/

static char		*ft_insert_special(t_struct *data, char *str)
{
	char	*tmp;

	tmp = NULL;
	if (ft_strlen(str) < 2)
		return (NULL);
	if (str[0] == '$' && str[1] == '?')
		tmp = ft_itoa_base(data->code_erreur, 10);
	else if (str[0] == '$' && str[1] == '$')
		tmp = ft_itoa(data->pid);
	return (tmp);
}

char			*ft_return_dollar(t_struct *data, char *str, int len)
{
	char	*new;
	char	*tmp;

	new = NULL;
	tmp = NULL;
	if ((tmp = ft_insert_special(data, str)))
		return (tmp);
	if (!(tmp = ft_strsub(str, 1, len - 1)))
		return (NULL);
	new = ft_strjoin(tmp, "=");
	ft_strdel(&tmp);
	tmp = ft_check_infos(data->env, new);
	ft_strdel(&new);
	if (tmp == NULL)
		return (NULL);
	new = ft_strsub(tmp, len, (ft_strlen(tmp) - len));
	ft_strdel(&tmp);
	return (new);
}

char			*ft_return_moins(t_struct *data)
{
	char	*new;
	char	*tmp;

	new = NULL;
	tmp = NULL;
	tmp = ft_check_infos(data->env, "OLDPWD=");
	if (tmp == NULL)
		return (NULL);
	new = ft_strsub(tmp, 7, ft_strlen(tmp) - 7);
	ft_strdel(&tmp);
	return (new);
}

char			*ft_return_home(t_struct *data)
{
	char	*new;
	char	*tmp;

	new = NULL;
	tmp = NULL;
	tmp = ft_check_infos(data->env, "HOME=");
	if (tmp == NULL)
		return (NULL);
	new = ft_strsub(tmp, 5, ft_strlen(tmp) - 5);
	ft_strdel(&tmp);
	return (new);
}
