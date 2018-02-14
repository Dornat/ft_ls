/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpolosuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 13:26:17 by dpolosuk          #+#    #+#             */
/*   Updated: 2018/02/13 16:00:40 by dpolosuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/xattr.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <dirent.h>
# include <ft_printf.h>
# include <errno.h>

# define R_OWN 0400
# define R_GRP 040
# define R_OTH 04
# define W_OWN 0200
# define W_GRP 020
# define W_OTH 02
# define X_OWN 0100
# define X_GRP 010
# define X_OTH 01

# define MAJ_MIN_OFFSET 3

typedef struct		s_flags
{
	unsigned int	lit_a:1;
	unsigned int	big_a:1;
	unsigned int	lit_ell:1;
	unsigned int	lit_f:1;
	unsigned int	lit_r:1;
	unsigned int	big_r:1;
	unsigned int	lit_t:1;
}					t_flags;

typedef struct		s_finfo
{
	char			ftype;
	char			fperms[10];
	unsigned int	fnlinks;
	char			fowner[33];
	char			fgroup[33];
	unsigned int	fsize;
	unsigned int	major;
	unsigned int	minor;
	char			*flmdate_s;
	char			attr;
}					t_finfo;

typedef struct		s_width
{
	unsigned int	link_width;
	unsigned int	size_width;
	unsigned int	block_num;
	unsigned int	own_width;
	unsigned int	grp_width;
	unsigned int	maj_width;
	unsigned int	min_width;
}					t_width;

void				ft_ls(t_list **names, t_flags *ls_flags, t_width *fields_w);
void				ft_ls_opn_dir(char *path, t_flags *ls_flags);

/*
** Parsing
*/

void				ft_parse_flags(int ac, char **av, t_flags *ls_flags, \
					t_list **names);
void				ft_check_for_valid_arg(char **av, int i, int ac);
int					ft_is_dir(char *name, char *path);
int					ft_is_dir_av(char *name, char *path, t_flags *ls_flags);
int					ft_is_dir_wo_path(char *name);

/*
** Path
*/

char				*ft_put_slash(char *path);
char				*ft_append_to_path(char *path, char *name);
void				ft_trim_path(char *path);

/*
** List manipulation
*/

void				ft_put_file(char *name, t_list **files);
void				ft_put_file_t(char *name, t_list **files, char *path);
void				ft_print_files_in_dir(t_list *ptr, t_flags *ls_flags, \
					char *path);
void				ft_sort_lst_ascii(t_list *list);
int					ft_num_of_lst_nodes(t_list *lst);
int					ft_index_of_cur_node(t_list *head, t_list *curr);
void				ft_lst_merge_sort(t_list **head_ref);
void				ft_lst_merge_sort_r(t_list **head_ref);
void				ft_lst_merge_sort_t(t_list **head_ref);
t_list				*ft_lst_sort_merge_t(t_list *a, t_list *b);
void				ft_sort_files_in_dir(t_list **files, t_flags *ls_flags);
int					ft_count_lst_nodes(t_list *ptr);

/*
** Dealing with ell
*/

void				ft_ls_pf_ell(char *file, char *path, t_width *ls_width);
void				ft_ftype(char *file, char *path, t_finfo *f_info);
void				ft_fpermissions(char *file, char *path, t_finfo *f_info);
unsigned int		ft_nlinks(char *file, char *path);
void				ft_fowner(char *file, char *path, t_finfo *f_info);
unsigned int		ft_fsize(char *file, char *path);
int					ft_is_maj_min(char *file, char *path);
unsigned int		ft_fmajor(char *file, char *path);
unsigned int		ft_fminor(char *file, char *path);
void				ft_fgroup(char *file, char *path, t_finfo *f_info);
char				*ft_flmdate_s(char *file, char *path);
size_t				ft_flmdate_i(char *file, char *path);
char				ft_fattr(char *file, char *path);
unsigned int		ft_find_grp_width(t_list *ptr, char *path, \
					t_flags *ls_flags);
unsigned int		ft_find_own_width(t_list *ptr, char *path, \
					t_flags *ls_flags);
unsigned int		ft_find_link_width(t_list *ptr, char *path, \
					t_flags *ls_flags);
unsigned int		ft_find_size_width(t_list *ptr, char *path, \
					t_flags *ls_flags);
unsigned int		ft_find_maj_width(t_list *ptr, char *path, \
					t_flags *ls_flags);
unsigned int		ft_find_min_width(t_list *ptr, char *path, \
					t_flags *ls_flags);
unsigned int		ft_find_block_num(t_list *ptr, char *path, \
					t_flags *ls_flags);
void				ft_ls_pf_norm_file(char *file, t_finfo *f_info, \
					t_width *ls_width);
void				ft_ls_pf_mm_file(char *file, t_finfo *f_info, \
					t_width *ls_width);
void				ft_print_lnk_file(char *file, char *path);

/*
** Dealing with av ell
*/

void				ft_ls_deal_with_favs(t_list *favs, t_flags *ls_flags);
t_list				*ft_put_favtolst(t_list *ptr, t_flags *ls_flags);
int					ft_is_finav(t_list *names, t_flags *ls_flags);
int					ft_chk_lnk_ptr_to_dir(char *path, t_flags *ls_flags);
unsigned int		ft_fav_find_link_width(t_list *favs);
unsigned int		ft_fav_find_size_width(t_list *favs);
unsigned int		ft_fav_find_own_width(t_list *favs);
unsigned int		ft_fav_find_grp_width(t_list *favs);
unsigned int		ft_fav_find_maj_width(t_list *favs);
unsigned int		ft_fav_find_min_width(t_list *favs);

/*
** Misc
*/

void				ft_put_zeroes_to_lsflags(t_flags *ls_flags);
void				ft_print_ls_usage(char c);
void				ft_print_error(char *s);
unsigned int		ft_count_dgts(unsigned int num);
int					ft_fislink(char *file, char *path);
void				ft_sort_params(char **av, int i, int ac);
void				ft_swap_av(char **s1, char **s2);

#endif
