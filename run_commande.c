/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commande.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <souchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:22:25 by souchen           #+#    #+#             */
/*   Updated: 2022/07/30 16:45:27 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	run_commands(t_struct *shell)
{
	int	i;
	int	fd[2];
	int	status;

	i = 0;
	status = 0;
	while (i < shell->divise.pipe)
	{
		if (pipe(fd) == -1)
			ft_putstr_fd("pipe error\n", 2);
		shell->output_fd = fd[1];
		next_run_commands(shell);
		close(shell->output_fd);
		if (shell->input_fd != 0)
			close(shell->input_fd);
		shell->input_fd = fd[0];
		i++;
	}
	next_run_commands(shell);
	func(shell, i, status);
	ft_free(shell);
}

void	func(t_struct *shell, int i, int status)
{
	int	j;

	j = 0;
	if (i == shell->divise.pipe)
	{
		waitpid(shell->pid, &status, 0);
		get_exit_code(status);
	}
	while (j < shell->divise.pipe + 1)
	{
		wait(NULL);
		j++;
	}
}
void	next_run_commands(t_struct	*shell)
{
	fun_redirection(shell);
	if (shell->commands[0][0] != '>')
	{
		arguments_func(shell);
		execution(shell);
	}
}

char	*execute_cmd(t_struct *shell, char **path)
{
	int		i;
	char	*cmd_path;
	char	*current_pth;
	char	*tmp;

	i = 0;
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
	char	*faded;
	char	**path;

	faded = NULL;
	path = NULL;
	i = 0;
	builtin_exist(shell);
	if (shell->builtin_exist == 1)
		run_builtin(shell);
	else if (!getenv("PATH"))
	{
		ft_putstr_fd("Minishell :",2);
		ft_putstr_fd(shell->cmd_splited[0], 2);
		ft_putstr_fd(" : command not found\n",2);
	}
	else
	{
		shell->pid = fork();
		if (shell->pid < 0)
		{
			ft_putstr_fd("Minishell: fork: Resource temporarily unavailable\n", 2);
			return ;
		}
		else if (shell->pid == 0)
		{
			output_input(shell);
			if (shell->arguments[0] != NULL)
			{
				path = get_path(shell);
				faded = execute_cmd(shell, path);
				if (execve(faded, shell->cmd_splited, shell->env.env) < 0)
					cmd_not_found(shell->cmd_splited[0]);
				ft_free_cmd(path);
				free(path);
			}
		}
	}
}
