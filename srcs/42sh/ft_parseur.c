/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parseur.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 14:39:15 by alsomvil          #+#    #+#             */
/*   Updated: 2019/03/01 15:19:22 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh42.h"

int		its_not_symbol(char c)
{
	if (c == '|' || c == '>' || c == '<' || c == '&' || c == ';')
		return (0);
	else
		return (1);
}

char	*recup_cmd(char *line, int *i, int nb)
{
	char	*test;

	test = NULL;
	if (!line)
		return (NULL);
	while (line[nb] == ' ')
	{
		(*i)++;
		nb++;
	}
	if (line[nb] == '"')
		return (check_quote(&line[nb], 0));
	else if (line[nb] == '$')
	{
		if (line[nb + 1] && line[nb + 1] == '{')
			return (check_bracket(&line[nb], 0, i));
	}
	else if ((test = search_fd_reddir(&line[nb], i)))
		return (test);
	else if ((test = search_reddir(&line[nb], i)))
		return (test);
	else if ((test = search_symboll(&line[nb], i)))
		return (test);
	else
		test = search_normally_arg(&line[nb], i);
	return (test);
}

void	ft_modif_line(char *line)
{
	int		i;
	int		j;
	int		k;
	char	*new_line;
	char	*temp;

	i = 0;
	j = 0;
	new_line = NULL;
	temp = NULL;
	if (ft_valid_quote(line, '"', 0))
	{
		temp = check_quote(line, 0);
		if (temp)
			new_line = ft_strjoin(line, temp);
	}
	if (new_line)
		printf("NEW_LINE = %s\n", new_line);
	else
		printf("LINE = %s\n", line);

	exit (0);
}

t_last	*ft_parseur(char *line)
{
	char	*temp;
	int		i;
	t_last	*list_cmd;
	t_last	*templist;

	i = 0;
	temp = NULL;
	while (line[i] == ' ')
		i++;
	ft_modif_line(line);
	if ((temp = recup_cmd(&line[i], &i, 0)) != NULL)
	{
		list_cmd = create_new_list();
		templist = list_cmd;
		list_cmd->name = temp;
		temp = NULL;
		//ATTENTION !! SEGFAULT ICI DANS LE CAS "dsf
		while (line[i] && (temp = recup_cmd(&line[i], &i, 0)) != NULL)
		{
			list_cmd->next = create_new_list();
			list_cmd->next->prev = list_cmd;
			list_cmd = list_cmd->next;
			list_cmd->name = ft_strdup(temp);
			free(temp);
		}
		list_cmd->next = NULL;
		list_cmd = templist;
	}
	else
		return (NULL);
	//print_last(list_cmd);
	ft_lexeur(list_cmd);
	if (error_lexer(list_cmd))
		return (NULL);
	return (list_cmd);
}
