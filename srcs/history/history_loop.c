/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 20:41:21 by bsiche            #+#    #+#             */
/*   Updated: 2019/04/26 01:22:03 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		get_last(void)
{
	t_list			*history;
	t_lstcontainer	*list;

	list = g_tracking.mysh->hist;
	if (!list)
		return (0);
	history = ft_lstgetlast(list->firstelement);
	if (!history)
		return (0);
	return (history->index);
}

t_list	*get_hist_nbr(size_t i)
{
	t_list	*history;

	if (!g_tracking.mysh || !g_tracking.mysh->hist)
		return (NULL);
	history = ft_lstgetfirst(g_tracking.mysh->hist->firstelement);
	if (!history)
		return (0);
	if (!history)
		return (0);
	while (history)
	{
		if (history->index == i)
			return (history);
		history = history->next;
	}
	return (history);
}

int		replace_str(size_t i)
{
	t_list	*history;

	history = ft_lstgetfirst(g_tracking.mysh->hist->firstelement);
	if (!history)
		return (0);
	while (history)
	{
		if (history->index == i)
		{
			if (ft_strlen(history->content) > 0)
			{
				clear_screen3();
				print_prompt();
				ft_free(g_tracking.str);
				g_tracking.str = NULL;
				cursor_reset();
				add_to_str(ft_strdup(history->content));
			}
			return (0);
		}
		history = history->next;
	}
	return (0);
}

int		history_up(void)
{
	t_list	*history;

	if (g_tracking.quotes != 0)
		return (0);
	if (g_tracking.histindex > 0)
		g_tracking.histindex--;
	history = get_hist_nbr(g_tracking.histindex);
	if (!history)
		return (0);
	replace_str(history->index);
	return (0);
}

int		history_down(void)
{
	t_list	*history;

	if (g_tracking.quotes != 0)
		return (0);
	if (g_tracking.histindex >= get_last())
	{
		clear_screen3();
		print_prompt();
		ft_free(g_tracking.str);
		g_tracking.str = NULL;
		cursor_reset();
		add_to_str(ft_strdup(g_tracking.tmp_hist));
	}
	g_tracking.histindex++;
	history = get_hist_nbr(g_tracking.histindex);
	if (!history)
		return (0);
	replace_str(history->index);
	return (0);
}
