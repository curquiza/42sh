/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_apply_ctrl_op.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 17:51:42 by curquiza          #+#    #+#             */
/*   Updated: 2017/08/20 17:51:55 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_apply_semic(t_ast *ast)
{
	int		ret;

	ret = CMD_SUCCESS;
	if (ast->left)
		ret = ft_execution(ast->left);
	if (ast->right)
		ret = ft_execution(ast->right);
	return (ret);
}

int		ft_apply_and(t_ast *ast)
{
	int		ret;

	ret = CMD_SUCCESS;
	if (ast->left)
	{
		ast->left->bg = 1;
		ret = ft_execution(ast->left);
	}
	if (ast->right)
		ret = ft_execution(ast->right);
	return (ret);
}

int		ft_apply_d_pipe(t_ast *ast)
{
	int		ret;

	ret = CMD_SUCCESS;
	if ((ret = ft_execution(ast->left)) != 0)
		ret = ft_execution(ast->right);
	return (ret);
}

int		ft_apply_d_and(t_ast *ast)
{
	int		ret;

	ret = CMD_SUCCESS;
	if ((ret = ft_execution(ast->left)) == 0)
		ret = ft_execution(ast->right);
	return (ret);
}
