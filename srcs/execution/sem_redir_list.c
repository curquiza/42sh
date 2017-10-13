/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_redir_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 09:39:02 by curquiza          #+#    #+#             */
/*   Updated: 2017/05/26 15:54:20 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_redirlst_del(t_redir **redir)
{
	t_redir		*current;
	t_redir		*supp;

	if (!redir)
		return ;
	current = *redir;
	while (current)
	{
		supp = current;
		current = current->next;
		supp->next = NULL;
		free(supp);
	}
	*redir = NULL;
}

t_redir	*ft_redir_newnode(int io_nbr, t_lexeme *lex, char *output)
{
	t_redir		*new;

	if (!(new = (t_redir *)malloc(sizeof(*new))))
		ft_exit("malloc error", 1);
	new->op = 0;
	if (lex)
		new->op = lex->op;
	new->io_nbr = io_nbr;
	new->output = output;
	new->hdoc = lex->hdoc;
	new->next = NULL;
	return (new);
}

void	ft_redirlst_add_back(t_redir **alst, t_redir *new)
{
	t_redir	*tmp;

	if (alst == NULL)
		return ;
	tmp = *alst;
	if (*alst == NULL)
		*alst = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	ft_build_redir_list(t_ast *ast)
{
	t_lexeme	*current;
	t_redir		*new;

	current = ast->redir;
	while (current)
	{
		if (current->token == IO_NBR && current->next && current->next->next)
		{
			new = ft_redir_newnode(ft_atoi(current->s), current->next,
														current->next->next->s);
			ft_redirlst_add_back(&ast->redir_list, new);
			current = current->next->next;
		}
		else if (current->token == RED_OP && current->next)
		{
			if (current->op == LESS || current->op == DLESS
									|| current->op == LESSAND)
				new = ft_redir_newnode(0, current, current->next->s);
			else
				new = ft_redir_newnode(1, current, current->next->s);
			ft_redirlst_add_back(&ast->redir_list, new);
			current = current->next;
		}
		current = current->next;
	}
}
