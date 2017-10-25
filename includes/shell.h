/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 13:56:25 by curquiza          #+#    #+#             */
/*   Updated: 2017/10/24 18:02:54 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <pwd.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <term.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include <sys/param.h>

# include "libft.h"
# include "define.h"
# include "struct.h"
# include "tc.h"
# include "token.h"
# include "lexer.h"
# include "parser.h"
# include "ast.h"
# include "semantics.h"
# include "expansion.h"
# include "built_in.h"
# include "execution.h"

t_shell	*g_shell;

/*
** basics.c
*/

int			ft_is_separator(char c);
int			ft_next_squote(int i, char *s);
int			ft_next_dquote(int i, char *s);
int			ft_is_uns_nbr(char *s);
char		*ft_tab_to_str(char **array);

/*
** init_shell.c
*/

char		**ft_init_priv(void);
t_flag		*ft_init_flags(int ac, char **av);
char		**ft_init_env(char **environ);
t_shell		*ft_init_shell(int ac, char **av, char **environ, char *name);

/*
** var_tab_functions1.c
*/

char		*ft_get_varvalue(char **vartab, char *varname);
int			ft_get_varindex(char **vartab, char *varname);
int			ft_exist_in(char **vartab, char *varname);

/*
** var_tab_functions2.c
*/

void		ft_add_var(char ***vartab, char *newvar, char *value);
void		ft_chg_varval(char **vartab, char *newvar, char *value);
void		ft_chg_varval_or_add(char ***vartab, char *newvar, char *value);
void		ft_suppr_var(char ***vartab, char *varname);

/*
** flags_token.c
*/

void		ft_put_token_name(enum e_token token);
void		ft_put_op_name(enum e_op op);
void		ft_put_lexlst(t_lexeme *lst);

/*
** flags_ast.c
*/

void		ft_put_lexlst_word(t_lexeme *lst);
void		ft_run_display_ast(t_ast *ast, int step, int move);
void		ft_putast(t_ast *ast);

/*
** prompt.c
*/

void		ft_put_cut_path(void);
void		ft_put_user(void);
void		ft_put_prompt(void);

/*
** signal.c
*/

int			ft_check_ctrl_c(char **line, t_shell *shell);
void		ft_ctrl_c(int sig);
void		ft_cancel_ctrl_c(int sig);
void		ft_redim_window(int sig);
void		ft_catch_signals(int mode);

/*
** exit_shell.c
*/

void		ft_del_histo(t_histo_ctrl **ctrl);
void		ft_del_shell(t_shell **shell);
int			ft_exit_shell(void);

#endif
