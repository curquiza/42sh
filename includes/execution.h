/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 10:02:26 by curquiza          #+#    #+#             */
/*   Updated: 2017/10/19 14:08:15 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "struct.h"

enum	e_cmd_search
{
	ISDIR = 1,
	NOSUCHFILE = 2,
	NOTFOUND = 3,
	NOPERM = 4,
	FOUND = 5
};

/*
** execution.c
*/

void				ft_pre_execution(t_ast *ast);
int					ft_execution(t_ast *ast);
void				ft_cmd_line_execution(t_ast **ast, t_shell *shell);

/*
** exec_apply_ctrl_op.c
*/

int					ft_apply_semic(t_ast *ast);
int					ft_apply_and(t_ast *ast);
int					ft_apply_d_pipe(t_ast *ast);
int					ft_apply_d_and(t_ast *ast);

/*
** exec_pipeline.c
*/

int					ft_apply_pipe(t_ast *ast);

/*
** exec_simple_cmd.c
*/

int					ft_exec_scmd(t_ast *ast);
int					ft_process_controller(pid_t pid, t_ast *ast);

/*
** exec_error_msg.c
*/

void				ft_put_errmsg(char *bin, char *s, char *msg);
int					ft_putmsg_cmderr(char *cmd, enum e_cmd_search ret,
												t_shell *shell);
void				ft_put_readonly_errmsg(char *bin, char *cmd, char *varname);
void				ft_put_invalidname_errmsg(char *bin, char *cmd,
																char *varname);
void				ft_put_cd_errmsg(char *bin, char *s, char *msg);

/*
** exec_cmd.c
*/

enum e_cmd_search	ft_check_cmd_slash(t_ast *ast);
char				**ft_get_pathtab(t_shell *shell);
enum e_cmd_search	ft_check_path(char *cmd);
enum e_cmd_search	ft_check_cmd_noslash(t_ast *ast);
int					ft_do_cmd(t_ast *ast);

/*
** exec_redirection.c
*/

int					ft_connect_fd(char *output, int to, int from,
														t_shell *shell);
int					ft_create_file(enum e_op op, char *output, t_shell *shell);
int					ft_apply_fd_aggr(t_redir *redir, t_shell *shell);
int					ft_apply_hdoc(t_redir *redir, t_shell *shell);
int					ft_do_redirection(t_redir *redir, t_shell *shell);

/*
** exec_ass_word.c
*/

void				ft_do_ass_word(t_ast *ast, int mode);

/*
** exec_cmd_return.c
*/

int					ft_get_cmdret(int status);
void				ft_fill_cmd_return(int ret, t_shell *shell);

/*
** job_lst.c
*/

t_job				*ft_joblst_new(char *cmdname, int pgid);
void				ft_joblst_addback(t_job **alst, t_job *new);
int					ft_joblst_len(t_job *lst);
t_job				*ft_joblst_last(t_job *lst);
t_job				*ft_joblst_at(t_job *lst, size_t n);

/*
** job_controller.c
*/

int					ft_wait_for_job(t_job **job);
void				ft_exit_job(int sig);

#endif
