/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <yismaili@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:21:06 by souchen           #+#    #+#             */
/*   Updated: 2022/09/01 01:24:40 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	builtin_exist(t_struct	*shell)
{
	shell->variable = 0;
	if (!ft_strcmp(shell->arguments[0], "exit") && shell->con_failed == 0)
		return ((shell->builtin_exist = 1), 1);
	else if (!ft_strcmp(shell->arguments[0], "unset"))
		shell->builtin_exist = 1;
	else if (!ft_strcmp(shell->arguments[0], "env"))
		return ((shell->builtin_exist = 1), 1);
	else if (!ft_strcmp(shell->arguments[0], "cd"))
		return ((shell->builtin_exist = 1), 1);
	else if (!ft_strcmp(shell->arguments[0], "pwd"))
		return ((shell->builtin_exist = 1), 1);
	else if (!ft_strcmp(shell->arguments[0], "echo") || \
		!ft_strcmp(&shell->arguments[0][1], "echo"))
	{
		if (shell->last == 1 && !ft_strcmp(&shell->arguments[0][1], "echo"))
			shell->variable = 1;
		return ((shell->builtin_exist = 1), 1);
	}
	else
		return (ft_builtin_exist_next(shell));
	return (0);
}

int	ft_builtin_exist_next(t_struct	*shell)
{
	if (!ft_strcmp(shell->arguments[0], "export") || \
		!ft_strcmp(&shell->arguments[0][1], "export"))
	{
		if (shell->last == 1 && !ft_strcmp(&shell->arguments[0][1], "export"))
			shell->variable = 1;
		return ((shell->builtin_exist = 1), 1);
	}
	else if (shell->arguments[1] != NULL)
		return (ft_builtin_exist_else(shell));
	else
		shell->builtin_exist = 0;
	return (0);
}

int	ft_builtin_exist_else(t_struct	*shell)
{
	if (!ft_strcmp(shell->arguments[1], "echo"))
	{
		if (shell->last == 1)
			shell->variable = 1;
		return ((shell->builtin_exist = 1), 1);
	}
	else if (!ft_strcmp(shell->arguments[1], "export"))
	{
		if (shell->last == 1)
			shell->variable = 1;
		return ((shell->builtin_exist = 1), 1);
	}
	else if (!ft_strcmp(shell->arguments[1], "pwd"))
	{
		if (shell->last == 1)
			shell->variable = 1;
		return ((shell->builtin_exist = 1), 1);
	}
	return (0);
}

int	run_builtin(t_struct *shell)
{
	if (!ft_strcmp(shell->arguments[0], "exit"))
		return (ft_exit(shell), 0);
	else if (!ft_strcmp(shell->arguments[0], "unset"))
		return (ft_unset(shell), 0);
	else if (!ft_strcmp(shell->arguments[0], "env"))
		return (ft_env(shell), 0);
	else if (!ft_strcmp(shell->arguments[0], "cd"))
		return (ft_cd(shell), 0);
	else if (!ft_strcmp(shell->arguments[0], "pwd"))
		return (ft_pwd(shell), 0);
	else if (!ft_strcmp(shell->arguments[0], "echo") || \
		!ft_strcmp(&shell->arguments[0][1], "echo"))
		return (ft_echo(shell), 0);
	else if (!ft_strcmp(shell->arguments[0], "export") || \
		!ft_strcmp(&shell->arguments[0][1], "export"))
		return (ft_export(shell), 0);
	else if (shell->arguments[1] != NULL)
		return (run_builtin_next(shell));
	return (1);
}

int	run_builtin_next(t_struct *shell)
{
	if (!ft_strcmp(shell->arguments[1], "echo"))
		return (ft_echo(shell), 0);
	else if (!ft_strcmp(shell->arguments[1], "export"))
		return (ft_export(shell), 0);
	else if (!ft_strcmp(shell->arguments[1], "pwd"))
		return (ft_pwd(shell), 0);
	return (0);
}
