/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <yismaili@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:22:25 by souchen           #+#    #+#             */
/*   Updated: 2022/09/01 01:36:06 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	execution(t_struct *shell)
{
	int		i;

	i = 0;
	shell->builtin_exist = 0;
	builtin_exist(shell);
	if (shell->builtin_exist == 1 && shell->divise.pipe == 0)
	{
		if ((shell->double_quote % 2 != 0 || shell->quote % 2 != 0) && \
				strcmp(shell->arguments[0], "echo"))
		{
			cmd_not_found2(shell);
			return (0);
		}
		if (shell->variable == 1)
			shell->output_fd = 1;
		run_builtin(shell);
	}
	else
	{
		if (create_process(shell) == 1)
			return (1);
	}
	ft_free_cmd(shell->arguments);
	return (0);
}

int	create_process(t_struct *shell)
{
	g_var.g_isrun = 1;
	shell->pid = fork();
	if (shell->pid < 0)
		return (ft_failed_fork(), 1);
	else if (shell->pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (shell->builtin_exist == 1 && shell->divise.pipe >= 1)
		{
			if (shell->double_quote % 2 != 0 || (shell->quote % 2 != 0 \
						&& strcmp(shell->arguments[0], "echo") && \
						strcmp(shell->arguments[1], "echo") \
						&& strcmp(&shell->arguments[0][1], "echo")))
				cmd_not_found(shell);
			if (shell->variable == 1)
				shell->output_fd = 1;
			run_builtin(shell);
			exit(1);
		}
		output_input(shell);
		if (shell->arguments[0] != NULL)
			execute_cmd(shell);
	}
	return (0);
}

int	ft_failed_fork(void)
{
	ft_putstr_fd("Minishell: fork: Resource", 2);
	ft_putstr_fd(" temporarily unavailable\n", 2);
	return (1);
}

int	ft_check_arg(t_struct *shell, char *cmd_path)
{
	int	nb;

	if (shell->arguments[0])
	{
		if (shell->arguments[0][0] == '|' && shell->arguments[1])
		{
			if (!shell->arguments[0][1])
				nb = next_execute_commands(shell, 2, cmd_path);
			else
			{
				shell->arguments[0] = &shell->arguments[0][1];
				nb = next_execute_commands(shell, 1, cmd_path);
			}
		}
		else if (shell->arguments[0][0] == '|' && shell->arguments[1] == NULL)
		{
			shell->arguments[0] = &shell->arguments[0][1];
			nb = next_execute_commands(shell, 1, cmd_path);
		}
		else
			nb = next_execute_commands(shell, 1, cmd_path);
		if (nb == 0)
			return (0);
	}
	return (1);
}

char	*execute_cmd(t_struct *shell)
{
	int		i;
	char	*cmd_path;

	i = 0;
	cmd_path = NULL;
	execve(shell->arguments[0], &shell->arguments[0], shell->env.env);
	if (!shell->path)
		return (cmd_not_found(shell), NULL);
	while (shell->path[i])
	{
		cmd_path = ft_strjoin(shell->path[i], "/");
		if (shell->right == 1 || (shell->indice != 1 && \
					(shell->quote % 2 != 0 || shell->double_quote % 2 != 0)) || \
				(shell->indice == 1 && (shell->quote % 2 != 0 || \
										shell->double_quote % 2 != 0) && \
				(ft_strncmp(shell->arguments[0], "echo", 4)) && \
				ft_strncmp(&shell->arguments[0][1], "echo", 4)))
			cmd_not_found(shell);
		if (ft_check_arg(shell, cmd_path) == 0)
			return (NULL);
		i++;
	}
	cmd_not_found(shell);
	return (NULL);
}
