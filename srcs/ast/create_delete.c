/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_delete.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 17:00:20 by curquiza          #+#    #+#             */
/*   Updated: 2017/08/20 17:00:21 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** ft_ast_newnode :
** Malloc un nouveau maillon de l'arbre.
*/

t_ast	*ft_ast_newnode(t_lexeme *lex, t_shell *shell)
{
	t_ast	*new;

	if (!(new = (t_ast *)malloc(sizeof(*new))))
		ft_exit("malloc error", 1);
	new->lex = lex;
	new->ass_word = NULL;
	new->cmd = NULL;
	new->redir = NULL;
	new->argtab = NULL;
	new->redir_list = NULL;
	new->shell = shell;
	new->left = NULL;
	new->right = NULL;
	new->bg = 0;
	return (new);
}

/*
** ft_del_ast :
** Supprime la totalité de l'arbre.
*/

void	ft_del_ast(t_ast **ast)
{
	if (*ast)
	{
		if ((*ast)->left)
			ft_del_ast(&(*ast)->left);
		if ((*ast)->right)
			ft_del_ast(&(*ast)->right);
		ft_lexlstdel(&((*ast)->ass_word));
		ft_lexlstdel(&((*ast)->redir));
		ft_lexlstdel(&((*ast)->cmd));
		ft_lexlstdel(&((*ast)->lex));
		ft_tabdel(&(*ast)->argtab);
		ft_redirlst_del(&(*ast)->redir_list);
		(*ast)->left = NULL;
		(*ast)->right = NULL;
		free(*ast);
		*ast = NULL;
	}
}
