/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 16:28:05 by curquiza          #+#    #+#             */
/*   Updated: 2017/10/26 16:50:08 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "token.h"

typedef struct		s_tc
{
	char			buff[TC_SIZE];
	char			tmp[TC_SIZE];
	int				nbr_char;
	int				prompt_len;
	int				init_prompt_len;
	int				x_max;
	int				curs_x;
	int				curs_y;
	char			*up;
	char			*down;
	char			*right;
	char			*left;
	int				ctrl_r;
	int				stop;
	int				redim;
}					t_tc;

typedef struct		s_histo
{
	char			*line;
	struct s_histo	*next;
	struct s_histo	*prev;
}					t_histo;

typedef struct		s_histo_ctrl
{
	t_histo			*start;
	t_histo			*end;
	char			*current;
	int				len;
	int				pos;
	int				max_reach;
}					t_histo_ctrl;

typedef struct		s_comp
{
	char			*word;
	struct s_comp	*next;
	struct s_comp	*prev;
}					t_comp;

typedef struct		s_comp_ctrl
{
	int				status;
	char			*word_to_comp;
	char			*path;
	char			*clues;
	t_comp			*start;
	t_comp			*end;
	int				len;
}					t_comp_ctrl;

typedef struct		s_flag
{
	int				token;
	int				ast;
}					t_flag;

typedef struct		s_lexeme
{
	char			*s;
	char			*hdoc;
	int				hdoc_delim;
	enum e_token	token;
	enum e_op		op;
	struct s_lexeme	*next;
}					t_lexeme;

typedef struct		s_redir
{
	enum e_op		op;
	int				io_nbr;
	char			*output;
	char			*hdoc;
	int				fd;
	struct s_redir	*next;
}					t_redir;

typedef struct		s_ast
{
	t_lexeme		*lex;
	t_lexeme		*ass_word;
	t_lexeme		*redir;
	t_lexeme		*cmd;
	char			**argtab;
	t_redir			*redir_list;
	struct s_shell	*shell;
	struct s_ast	*left;
	struct s_ast	*right;
	int				bg;
}					t_ast;

typedef struct		s_job
{
	char			*cmd_name;
	int				pgid;
	struct s_job	*next;
}					t_job;

typedef struct		s_shell
{
	char			*name;
	char			*line;
	t_lexeme		*lex;
	t_ast			*ast;
	int				run;
	int				exit_status;
	char			**var_loc;
	char			**var_env;
	char			**var_priv;
	int				std_fd[FD_MAX];
	t_tc			*tc_tool;
	t_flag			*flags;
	t_histo_ctrl	*histo_ctrl;
	t_comp_ctrl		*comp_ctrl;
	int				ctrl_d;
	int				ctrl_c;
	int				inhib;
	int				event_err;
	pid_t			pgid;
	int				terminal;
	t_job			*job_lst;
	struct termios	dfl_term;
}					t_shell;

#endif
