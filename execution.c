/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:22:25 by souchen           #+#    #+#             */
/*   Updated: 2022/08/04 02:46:44 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	execution(t_struct *shell)
{
	int		i;
	char	**path;

	i = 0;
	path = NULL;
	builtin_exist(shell);
	if (shell->builtin_exist == 1)
		run_builtin(shell);
	else if (!get_path(shell))
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
				execute_cmd(shell, path);
		}
	}
}

char	*execute_cmd(t_struct *shell, char **path)
{
	int		i;
	char	*cmd_path;
	char	*tmp;

	i = 0;
	path = get_path(shell);
	cmd_path = NULL;
	g_var = execve(shell->arguments[0], &shell->arguments[0], shell->env.env);
	while (path[i])
	{
		tmp = path[i];
		path[i] = ft_strjoin(path[i], "/");
		free (tmp);
		if (shell->quote % 2 != 0 || shell->double_quote % 2 != 0
			|| (shell->right == 1))
		{
			cmd_not_found(shell);
			exit(0);
		}
		if (shell->arguments[0][0] == '|' && shell->arguments[1])
		{
			if (!shell->arguments[0][1])
				next_execute_commands(shell, 2, path[i]);
			else
			{
				shell->arguments[0] = &shell->arguments[0][1];
				next_execute_commands(shell, 1, path[i]);
			}
		}
		else if (shell->arguments[0][0] == '|' && shell->arguments[1] == NULL)
		{
			shell->arguments[0] = &shell->arguments[0][1];
			next_execute_commands(shell, 1, path[i]);
		}
		else
			next_execute_commands(shell, 1, path[i]);
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
	g_var = execve(command, &shell->arguments[i - 1], shell->env.env);
	free(command);
}

void	cmd_not_found(t_struct *shell)
{
	g_status = 127;
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
	exit(g_status);
}
