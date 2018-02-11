/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_opn_dir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpolosuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 17:59:44 by dpolosuk          #+#    #+#             */
/*   Updated: 2018/02/11 20:08:40 by dpolosuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

static void		ft_ls_opn_dir_while_else(t_list *ptr, char **path, \
				t_flags *ls_flags)
{
	while (ptr)
	{
		if (ft_is_dir(ptr->content, *path) && ft_strcmp(ptr->content, ".") && \
			ft_strcmp(ptr->content, "..") && ((char*)ptr->content)[0] != '.')
		{
			*path = ft_append_to_path(*path, ptr->content);
			ft_printf("\n%s:\n", *path);
			ft_ls_opn_dir(*path, ls_flags);
			ft_trim_path(*path);
		}
		ptr = ptr->next;
	}
}

static void		ft_ls_opn_dir_while_elseif(t_list *ptr, char **path, \
				t_flags *ls_flags)
{
	while (ptr)
	{
		if (ft_is_dir(ptr->content, *path) && ft_strcmp(ptr->content, ".") && \
			ft_strcmp(ptr->content, ".."))
		{
			*path = ft_append_to_path(*path, ptr->content);
			ft_printf("\n%s:\n", *path);
			ft_ls_opn_dir(*path, ls_flags);
			ft_trim_path(*path);
		}
		ptr = ptr->next;
	}
}

static void		ft_ls_opn_dir_while(t_list *ptr, char **path, t_flags *ls_flags)
{
	if (ls_flags->big_a)
	{
		while (ptr)
		{
			if (ft_is_dir(ptr->content, *path) && \
				ft_strcmp(ptr->content, ".") && \
				ft_strcmp(ptr->content, ".."))
			{
				*path = ft_append_to_path(*path, ptr->content);
				ft_printf("\n%s:\n", *path);
				ft_ls_opn_dir(*path, ls_flags);
				ft_trim_path(*path);
			}
			ptr = ptr->next;
		}
	}
	else if (ls_flags->lit_a)
		ft_ls_opn_dir_while_elseif(ptr, path, ls_flags);
	else
		ft_ls_opn_dir_while_else(ptr, path, ls_flags);
}

static void		ft_ls_readdir(DIR **dir_ptr, t_list **files, char *path, \
				t_flags *ls_flags)
{
	struct dirent	*dir_struct;

	dir_struct = NULL;
	if (ls_flags->lit_t)
	{
		while ((dir_struct = readdir(*dir_ptr)) != NULL)
			ft_put_file_t(dir_struct->d_name, files, path);
	}
	else
	{
		while ((dir_struct = readdir(*dir_ptr)) != NULL)
			ft_put_file(dir_struct->d_name, files);
	}
}

void			ft_ls_opn_dir(char *path, t_flags *ls_flags)
{
	DIR				*dir_ptr;
	t_list			*files;

	files = NULL;
	if (!path)
	{
		dir_ptr = opendir(".");
		path = ft_strdup(".");
	}
	if (!(dir_ptr = opendir(path)))
	{
		ft_print_error(ft_strrchr(path, '/') + 1);
		return ;
	}
	path = ft_put_slash(path);
	ft_ls_readdir(&dir_ptr, &files, path, ls_flags);
	ft_sort_files_in_dir(&files, ls_flags);
	ft_print_files_in_dir(files, ls_flags, path);
	if (ls_flags->big_r)
		ft_ls_opn_dir_while(files, &path, ls_flags);
	ft_strdel(&path);
	ft_lstdel(&files, ft_lstdelfunc);
	closedir(dir_ptr);
	return ;
}
