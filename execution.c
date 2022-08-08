/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:22:25 by souchen           #+#    #+#             */
/*   Updated: 2022/08/08 20:22:42 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	execution(t_struct *shell)
{
	int		i;

	i = 0;
	builtin_exist(shell);
	if (shell->builtin_exist == 1)
	{
		if (shell->quote % 2 != 0 || shell->double_quote % 2 != 0
			|| (shell->right == 1))
		{
			cmd_not_found2(shell);
			return ;
		}
		run_builtin(shell);
	}
	else if (!shell->path)
		print_cmd_not_f(shell);
	else
	{
		shell->pid = fork();
		if (shell->pid < 0)
		{
			ft_putstr_fd("Minishell: fork: Resource \
					temporarily unavailable\n", 2);
			return ;
		}
		else if (shell->pid == 0)
		{
			output_input(shell);
			if (shell->arguments[0] != NULL)
				execute_cmd(shell);
		}
		ft_free_cmd(shell->arguments);
	}
}

void	ft_check_arg(t_struct *shell, char *cmd_path)
{
	if (shell->arguments[0][0] == '|' && shell->arguments[1])
	{
		if (!shell->arguments[0][1])
			next_execute_commands(shell, 2, cmd_path);
		else
		{
			shell->arguments[0] = &shell->arguments[0][1];
			next_execute_commands(shell, 1, cmd_path);
		}
	}
	else if (shell->arguments[0][0] == '|' && shell->arguments[1] == NULL)
	{
		shell->arguments[0] = &shell->arguments[0][1];
		next_execute_commands(shell, 1, cmd_path);
	}
	else
		next_execute_commands(shell, 1, cmd_path);
}

char	*execute_cmd(t_struct *shell)
{
	int		i;
	char	*cmd_path;

	i = 0;
	cmd_path = NULL;
	execve(shell->arguments[0], &shell->arguments[0], shell->env.env);
	while (shell->path[i])
	{
		cmd_path = ft_strjoin(shell->path[i], "/");
		if (shell->quote % 2 != 0 || shell->double_quote % 2 != 0
			|| (shell->right == 1))
		{
			cmd_not_found(shell);
		}
		ft_check_arg(shell, cmd_path);
		i++;
	}
	cmd_not_found(shell);
	return (NULL);
}

void	next_execute_commands(t_struct *shell, int i, char *command)
{
	char	*aux;
	char	**test;
	int		k;

	k = 0;
	aux = NULL;
	if (shell->arguments[1] && (shell->arguments[1][0] == QUOTE || \
		shell->arguments[1][0] == DOUBLE_QUOTE))
	{
		while (k < (int)ft_strlen(shell->arguments[1]))
		{
			if (shell->arguments[1][k] == '"' \
				|| shell->arguments[1][k] == QUOTE)
				shell->arguments[1][k] = '<';
			aux = ft_strtrim(shell->arguments[1], "<");
			k++;
		}
		test = ft_split(aux, '<');
		shell->arguments[1] = test[0];
	}
	command = ft_strjoin(command, shell->arguments[i - 1]);
	execve(command, &shell->arguments[i - 1], shell->env.env);
}

void	cmd_not_found(t_struct *shell)
{
	gl_var.g_status = 127;
	if (shell->arguments[0][0] != '|')
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(shell->arguments[0], 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	else if (shell->arguments[1])
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(shell->arguments[1], 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	exit(gl_var.g_status);
}

void	cmd_not_found2(t_struct *shell)
{
	gl_var.g_status = 127;
	if (shell->arguments[0][0] != '|')
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(shell->arguments[0], 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	else if (shell->arguments[1])
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(shell->arguments[1], 2);
		ft_putstr_fd(": command not found\n", 2);
	}
}
