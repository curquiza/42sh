/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 18:19:55 by curquiza          #+#    #+#             */
/*   Updated: 2017/10/13 11:21:11 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

/*
** main
*/

# define SHELL_NAME "42sh"
# define HDOC_PROMPT "hdoc> "
# define BSLASH_PROMPT "bslash> "
# define SQUOTE_PROMPT "s_quote> "
# define DQUOTE_PROMPT "d_quote> "
# define PIPE_PROMPT "pipe> "
# define DPIPE_PROMPT "d_pipe> "
# define DAND_PROMPT "d_and> "

/*
** flags
*/

# define FLAG_TOKEN "--token"
# define FLAG_AST "--ast"

/*
** execution
*/

# define CMD_FAILURE 1
# define CMD_SUCCESS 0

/*
** termcaps
*/

# define TC_SIZE 2048
# define DEF_TERM "xterm-256color"
# define PROMPT_DEF_SIZE 7

/*
** signals
*/

# define SIGINT_ON 1
# define SIGINT_OFF 0

/*
** ctrl_d
*/

# define UNEXP_CTRLD_MSG "syntax error: unexpected end of file"

/*
** historic
*/

# define HISTO_SIZE 50
# define HISTO_S_PROMPT "histo_search> "
# define HISTO_ERR_MSG "No match found"
# define HISTO_OK_MSG "Match found"

/*
** completion
*/

# define COMP_SIZE 100
# define COMP_MSG "Too many possibilities"
# define COMP_PROMPT "compl> "

#endif
