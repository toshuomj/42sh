/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 19:41:54 by bsiche            #+#    #+#             */
/*   Updated: 2019/01/13 23:16:00 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh42.h"

void	begin_paste(void)
{
	char	*tmp;

	tmp = ft_strdup(g_tracking.cpaste->line);
	if (g_tracking.cpaste->line)
		add_to_str(tmp);
}
