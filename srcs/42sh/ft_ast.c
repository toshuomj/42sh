/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ast.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 02:25:05 by alsomvil          #+#    #+#             */
/*   Updated: 2019/02/15 10:03:16 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/sh42.h"

#define ORDER g_tracking.mysh->order
#define EXEC g_tracking.mysh->exec

t_tree		*new_branch(void)
{
	t_tree	*tree;

	tree = ft_memalloc(sizeof(t_tree));
	tree->name = NULL;
	tree->cmd = NULL;
	tree->prev = NULL;
	tree->right = NULL;
	tree->left = NULL;
	return (tree);
}

void		create_ast(t_tree *tree, t_tab_arg *tab_arg)
{
	t_tab_arg	*temp;
	t_tab_arg	*temp_left;
	t_tab_arg	*temp_right;

	temp = NULL;
	temp_left = tab_arg;
	while (tab_arg->next)
		tab_arg = tab_arg->next;
	while (tab_arg->prev)
	{
		if ((temp == NULL) && tab_arg->type == OP)
		{
			temp = tab_arg;
		}
		/*else if (tab_arg->type == OP)
		{
			if (tab_arg->tab_test[0][0] == ';' || tab_arg->tab_test[0][0] == '&')
				temp = tab_arg;
		}*/
		tab_arg = tab_arg->prev;
	}
	if (temp)
	{
		if (temp->prev)
			temp->prev->next = NULL;
		temp_right = temp->next;
		temp_right->prev = NULL;
	}
	else
	{
		tree->name = ft_strdup(tab_arg->tab_test[0]);
		tree->cmd = tab_arg->tab_test;
		return ;
	}
	tree->type = temp->type;
	tree->name = ft_strdup(temp->tab_test[0]);
	tree->cmd = temp->tab_test;
	if (temp_left)
	{
		tree->left = new_branch();
		tree->left->prev = tree;
		create_ast(tree->left, temp_left);
	}
	if (temp_right)
	{
		tree->right = new_branch();
		tree->right->prev = tree;
		create_ast(tree->right, temp_right);
	}
	return ;
}

void		init_ast(void)
{
	g_tracking.mysh->exec = ft_memalloc(sizeof(t_exec));
	g_tracking.mysh->exec->left = NULL;
	g_tracking.mysh->exec->right = NULL;
	g_tracking.mysh->exec->sym = NULL;
}

void		ft_ast(t_tab_arg *tab_arg)
{
	t_tree	*tree;
	pid_t	gpid;
	pipe(descrf);
	pipe(descrf_two);

	tree = new_branch();
	create_ast(tree, tab_arg);
	init_ast();
	execute_ast(tree,tab_arg);
	//exit (0);
	add_to_exec(1);
	if (EXEC->ret == 0)
		exec_command();
	ORDER = NULL;
	return ;
}
