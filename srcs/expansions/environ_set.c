/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 08:40:37 by mjose             #+#    #+#             */
/*   Updated: 2019/02/19 06:07:16 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "sh42.h"

void		replace_env_set_str(char *varname, char *varvalue)
{
	t_env_set	*set_env;
	t_env_set	*first;

	if (g_tracking.mysh->setenv_lst == NULL)
		add_to_env_set(varname, varvalue);
	else
	{
		set_env = g_tracking.mysh->setenv_lst;
		first = g_tracking.mysh->setenv_lst;
		while (set_env)
		{
			if (ft_strequ(varname, set_env->param->key))
			{
				ft_strdel(&set_env->param->value);
				set_env->param->value = ft_strdup(varvalue);
				g_tracking.mysh->setenv_lst = first;
				return ;
			}
			if (set_env->next)
				set_env = set_env->next;
			else
			{
				add_to_env_set(varname, varvalue);
				break ;
			}
		}
		g_tracking.mysh->setenv_lst = first;
	}
}

t_env_set	*new_envset(char *varname, char *varvalue)
{
	t_env_set	*env_lst;
	t_keyval	*buf;

	env_lst = NULL;
	buf = NULL;
	buf = (t_keyval *)malloc(sizeof(t_keyval));
	env_lst = (t_env_set *)malloc(sizeof(t_env_set));
	buf->key = ft_strdup(varname);
	buf->value = ft_strdup(varvalue);
	env_lst->param = buf;
	env_lst->next = NULL;

	return (env_lst);
}

void	add_to_env_set(char *varname, char *varvalue)
{
	t_env_set	*env_list;
	t_env_set	*first;
	t_env_set	*new_envvar;

	if (g_tracking.mysh->setenv_lst == NULL)
		g_tracking.mysh->setenv_lst = new_envset(varname, varvalue);
	else
	{
		env_list = g_tracking.mysh->setenv_lst;
		first = g_tracking.mysh->setenv_lst;
		while (env_list && env_list->next)
			env_list = env_list->next;
		new_envvar = new_envset(varname, varvalue);
		env_list->next = new_envvar;
		g_tracking.mysh->setenv_lst = first;
	}
}