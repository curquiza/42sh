/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 16:44:40 by curquiza          #+#    #+#             */
/*   Updated: 2017/08/20 17:09:09 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_start_shell_loop(t_lexeme **lex, t_ast **ast, char **line)
{
	if (g_shell->ctrl_c == 0)
	{
		*lex = NULL;
		*ast = NULL;
		ft_put_prompt();
		ft_read_line(line, PROMPT_DEF_SIZE);
	}
	g_shell->ctrl_c = 0;
}

/*
** DEROULEMENT DU SHELL :
** 1) lexer : on sépare la chaine de char envoyée par l'utilisateur en token
** (càd en mots) et on identifie le type de token, si possible.
** ex : opérateur de contrôle, io_number, word...
** 2) parser : on verifie les erreurs de syntax + on gere les inhibiteurs (le
** shell attend le retour de l'user) + on recupere les arguments des here-docs.
** Cf shell grammar pour les hdocs.
** 3) ast : on construit l'abstract syntax tree. Les noeuds sont des opérateurs
** de controle et les feuilles des commandes simples.
** 4) LANCEMENT DE FT_CMD_LINE_EXECUTION
** Cette fonction parcourt l'arbre, et pour chaque leaf de l'ast (cmd simple)
** va gérer les étapes suivantes :
** - semantic_analysis : dans l'ast, à l'intérieur de chaque feuille (= les
** commandes simples) on split les tokens en differents roles : assigment words,
** commande, arguments, ou redirection.
** - expansion : on gère les expansions, càd dans mon cas pour l'instant la
** parameter expansion (en mode bébé) et la removal quotes (simple quote,
** double quote et back-slash). Cf shell grammar.
** - organisation rapide pré-execution : pour faciliter la future execution, on
** crée un **char pour stocker les arguments, et on re-organise les redirections
** dans une liste chainée adaptéee et on sauve stdin, stdout et stderr.
** - execution : on execute la commande simple.
*/

int		main(int ac, char **av, char **environ)
{
	g_shell = ft_init_shell(ac, av, environ, SHELL_NAME);
	ft_catch_signals(SIGINT_ON);
	while (g_shell->run == 1)
	{
		ft_start_shell_loop(&g_shell->lex, &g_shell->ast, &g_shell->line);
		ft_lexer(&g_shell->lex, g_shell->line);
		if (ft_parser(&g_shell->lex, g_shell) == 0)
		{
			ft_ast(g_shell->lex, &g_shell->ast, g_shell);
			ft_catch_signals(SIGINT_OFF);
			ft_cmd_line_execution(&g_shell->ast, g_shell);
			ft_catch_signals(SIGINT_ON);
		}
		else
		{
			if (g_shell->ctrl_c == 0)
				ft_fill_cmd_return(258, g_shell);
			ft_lexlstdel(&g_shell->lex);
		}
		g_shell->run == 1 && g_shell->ctrl_c == 0 ? ft_putendl("") : 0;
	}
	return (ft_exit_shell());
}
