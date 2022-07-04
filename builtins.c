/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:21:06 by souchen           #+#    #+#             */
/*   Updated: 2022/07/04 17:33:17 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
int builtin_exist(t_struct *shell)
{
	if(!ft_strncmp(shell->arguments[0], "exit", 4))
		shell->builtin_exist = 1;
	else if(!ft_strncmp(shell->arguments[0], "unset", 5))
		shell->builtin_exist = 1;
	else if(!ft_strncmp(shell->arguments[0], "env", 3))
		shell->builtin_exist = 1;
	else if(!ft_strncmp(shell->arguments[0], "cd", 2))
		shell->builtin_exist = 1;
	else if(!ft_strncmp(shell->arguments[0], "pwd", 3))
		shell->builtin_exist = 1;
	else if(!ft_strncmp(shell->arguments[0], "echo" ,4))
		shell->builtin_exist = 1;
	else if(!ft_strncmp(shell->arguments[0], "export", 6))
		shell->builtin_exist = 1;
	else
		shell->builtin_exist = 0;
	return 0;

}
void	run_builtin(t_struct *shell)
{
	if (!ft_strncmp(shell->arguments[0], "exit", 4))
		ft_exit(shell);
	else if(!ft_strncmp(shell->arguments[0], "unset", 5))
		ft_unset(shell);
	else if(!ft_strncmp(shell->arguments[0], "env", 3))
		ft_env(shell);
	else if(!ft_strncmp(shell->arguments[0], "cd", 2))
		ft_cd(shell);
	else if(!ft_strncmp(shell->arguments[0] , "pwd", 3))
		ft_pwd();
	else if(!ft_strncmp(shell->arguments[0], "echo", 4))
		ft_echo(shell);
	else if(!ft_strncmp(shell->arguments[0], "export", 6))
		ft_export(shell);

}
