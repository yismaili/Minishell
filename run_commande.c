/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commande.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:22:25 by souchen           #+#    #+#             */
/*   Updated: 2022/07/28 16:02:48 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	**get_path(t_struct *ptr)
{
	int		i;
	char	**path;

	i = 0;
	while (ptr->env.tmp_var[i])
	{
		if (ft_strcmp(ptr->env.tmp_var[i], "PATH") == 0)
		{
			path = ft_split(ptr->env.tmp_con[i], ':');
			return (path);
		}
		i++;
	}
	return (NULL);
}

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
		if (shell->input_fd > 0)
			close(shell->input_fd);
		shell->output_fd = fd[1];
		next_run_commands(shell);
		close(shell->output_fd);
		shell->input_fd = fd[0];
		i++;
	}
///	close(shell->input_fd);
	next_run_commands(shell);
	ft_free_cmd(shell->commands);
}

void	next_run_commands(t_struct *shell)
{
	fun_redirection(shell);
	if (shell->commands[0][0] != '>')
	{
		arguments_func(shell);
		execution(shell);
		ft_free_cmd(shell->arguments);
		free(shell->arguments);
		ft_free_cmd(shell->cmd_splited);
		free(shell->cmd_splited);
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
char *execute_cmd(t_struct *shell, char **path)
{
	int i = 0;
	char	*cmd_path;
	char	*current_pth;
	char	*tmp;
	
	cmd_path = NULL;
	while (path[i])
	{
		tmp = path[i];
		path[i] = ft_strjoin(path[i], "/");
		free (tmp);
		if (!ft_strcmp(shell->commands[0], "./minishell "))
		{
			current_pth = getcwd(NULL, sizeof(NULL));
			cmd_path = ft_strjoin(current_pth, "/minishell");
			free(current_pth);
		}
		else
			cmd_path = ft_strjoin(path[i], shell->cmd_splited[0]);
		if (access(cmd_path, X_OK) == 0)
			return(cmd_path);
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
	char	**path = NULL;

	i = 0;
	builtin_exist(shell);
	if (shell->builtin_exist == 1)
		run_builtin(shell);
	else
	{
		pid = fork();
		if (pid < 0)
		{
			ft_putstr_fd("Minishell: fork: Resource temporarily unavailable\n", 2);
			return ;
		}
		else if (pid == 0)
		{
			output_input(shell);
			if (shell->arguments[0] != NULL && getenv("PATH"))
			{
				path = get_path(shell);
				faded = execute_cmd(shell, path);
			if (execve(faded, shell->cmd_splited, shell->env.env) < 0)
				cmd_not_found(shell->cmd_splited[0]);
			ft_free_cmd(path);
			free(path);
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
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(" : command not found\n",2);
		exit(127);
	}
}