/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getstat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: akira <akira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 18:47:53 by bsiche            #+#    #+#             */
/*   Updated: 2019/02/15 08:20:41 by akira            ###   ########.fr       */
=======
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 18:47:53 by bsiche            #+#    #+#             */
/*   Updated: 2019/01/12 02:27:17 by bsiche           ###   ########.fr       */
>>>>>>> mjose.merge
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	ft_special(t_ls *info, struct stat *tmp, char *str)
{
	char		*permission;
	char		*symlink;
	char		*fleche;

	permission = ft_usrmode(tmp->st_mode);
	if (permission[0] == 'l')
	{
		symlink = ft_strnew(1025);
		readlink(str, symlink, 1025);
		fleche = ft_strdup("-> ");
		symlink = ft_strjoinfree(fleche, symlink, 3);
		symlink = ft_strjoinfree(symlink, "\0", 1);
		info->symlink = symlink;
	}
<<<<<<< HEAD
//	if (permission[0] == 'c' || permission[0] == 'b')
//	{
//		info->maj = major(tmp->st_rdev);
//		info->min = minor(tmp->st_rdev);
//	}
=======
	if (permission[0] == 'c' || permission[0] == 'b')
	{
		info->maj = major(tmp->st_rdev);
		info->min = minor(tmp->st_rdev);
	}
>>>>>>> mjose.merge
	free(permission);
}

void	ft_stat2(t_ls *info, struct stat *tmp, time_t cur)
{
	info->permission = tmp->st_mode;
	info->size = tmp->st_size;
	if (((cur - tmp->st_mtime) > 15778476) ||
		((tmp->st_mtime - cur) > 15778476))
		info->timeswitch = 1;
	info->hardlink = tmp->st_nlink;
	info->block = tmp->st_blocks;
	info->usrname = tmp->st_uid;
	info->group = tmp->st_gid;
	info->symlink = NULL;
	info->acl = ' ';
	info->maj = 0;
	info->min = 0;
	info->color = 0;
	info->strpad = NULL;
}

void	getattribut(char *path, t_ls *info)
{
	int		i;
	acl_t	acl;

	acl = NULL;
<<<<<<< HEAD
//	acl = acl_get_link_np(path, ACL_TYPE_EXTENDED);
	if (acl != NULL)
		info->acl = '+';
//	i = listxattr(path, NULL, 0, XATTR_NOFOLLOW);
	if (i != 0 && i != -1)
		info->acl = '@';
//	acl_free(acl);
=======
	acl = acl_get_link_np(path, ACL_TYPE_EXTENDED);
	if (acl != NULL)
		info->acl = '+';
	i = listxattr(path, NULL, 0, XATTR_NOFOLLOW);
	if (i != 0 && i != -1)
		info->acl = '@';
	acl_free(acl);
>>>>>>> mjose.merge
	acl = NULL;
}

int		ft_stat(char *path, t_ls *info, char *option)
{
	struct stat		*tmp;
	time_t			cur;
	int				u;

	cur = time(NULL);
	if ((tmp = malloc(sizeof(struct stat) + 1)) == NULL)
		return (-1);
	if (lstat(path, tmp) == -1)
	{
		free(tmp);
		return (-1);
	}
	u = checkoption(option, 'u');
	if (u == 0)
		info->time = tmp->st_mtime;
	if (u == 1)
		info->time = tmp->st_atime;
	ft_stat2(info, tmp, cur);
	ft_special(info, tmp, path);
	if (checkoption(option, '@') == 1)
		getattribut(path, info);
	free(tmp);
	return (0);
}
