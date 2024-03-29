/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_lst_options.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 15:14:07 by hdufer            #+#    #+#             */
/*   Updated: 2019/04/27 20:41:48 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char	*create_path_hist(void)
{
	char	*path;
	char	*user;

	path = ft_strdup("/Users/");
	user = getlogin();
	path = ft_strjoinfree(path, user, 1);
	path = ft_strjoinfree(path, "/.42hist", 1);
	return (path);
}

void	print_history(void)
{
	t_list	*tmp;
	char	*buf;

	tmp = ft_lstgetfirst(g_tracking.mysh->hist->firstelement);
	if (!tmp)
		return ;
	while (tmp)
	{
		buf = tmp->content;
		ft_putnbr(tmp->index + 1);
		ft_putstr(": ");
		ft_putendl(buf);
		tmp = tmp->next;
	}
	return ;
}

void	hist_file_to_lst(void)
{
	int		fd;
	char	*line;
	char	*path;
	int		t;

	line = NULL;
	path = create_path_hist();
	fd = open(path, O_CREAT | O_RDWR, 00777);
	ft_free(path);
	if (fd < 0)
		ft_putendl_fd("Error while opening/creating .42hist", 2);
	if (g_tracking.mysh->hist == NULL)
		g_tracking.mysh->hist = lstcontainer_new();
	while ((t = get_next_line(fd, &line)) == 1 && line != NULL)
	{
		if (ft_strcmp(line, "\n") != 0 && ft_strlen(line) > 0 && line[0] > 32)
			lstcontainer_add(g_tracking.mysh->hist, ft_strdup(line));
		if (line)
			ft_free(line);
		line = NULL;
	}
	ft_free(line);
	line = NULL;
	close(fd);
}
