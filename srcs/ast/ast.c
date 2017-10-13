/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 22:12:13 by curquiza          #+#    #+#             */
/*   Updated: 2017/07/30 19:41:18 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** ft_ast :
** Fonction générale de construction de l'ast.
** A partir de la liste chainée lex, va construire une premiere fois l'arbre par
** rapport aux ';' puis va repasser dans l'arbre pour reduire chaque noeud en
** commande simple par rapport aux autres opérateurs de contrôle.
** L'ordre de passage correspond à la priorité de chaque opérateur.
** Si le flag --ast est activé, affiche l'arbre.
*/

void	ft_ast(t_lexeme *lex, t_ast **ast, t_shell *shell)
{
	if (!ast)
		return ;
	*ast = NULL;
	if (lex)
	{
		*ast = ft_ast_newnode(lex, shell);
		ft_build_ast(*ast, SEMIC, -1);
		ft_build_ast(*ast, DAND, DPIPE);
		ft_build_pipeline(*ast);
	}
	if (*ast && (*ast)->shell->flags->ast == 1)
		ft_putast(*ast);
}
