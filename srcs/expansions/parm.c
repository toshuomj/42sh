/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 06:10:07 by mjose             #+#    #+#             */
/*   Updated: 2019/01/29 07:36:51 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

int		is_to_add_or_mod_parm(char *to_transf)
{
	int		i;

	i = 0;
	while (to_transf[i])
	{
		if (to_transf[i] == '$')
			return (0);
		if (to_transf[i] == '=')
			return (1);
	}
	return (0);
}

int		have_parm(char *to_transf)
{
	int		i;
	int		to;

	i = 0;
	while (to_transf[i])
	{
		if (to_transf[i] == '$' && to_transf[i + 1] == '{')
		{
			to = i;
			while (to_transf[to])
			{
				if (to_transf[to] == '}')
					return (1);
				to++;
			}
		}
		i++;
	}
	return (0);
}