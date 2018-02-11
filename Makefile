# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dpolosuk <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/09 13:27:26 by dpolosuk          #+#    #+#              #
#    Updated: 2018/02/11 12:11:32 by dpolosuk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRC = ft_check_for_valid_arg.c \
		ft_fgdamm_functions.c \
		ft_find_grp_own_width.c \
		ft_find_lnk_sz_wdth_blnk.c \
		ft_find_major_minor_width.c \
		ft_ftplos_functions.c \
		ft_is_dir.c \
		ft_ls.c \
		ft_ls_lst_manipulation.c \
		ft_ls_opn_dir.c \
		ft_ls_pf_ell.c \
		ft_lst_merge_sort.c \
		ft_lst_merge_sort_r.c \
		ft_lst_merge_sort_t.c \
		ft_misc_functions.c \
		ft_parse_flags.c \
		ft_path_functions.c \
		ft_print_files_in_dir.c \
		ft_put_file.c \
		ft_sort_files_in_dir.c \
		ft_sort_params.c \

INCLUDE = -I ./includes -I ./lft3.0/lftpf/includes -I ./lft3.0/lft2.0/includes
CFLAGS = -g -Wall -Wextra #-Werror
LIB = -L ./lft3.0/ -lftprintf

OBJ_PATH = ./src/
OBJ = $(addprefix $(OBJ_PATH), $(SRC:.c=.o))

.PHONY: all clean fclean re
all: $(NAME)

$(NAME): $(OBJ)
	@make -C ./lft3.0 all
	@echo library made
	@gcc $(CFLAGS) $(OBJ) $(INCLUDE) $(LIB) -o $(NAME)
	@echo ft_ls made

%.o: %.c
	@gcc $(CFLAGS) -c $< -o $@ $(INCLUDE)

clean:
	@make -C ./lft3.0 clean
	@echo library objectfiles cleaned
	@/bin/rm -f $(OBJ)
	@echo ft_ls objectfiles cleaned

fclean: clean
	@make -C ./lft3.0 fclean
	@echo library name cleaned
	@/bin/rm -f $(NAME)
	@echo ft_ls name cleaned

re: fclean all
