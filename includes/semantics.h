/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semantics.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 20:44:22 by curquiza          #+#    #+#             */
/*   Updated: 2017/05/26 13:53:17 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SEMANTICS_H
# define SEMANTICS_H

# include "struct.h"

/*
** semantics.c
*/

void	ft_semantic_analysis(t_ast *ast);

/*
** sem_split.c
*/

void	ft_get_ass_word(t_ast *ast);
void	ft_redir_split(t_ast *ast, t_lexeme **start, t_lexeme **current);
void	ft_get_redir(t_ast *ast);
void	ft_get_cmd(t_ast *ast);
void	ft_get_argtab(t_ast *ast);

/*
** sem_redir_list.c
*/

void	ft_redirlst_del(t_redir **redir);
t_redir	*ft_redir_newnode(int io_nbr, t_lexeme *op, char *output);
void	ft_redirlst_add_back(t_redir **alst, t_redir *new);
void	ft_build_redir_list(t_ast *ast);

#endif
