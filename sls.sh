#!/bin/bash

ls $@ > ls_diff
./ft_ls $@ > my_diff
#sleep 1
vim -d my_diff ls_diff
#rm diff_ls diff_my
