/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 09:41:45 by curquiza          #+#    #+#             */
/*   Updated: 2017/08/20 17:56:27 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_get_ass_word(t_ast *ast)
{
	t_lexeme	*current;
	t_lexeme	*start;

	current = ast->lex;
	if (!current || current->token != ASS_WORD)
		return ;
	start = current;
	while (current->next && current->next->token == ASS_WORD)
		current = current->next;
	ast->ass_word = start;
	ast->lex = current->next;
	current->next = NULL;
}

void	ft_redir_split(t_ast *ast, t_lexeme **start, t_lexeme **current)
{
	if ((*current)->next && (*current)->next->token == RED_OP)
		*current = (*current)->next;
	if ((*current)->next && (*current)->next->token == WORD)
		*current = (*current)->next;
	if (!ast->redir)
		ast->redir = *start;
	else
		ft_lexlst_last(ast->redir)->next = *start;
	*start = (*current)->next;
	(*current)->next = NULL;
}

void	ft_get_redir(t_ast *ast)
{
	t_lexeme	*current;
	t_lexeme	*start;

	current = ast->lex;
	if (current && (current->token == IO_NBR || current->token == RED_OP))
	{
		ft_redir_split(ast, &ast->lex, &current);
		ft_get_redir(ast);
	}
	while (current)
	{
		if (current->next && (current->next->token == IO_NBR
								|| current->next->token == RED_OP))
		{
			start = current;
			current = current->next;
			ft_redir_split(ast, &start->next, &current);
			ft_get_redir(ast);
			return ;
		}
		current = current->next;
	}
}

void	ft_get_cmd(t_ast *ast)
{
	ast->cmd = ast->lex;
	if (ast->lex)
	{
		ast->lex = ast->lex->next;
		ast->cmd->next = NULL;
	}
}

void	ft_get_argtab(t_ast *ast)
{
	int			len;
	int			i;
	t_lexeme	*current;

	if (!ast->cmd)
		return ;
	len = ft_lexlst_len(ast->lex) + 1;
	if (!(ast->argtab = (char **)malloc(sizeof(*ast->argtab) * (len + 1))))
		ft_exit("malloc error", 1);
	ast->argtab[len] = NULL;
	current = ast->lex;
	if (ft_strrchr(ast->cmd->s, '/'))
		ast->argtab[0] = ft_strdup(ft_strrchr(ast->cmd->s, '/') + 1);
	else
		ast->argtab[0] = ft_strdup(ast->cmd->s);
	i = 1;
	while (i < len)
	{
		ast->argtab[i] = ft_strdup(current->s);
		current = current->next;
		i++;
	}
}
