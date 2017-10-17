# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: curquiza <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/16 17:08:05 by curquiza          #+#    #+#              #
#    Updated: 2017/10/17 12:32:02 by sfranc           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 42sh

CC = gcc -g -Wall -Wextra -Werror
#CC = gcc -Wall -Wextra -Werror -fsanitize=address

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

LIB = -L$(LIBFT_DIR) -lft -ltermcap
INCL = -I includes -I $(LIBFT_DIR)/includes

################################################################################
################################## RESOURCES ###################################
################################################################################

SRC = srcs

C_DIR = $(addprefix $(SRC)/, \
	  read_line \
	  lexer \
	  parser \
	  ast \
	  execution \
	  shell)


C_FILES = $(addprefix $(SRC)/, \
	  $(READLINE) \
	  $(LEXER) \
	  $(PARSER) \
	  $(AST) \
	  $(EXEC) \
	  $(MAIN)) 

READLINE = $(addprefix read_line/, \
		   init_reset.c \
		   move_left_right.c \
		   move_up_down.c \
		   move_start_end.c \
		   move_word.c \
		   insert_char.c \
		   copy_cut.c \
		   delete.c \
		   clear.c \
		   replace_cursor.c \
		   ctrl_d.c \
		   completion.c \
		   compl_init_reset.c \
		   compl_get_words.c \
		   compl_matches.c \
		   compl_ascii_sort.c \
		   compl_display.c \
		   histo_add_line.c \
		   histo_up_down.c \
		   ctrl_r.c \
		   interpreter.c \
		   read_line.c)

LEXER = $(addprefix lexer/, \
	  lex_list.c \
	  lex_list_del.c \
	  lexer.c \
	  lexer_token_type.c \
	  lexer_op_type.c)

PARSER = $(addprefix parser/, \
	  parser.c \
	  syntax_error.c \
	  inhibitor.c \
	  inhibitor_check.c \
	  inhibitor_get_endoftoken.c \
	  here_doc.c \
	  here_doc_get_lines.c)

AST = $(addprefix ast/, \
	  build_ast.c \
	  create_delete.c \
	  ast.c)

EXEC = $(addprefix execution/, \
	  semantics.c \
	  sem_split.c \
	  sem_redir_list.c \
	  expansion.c \
	  exp_tilde.c \
	  exp_parameter.c \
	  exp_quote_removal.c \
	  built_in.c \
	  built_in_flags.c \
	  built_in_echo.c \
	  built_in_cd.c \
	  built_in_env.c \
	  built_in_setenv.c \
	  built_in_unsetenv.c \
	  built_in_exit.c \
	  built_in_set.c \
	  built_in_unset.c \
	  built_in_export.c \
	  execution.c \
	  exec_apply_ctrl_op.c \
	  exec_simple_cmd.c \
	  exec_error_msg.c \
	  exec_cmd.c \
	  exec_redirection.c \
	  exec_ass_word.c \
	  exec_cmd_return.c)

MAIN = $(addprefix shell/, \
	  signal.c \
	  prompt.c \
	  flags_token.c \
	  flags_ast.c \
	  init_shell.c \
	  var_tab_functions1.c \
	  var_tab_functions2.c \
	  basics.c \
	  exit_shell.c \
	  main.c)


################################################################################
################################### OBJECTS ####################################
################################################################################

OBJ = objs
O_DIR = $(C_DIR:$(SRC)/%=$(OBJ)/%)
O_FILES = $(C_FILES:$(SRC)/%.c=$(OBJ)/%.o)


################################################################################
#################################### RULES #####################################
################################################################################

all : $(NAME)

$(LIBFT) :
	@echo "\033[1;31m-- LIBFT -----------------------\033[0m"
	@make -C $(LIBFT_DIR)
	@printf  "%-45s\033[1;33m%s\033[0m\n" "Make $@" "OK"
	@echo "\033[1;31m-- OBJECTS ---------------------\033[0m"

$(NAME) : $(MLX) $(LIBFT) $(O_FILES)
	@$(CC) $(O_FILES) -o $@ $(LIB) $(INCL)
	@echo "\033[1;31m-- EXEC ------------------------\033[0m"
	@printf  "%-45s\033[1;32m%s\033[0m\n" "Make $@" "OK"

$(OBJ)/%.o: $(SRC)/%.c includes/
	@mkdir -p objs/ $(O_DIR)
	@$(CC) -o $@ -c $< $(INCL)
	@printf  "%-45s\033[1;32m%s\033[0m\n" "Make $@" "OK"

clean :
	@make clean -C $(LIBFT_DIR)
	@printf  "%-45s\033[1;33m%s\033[0m\n" "Make $@_libft" "OK"
	@rm -rf $(OBJ)
	@printf  "%-45s\033[1;32m%s\033[0m\n" "Make $@" "OK"

fclean : clean
	@make fclean -C $(LIBFT_DIR)
	@printf  "%-45s\033[1;33m%s\033[0m\n" "Make $@_libft" "OK"
	@rm -rf $(NAME)
	@printf  "%-45s\033[1;32m%s\033[0m\n" "Make $@" "OK"

re : fclean all

.PHONY : clean all fclean re
