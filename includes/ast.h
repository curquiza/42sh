/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 22:13:49 by curquiza          #+#    #+#             */
/*   Updated: 2017/05/29 19:52:31 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "token.h"
# include "struct.h"

/*
** ast.c
*/

void	ft_ast(t_lexeme *lex, t_ast **ast, t_shell *shell);

/*
** build_ast.c
*/

int		ft_is_in_lexlst(t_lexeme *lex, enum e_op op);
void	ft_split_in_tree_pipe(t_ast *ast);
void	ft_build_pipeline(t_ast *ast);
void	ft_split_in_tree(t_ast *ast, enum e_op op1, enum e_op op2);
void	ft_build_ast(t_ast *ast, enum e_op op, enum e_op op2);

/*
** create_delete.c
*/

t_ast	*ft_ast_newnode(t_lexeme *lex, t_shell *shell);
void	ft_del_ast(t_ast **ast);

#endif
