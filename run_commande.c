/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commande.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:22:25 by souchen           #+#    #+#             */
/*   Updated: 2022/07/15 18:04:35 by yismaili         ###   ########.fr       */
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
char *execute_cmd(t_struct *shell)
{
	int i = 0;
	char	*cmd_path;
	char	*current_path;
//	char **splt;
	char	*join_slach = NULL;

	while (shell->path[i])
	{
		cmd_path = NULL;
		current_path = NULL;
		if (!ft_memcmp(shell->commands[0], "./", 2))
		{
			current_path = getcwd(current_path, sizeof(current_path));
			//splt = ft_split(shell->commands[0], '/');
			join_slach = ft_strjoin(current_path, "/");
			cmd_path = ft_strjoin(join_slach, "minishell");
			if (access(cmd_path, F_OK) == 0)
				execve(cmd_path, &shell->arguments[0], shell->env.env);
		}
		if (shell->arguments[0][0] == '|' && !shell->arguments[0][1])
		{
			cmd_path = ft_strjoin(shell->path[i], shell->arguments[1]);
			if (access(cmd_path, F_OK) == 0)
				execve(cmd_path, &shell->arguments[1], shell->env.env);
		}
		else if (shell->arguments[0][0] == '|' && shell->arguments[0][1])
		{
			shell->arguments[0] = &shell->arguments[0][1];
			cmd_path = ft_strjoin(shell->path[i], shell->arguments[0]);
			if  (access(cmd_path, F_OK) == 0)
				execve(cmd_path, &shell->arguments[1], shell->env.env);
		}
		else
		{
			cmd_path = ft_strjoin(shell->path[i], shell->arguments[0]);
			if  (access(cmd_path, F_OK) == 0)
				execve(cmd_path, &shell->arguments[0], shell->env.env);
		}
		free(cmd_path);
			i++;
		}
	return(NULL);
}
void	execution(t_struct *shell)
{
	int		i;
	pid_t	pid;
	char	*faded = NULL;

	i = 0;
	builtin_exist(shell);
	if (shell->builtin_exist == 1)
		run_builtin(shell);
	else
	{
		pid = fork();
		if (pid < 0)
			printf("Error fork\n");
		else if (pid == 0)
		{
			output_input(shell);
			if (shell->arguments[0] != NULL)
			{
				faded = execute_cmd(shell);
				if (!faded)
					cmd_not_found(shell->arguments[1]);
			}
		}
		else
			wait(0);
	}
}

void cmd_not_found(char *cmd)
{
	if (cmd)
	{
		printf("Minishell: %s:  command not found\n", cmd);
		exit(1);
	}
}