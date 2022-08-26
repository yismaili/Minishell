/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <souchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:21:06 by souchen           #+#    #+#             */
/*   Updated: 2022/08/24 18:22:08 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	builtin_exist(t_struct	*shell)
{
	shell->variable = 0;
	if (!ft_strcmp(shell->arguments[0], "exit"))
	{
		shell->builtin_exist = 1;
		return 1;
	}
	else if (!ft_strcmp(shell->arguments[0], "unset"))
	{
		shell->builtin_exist = 1;
	}
	else if (!ft_strcmp(shell->arguments[0], "env"))
	{
		shell->builtin_exist = 1;
		return 1;
	}
	else if (!ft_strcmp(shell->arguments[0], "cd"))
	{
		shell->builtin_exist = 1;
		return 1;
	}
	else if (!ft_strcmp(shell->arguments[0], "pwd"))
	{
		shell->builtin_exist = 1;
		return 1;
	}
	else if (!ft_strcmp(shell->arguments[0], "echo") || !ft_strcmp(&shell->arguments[0][1], "echo"))
	{
		if(shell->last == 1 && !ft_strcmp(&shell->arguments[0][1], "echo"))
			shell->variable = 1;
		shell->builtin_exist = 1;
		return 1;
	}
	else if (!ft_strcmp(shell->arguments[0], "export") || !ft_strcmp(&shell->arguments[0][1], "export"))
	{
		if(shell->last == 1 && !ft_strcmp(&shell->arguments[0][1], "export"))
			shell->variable = 1;
		shell->builtin_exist = 1;
		return 1;
	}
	
	else if(shell->arguments[1] != NULL)
	{
		
		
		if (!ft_strcmp(shell->arguments[1], "echo"))
		{
			shell->builtin_exist = 1;
			if(shell->last == 1)
				shell->variable = 1;
			return 1;
		}
		else if (!ft_strcmp(shell->arguments[1], "export"))
		{
			shell->builtin_exist = 1;
			if(shell->last == 1)
				shell->variable = 1;
			return 1;
		}
	}
	else
		shell->builtin_exist = 0;
	return (0);
}

void	run_builtin(t_struct *shell)
{
	if (!ft_strcmp(shell->arguments[0], "exit"))
	{
		ft_exit(shell);
		return ;
	}
	else if (!ft_strcmp(shell->arguments[0], "unset"))
	{
		ft_unset(shell);
		return ;
	}
	else if (!ft_strcmp(shell->arguments[0], "env"))
	{
		ft_env(shell);
		return ;
	}
	else if (!ft_strcmp(shell->arguments[0], "cd"))
	{
		ft_cd(shell);
		return ;
	}
	else if (!ft_strcmp(shell->arguments[0], "pwd"))
	{
		ft_pwd(shell);
		return ;
	}
	else if (!ft_strcmp(shell->arguments[0], "echo") || !ft_strcmp(&shell->arguments[0][1], "echo"))
	{
		ft_echo(shell);
		return ;
	}
	else if (!ft_strcmp(shell->arguments[0], "export") || !ft_strcmp(&shell->arguments[0][1], "export"))
	{
		ft_export(shell);
		return ;
	}
	else if(shell->arguments[1] != NULL)
	{
		if (!ft_strcmp(shell->arguments[1], "echo"))
		{
			ft_echo(shell);
			return ;
		}
		else if (!ft_strcmp(shell->arguments[1], "export"))
		{
			ft_export(shell);
			return ;
		}
	}
	
}