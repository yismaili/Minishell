/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <souchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:22:25 by souchen           #+#    #+#             */
/*   Updated: 2022/08/20 13:47:23 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	execution(t_struct *shell)
{
	int		i;

	i = 0;
	builtin_exist(shell);
	if (shell->builtin_exist == 1)
	{
		run_builtin(shell);
	}
	else if (!shell->path)
		print_cmd_not_f(shell);
	else
		if (create_process(shell) == 1)
			return (1);
	ft_free_cmd(shell->arguments);
	return (0);
}

int	create_process(t_struct *shell)
{
	shell->pid = fork();
	if (shell->pid < 0)
	{
		ft_putstr_fd("Minishell: fork: Resource", 2);
		ft_putstr_fd(" temporarily unavailable\n", 2);
		return (1);
	}
	else if (shell->pid == 0)
	{
		output_input(shell);
		if (shell->arguments[0] != NULL)
			execute_cmd(shell);
	}
	return (0);
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
		if (shell->right == 1 || (shell->indice != 1 && \
					(shell->quote % 2 != 0 || shell->double_quote % 2 != 0)) || \
				(shell->indice == 1 && (shell->quote % 2 != 0 || \
										shell->double_quote % 2 != 0) && \
				(ft_strncmp(shell->arguments[0], "echo", 4)) && \
				(ft_strncmp(shell->arguments[1], "echo", 4))))
		{
			cmd_not_found(shell);
		}
		ft_check_arg(shell, cmd_path);
		i++;
	}
	cmd_not_found(shell);
	return (NULL);
}
