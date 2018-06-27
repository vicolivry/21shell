/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/19 14:01:12 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/14 09:08:46 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static int		ft_read_file(t_list *lst, int *ret)
{
	char	tmp[BUFF_SIZE_GNL + 1];
	char	*store;

	store = lst->content;
	*ret = read(lst->content_size, tmp, BUFF_SIZE_GNL);
	tmp[*ret] = '\0';
	if (!(lst->content = ft_strjoin(store, tmp)))
		return (0);
	ft_strdel(&store);
	return (1);
}

static t_list	*srch_or_create(unsigned int fd, t_list **lst)
{
	t_list	*tmp;

	tmp = *lst;
	if (tmp == NULL)
	{
		*lst = ft_lstnew("", 1);
		tmp = *lst;
		tmp->content_size = fd;
		return (tmp);
	}
	while (tmp)
	{
		if (tmp->content_size == fd)
			return (tmp);
		if (tmp->next == NULL)
			tmp->next = ft_lstnew("", fd);
		tmp = tmp->next;
	}
	return (*lst);
}

static int		last_line(char **line, t_list **lst)
{
	t_list	*tmp;

	tmp = *lst;
	if (!(*line = ft_strdup(tmp->content)))
		return (-1);
	ft_bzero(tmp->content, ft_strlen(tmp->content));
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	static t_list	*lst = NULL;
	char			*file;
	int				ret;
	t_list			*tmp;

	ret = 1;
	if (!line || fd < 0 || !(tmp = srch_or_create(fd, &lst)))
		return (-1);
	while (ret > 0 && (ft_read_file(lst, &ret)))
		if ((file = ft_strchr(lst->content, '\n')) != NULL)
		{
			*file = '\0';
			if (!(*line = ft_strdup(lst->content)))
				return (-1);
			ft_memmove(lst->content, file + 1, ft_strlen(file + 1) + 1);
			return (1);
		}
	ft_strdel(&file);
	if (ret == 0 && ft_strlen(tmp->content) != 0)
		return ((ret = last_line(&(*line), &tmp)));
	if (!(*line = ft_strnew(0)))
		return (-1);
	return (ret);
}
