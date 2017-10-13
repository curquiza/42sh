/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 17:00:33 by curquiza          #+#    #+#             */
/*   Updated: 2017/08/20 17:00:53 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** ft_is_in_lexlst :
** Vérifie si un type d'opérateur est présent dans la liste chainée de type
** t_lexeme.
*/

int		ft_is_in_lexlst(t_lexeme *lex, enum e_op op)
{
	while (lex)
	{
		if (lex->op == op)
			return (1);
		lex = lex->next;
	}
	return (0);
}

/*
** ft_build_pipeline et ft_split_in_tree_pipe :
** Idem que ft_build_ast et ft_split_in_tree mais dans le cas des pipes. L'arbre
** est construit à l'envers du cas géneral.
*/

void	ft_split_in_tree_pipe(t_ast *ast)
{
	t_lexeme	*scmd_start;
	t_lexeme	*node;
	t_lexeme	*current;

	current = ast->lex;
	if (!current || (current && !current->next))
		return ;
	scmd_start = current;
	while (current->next && current->next->op != PIPE)
		current = current->next;
	node = current->next;
	current->next = NULL;
	if (scmd_start)
		ast->left = ft_ast_newnode(scmd_start, ast->shell);
	current = node->next;
	node->next = NULL;
	ast->lex = node;
	if (current)
		ast->right = ft_ast_newnode(current, ast->shell);
}

void	ft_build_pipeline(t_ast *ast)
{
	if (ast)
	{
		if (ft_is_in_lexlst(ast->lex, PIPE))
			ft_split_in_tree_pipe(ast);
		if (ast->left)
			ft_build_pipeline(ast->left);
		if (ast->right)
			ft_build_pipeline(ast->right);
	}
}

/*
** ft_split_in_tree :
** Split la liste chainée lex par rapoort à l'opérateur de contrôle op.
** Le noeud : op.
** La branche gauche : la partie de lex à gauche de op.
** La branche droite : la partie de lex à droite de op.
*/

void	ft_split_in_tree(t_ast *ast, enum e_op op1, enum e_op op2)
{
	t_lexeme	*left_end;
	t_lexeme	*node;
	t_lexeme	*current;

	left_end = NULL;
	node = NULL;
	current = ast->lex;
	if (!current || (current && !current->next))
		return ;
	while (current && current->next)
	{
		if (current->next->op == op1 || current->next->op == op2)
		{
			node = current->next;
			left_end = current;
		}
		current = current->next;
	}
	ast->right = ft_ast_newnode(node->next, ast->shell);
	node ? node->next = NULL : 0;
	left_end ? left_end->next = NULL : 0;
	ast->left = ft_ast_newnode(ast->lex, ast->shell);
	ast->lex = node;
}

/*
** ft_build_ast :
** Parcourt l'arbre puis appelle la fonction de split.
** Deux opérateurs possible dans le cas de priorités égales (ex : || et &&)
*/

void	ft_build_ast(t_ast *ast, enum e_op op1, enum e_op op2)
{
	if (ast)
	{
		if (ft_is_in_lexlst(ast->lex, op1) || ft_is_in_lexlst(ast->lex, op2))
			ft_split_in_tree(ast, op1, op2);
		if (ast->right)
			ft_build_ast(ast->right, op1, op2);
		if (ast->left)
			ft_build_ast(ast->left, op1, op2);
	}
}
