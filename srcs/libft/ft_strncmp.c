/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 17:28:08 by bsiche            #+#    #+#             */
/*   Updated: 2019/01/07 18:09:00 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str;
	unsigned char	*str2;

	i = 0;
	str = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while ((str[i] || str2[i]) && i < n)
	{
		if (str[i] != str2[i])
			return (str[i] - str2[i]);
		i++;
	}
	return (0);
}

int		ft_strncmplc(const char *s1, const char *s2, size_t n)
{
	char	*cmp1;
	char	*cmp2;
	int		i;

	cmp1 = ft_strdup(s1);
	cmp2 = ft_strdup(s2);
	i = 0;
	while (cmp1[i])
	{
		cmp1[i] = ft_tolower(cmp1[i]);
		i++;
	}
	i = 0;
	while (cmp2[i])
	{
		cmp2[i] = ft_tolower(cmp2[i]);
		i++;
	}
	i = ft_strncmp(cmp1, cmp2, n);
	free(cmp1);
	free(cmp2);
	return (i);
}