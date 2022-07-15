/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commande.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:22:25 by souchen           #+#    #+#             */
/*   Updated: 2022/07/15 12:24:03 by yismaili         ###   ########.fr       */
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
	char	*faded = NULL;

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
			{
				while (shell->path[i] != NULL)
				{
					if (shell->arguments[0][0] == '|' && shell->arguments[1])
						faded = next_execution(shell, i);
					else
						faded = next_execution(shell, i);
					i++;
				}
			}
			if (!faded)
				printf("Minishell: %s: command not found\n", shell->arguments[0]);
		}
		else if (id > 0)
			waitpid(id, NULL, 0);
	}
}

char	*next_execution(t_struct *shell, int i)
{
	char	*cmd_path;
	char    *buff;
	// char **splt;
	// char	*join_slach = NULL;
   
	cmd_path = NULL;
	buff = NULL;
	if (!ft_memcmp(shell->commands[0], "./", 2))
	{
		buff = getcwd(buff, sizeof(buff));
	 	//splt = ft_split(shell->cmd_paths[0], '/');
		//join_slach = ft_strjoin(buff, "/");
		//cmd_path = ft_strjoin(join_slach, splt[1]);
		cmd_path = ft_strjoin(buff, "/minishell");
		//printf("%s\n", cmd_path);
		if (access(cmd_path, F_OK) == 0)
			execve(cmd_path, &shell->arguments[0], shell->env.env);
		else
			cmd_not_found(shell->arguments[0]);
	}
	else if (shell->arguments[0][0] == '|' && !shell->arguments[0][1])
	{
		cmd_path = ft_strjoin(shell->path[i], shell->arguments[1]);
		if (access(cmd_path, F_OK) == 0)
			execve(cmd_path, &shell->arguments[1], shell->env.env);
		else
			cmd_not_found(shell->arguments[1]);
	}
	else if (shell->arguments[0][0] == '|' && shell->arguments[0][1])
	{
		shell->arguments[0] = &shell->arguments[0][1];
		cmd_path = ft_strjoin(shell->path[i], shell->arguments[0]);
		if (access(cmd_path, F_OK) == 0)
			execve(cmd_path, &shell->arguments[1], shell->env.env);
		else
			cmd_not_found(shell->arguments[1]);
	}
	else
	{
		cmd_path = ft_strjoin(shell->path[i], shell->arguments[0]);
		if (access(cmd_path, F_OK) == 0)
			execve(cmd_path, &shell->arguments[0], shell->env.env);
		else
			cmd_not_found(shell->arguments[1]);
	}
	free(cmd_path);
	return (NULL);
}

void cmd_not_found(char *cmd)
{
	if (cmd)
	{
		printf("Minishell: %s:  command not found\n", cmd);
		exit(1);
	}
}