/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inhibitor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 21:47:29 by curquiza          #+#    #+#             */
/*   Updated: 2017/07/31 19:23:18 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** ft_read_line_again :
** Affiche le prompt correspondant à l'inhibiteur et récupère la nouvelle entrée
** de l'utilisateur.
*/

void	ft_read_line_again(enum e_inhib inhib, char **line)
{
	char	*prompt;

	if (inhib == I_SQUOTE)
		prompt = ft_strdup(SQUOTE_PROMPT);
	else if (inhib == I_DQUOTE)
		prompt = ft_strdup(DQUOTE_PROMPT);
	else if (inhib == I_BSLASH)
		prompt = ft_strdup(BSLASH_PROMPT);
	else if (inhib == I_PIPE)
		prompt = ft_strdup(PIPE_PROMPT);
	else if (inhib == I_DPIPE)
		prompt = ft_strdup(DPIPE_PROMPT);
	else if (inhib == I_DAND)
		prompt = ft_strdup(DAND_PROMPT);
	else
		prompt = ft_strdup("> ");
	ft_putstr(prompt);
	g_shell->inhib = 1;
	ft_read_line(line, ft_strlen(prompt));
	g_shell->inhib = 0;
	ft_strdel(&prompt);
}

/*
** ft_manage_inhib_ctrl :
** Retourne -1 si un Ctrl C ou un Ctrl D a été capté, 0 sinon.
*/

int		ft_manage_inhib_ctrl(char **line, t_shell *shell)
{
	if (ft_check_ctrl_c(line, shell) == 1)
		return (-1);
	if (ft_check_and_restore_ctrld(shell) == 1)
	{
		ft_putendl3_fd(shell->name, ": ", UNEXP_CTRLD_MSG, 2);
		free(*line);
		return (-1);
	}
	return (0);
}

/*
** ft_hook_line_up_to_lex :
** Complète la fin du token du dernier maillon de lex. Puis passe le reste au
** lexer et ajoute à la suite de lex les nouveaux tokens.
*/

void	ft_hook_line_up_to_lex(int ret_inhib, t_lexeme **lex, char **line)
{
	if (ret_inhib == I_SQUOTE)
		ft_add_endoftoken_quote(*lex, line, 39);
	else if (ret_inhib == I_DQUOTE)
		ft_add_endoftoken_quote(*lex, line, 34);
	else if (ret_inhib == I_BSLASH)
		ft_add_endoftoken_bslash(*lex, line);
	ft_lexer(lex, *line);
	ft_lexlst_remove_if(lex, "", 0);
}

/*
** ft_inhibitor :
** Vérifie les fermetures de doubles et simples quotes, et des back-slashs.
** Vérifie si les pipes, double and et double pipe possèdent une deuxième
** commande simple après l'opérateur de contrôle.
** Rend la main à l'utilisateur si nécessaire => vérifie donc à chaque fois les
** erreurs de syntaxe, le ctrl_d, et split la chaine de char récupérée dans les
** bons maillons.
*/

int		ft_inhibitor(t_lexeme **lex, t_shell *shell)
{
	char	*tokenerror;
	char	*line;
	int		ret_inhib;

	if (!lex || !(*lex))
		return (-1);
	line = NULL;
	while ((ret_inhib = ft_check_all_inhib(*lex)) != I_OK)
	{
		ft_read_line_again(ret_inhib, &line);
		if (ft_manage_inhib_ctrl(&line, shell) == -1)
			return (-1);
		ft_hook_line_up_to_lex(ret_inhib, lex, &line);
		if ((tokenerror = ft_check_tokenerror(*lex)) != NULL)
		{
			ft_puterr_unexp_token(tokenerror, shell->name);
			free(line);
			return (-1);
		}
	}
	free(line);
	return (0);
}
