/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commande.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <souchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:22:25 by souchen           #+#    #+#             */
/*   Updated: 2022/07/04 13:58:48 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	run_commands(t_struct *shell)
{
	int	i;
	int	fd[2];

	i = 0;
	shell->cmp = 0;
	while (shell->divise.pipe > i)
	{
		if (pipe(fd) == -1)
		{
			printf("pipe error\n");
			exit(0);
		}
		shell->output_fd = fd[1];
		next_run_commands(shell);
		close(shell->output_fd);
		if (shell->input_fd != 0)
			close(shell->input_fd);
		shell->input_fd = fd[0];
		i++;
	}
	next_run_commands(shell);
}

void	next_run_commands(t_struct *shell)
{
	fun_redirection(shell);
	if (shell->commands[0][0] != '>')
	{
		arguments_func(shell);
		execution(shell);
		free(shell->arguments);
	}
}

void	fun_redirection(t_struct *shell)
{
	shell->line_commande = ft_strdup(shell->commands[shell->cmp]);
	if (shell->divise.number_command > 1)
		shell->cmp++;
	while (shell->commands[shell->cmp] && \
			(shell->commands[shell->cmp][0] == '<' || \
			shell->commands[shell->cmp][0] == '>'))
	{
		if (shell->commands[shell->cmp][0] == '>')
			outredirection(shell);
		else if (shell->commands[shell->cmp][0] == '<')
			inredirection(shell);
		shell->cmp++;
	}
}

void	execution(t_struct *shell)
{
	int		i;
	int		id;

	i = 0;
	builtin_exist(shell);
	if (shell->builtin_exist == 1)
		run_builtin(shell);
	else
	{
				id = fork();
		if (id < 0)
			printf("Error fork\n");
		else if (id == 0)
		{
			output_input(shell);
			if (shell->arguments[0] != NULL)
				while (shell->path[i] != NULL)
				{
					if (shell->arguments[0][0] == '|' && shell->arguments[1])
						next_execution(shell, i);
					else
						next_execution(shell, i);
					i++;
				}
		}
		else if (id > 0)
			waitpid(id, NULL, 0);
	}
}

void	next_execution(t_struct *shell, int i)
{
	char	*command;
	int		test;

	command = ft_strdup(shell->path[i]);
	if (shell->arguments[0][0] == '|' && !shell->arguments[0][1])
	{
		command = ft_strjoin(shell->path[i], shell->arguments[1]);
		test = execve(command, &shell->arguments[1], shell->env.env);
	}
	if (shell->arguments[0][0] == '|' && shell->arguments[0][1])
	{
		shell->arguments[0] = &shell->arguments[0][1];
		command = ft_strjoin(shell->path[i], shell->arguments[0]);
		test = execve(command, &shell->arguments[1], shell->env.env);
	}
	else
	{
		command = ft_strjoin(shell->path[i], shell->arguments[0]);
		test = execve(command, &shell->arguments[0], shell->env.env);
	}
	free(command);
}
