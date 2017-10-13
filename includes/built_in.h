/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 15:33:31 by curquiza          #+#    #+#             */
/*   Updated: 2017/08/20 17:58:39 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

enum	e_builtin
{
	NOT_BUILTIN,
	B_ECHO,
	B_CD,
	B_ENV,
	B_SETENV,
	B_UNSETENV,
	B_EXIT,
	B_SET,
	B_UNSET,
	B_EXPORT
};

/*
** built_in.c
*/

int				ft_exec_built_in(t_ast *ast, enum e_builtin ret);
enum e_builtin	ft_is_built_in(char *s);

/*
** built_in_flags.c
*/

void			ft_put_usage(char *cmd, char flag_error, char *legal_flags);
char			ft_check_illegal_flags(char *flags, char *legal_flags);
char			*ft_get_flags(char **array);
void			ft_fill_flagstab(char *s, char *flags, int *cpt_flags);
char			**ft_get_arg(char **array, char flag_error);

/*
** built_in_echo.c
*/

int				ft_builtin_echo(t_ast *ast);

/*
** built_in_cd.c
*/

int				ft_check_err_cd(char *path, t_shell *shell);
int				ft_go_to_dir(t_shell *shell, char *path);
int				ft_go_to_home(t_shell *shell);
int				ft_go_to_oldpwd(t_shell *shell);
int				ft_builtin_cd(t_ast *ast);

/*
** built_in_env.c
*/

char			**ft_get_new_env(char **arg, char *flags, t_shell *shell);
t_shell			*ft_get_new_shell(char **arg, char *flags, t_shell *old_shell);
char			**ft_get_utility(char **arg);
int				ft_exec_utility_env(t_shell *shell, char **arg);
int				ft_builtin_env(t_ast *ast);

/*
** built_in_setenv.c
*/

int				ft_is_valid_name(char *s);
int				ft_check_err_setenv(t_shell *shell, char *arg, char *cmd);
int				ft_builtin_setenv(t_ast *ast);

/*
** built_in_unsetenv.c
*/

int				ft_builtin_unsetenv(t_ast *ast);

/*
** built_in_exit.c
*/

int				ft_is_numeric_str(char *s);
int				ft_builtin_exit(t_ast *ast);

/*
** built_in_set.c
*/

void			ft_apply_flags_set(char *flags, t_shell *shell);
int				ft_builtin_set(t_ast *ast);

/*
** built_in_unset.c
*/

int				ft_builtin_unset(t_ast *ast);

/*
** built_in_export.c
*/

int				ft_check_name_err(t_shell *shell, char *name, char *cmd);
int				ft_only_name_export(t_shell *shell, char *arg, char *cmd);
int				ft_val_with_name_export(t_shell *shell, char *arg, char *cmd);
int				ft_builtin_export(t_ast *ast);

#endif
