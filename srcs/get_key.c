/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_key.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 03:05:45 by bsiche            #+#    #+#             */
/*   Updated: 2018/12/02 05:23:02 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	ft_return(void)
{
	g_tracking.cmd = ft_strdup(g_tracking.str);
	free(g_tracking.str);
	cursor_reset();
	g_tracking.str = ft_strnew(0);
}

int		ft_exec_key(char *str)
{
	if (ft_strcmp(str, K_LEFT) == 0)
		move_left();
	if (ft_strcmp(str, K_RIGHT) == 0)
		move_right();
	if (ft_strcmp(str, K_UP) == 0)
	{
		g_tracking.pos->abs -= g_tracking.terminfo->sizex;
	}
	if (ft_strcmp(str, K_DOWN) == 0)
	{
		g_tracking.pos->abs += g_tracking.terminfo->sizex;
	}
	if (ft_strcmp(str, K_DEL) == 0)
		rem_from_str();
	return (1);
}

int		is_cmd(char *str)
{
	int		i;
	t_list	*tmp;
	int		flag;

	i = ft_strlen(str);
	tmp = g_tracking.key_list->firstelement;
	flag = 0;
	while (tmp)
	{
		if (ft_strncmp(str, tmp->content, i) == 0)
			flag++;
		if (strlen(tmp->content) == i && ft_strncmp(str, tmp->content, i) == 0)
			return (ft_exec_key(str));
		tmp = tmp->next;
	}
	if (flag == 0)
		return (3);
	return (0);
}

int	single_key(char c)
{
	if (c == K_BKSP)
	{
		rem_from_str();
		return (1);
	}
	if (c == 10 || c == 13)
	{
		ft_return();
		g_tracking.swi = 1;
		return (1);
	}
	if (c == K_TAB)
	{
		ft_putnbr(g_tracking.swi);
		sleep(2);
		return (1);
	}
	return (0);
}

void	readloop(void)
{
	char	c;
	char	*str;
	int		i;

	str = ft_strnew(2);
	i = 0;
	read(STDERR_FILENO, &c, 1);
	str = ft_strjoinchar(str, c, 1);
	i = single_key(c);
	if (c < 32)
	{
		while (i == 0)
		{
			read(STDERR_FILENO, &c, 1);
			str = ft_strjoinchar(str, c, 1);
			i = is_cmd(str);
			if (i == 3)
				break ;
		}
	}
	if (i == 1)
		free(str);
	else
		add_to_str(str);
}

int		get_key(void)
{
	char	*test;

	ft_putstr(g_tracking.prompt);
	while (g_tracking.swi == 0)
	{
		readloop();
	}
	return (1);
}