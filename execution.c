
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                     :+:      :+:    :+:      */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <souchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:22:25 by souchen           #+#    #+#             */
/*   Updated: 2022/07/30 18:23:52 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"


void print_cmd_not_f(t_struct *shell)
{
	ft_putstr_fd("Minishell :",2);
	ft_putstr_fd(shell->cmd_splited[0], 2);
	ft_putstr_fd(" : command not found\n", 2);
} 
void process_shild_execute(char **path, t_struct *shell)
{
	char *faded;
	faded = NULL;
	path = NULL;
	path = get_path(shell);
	faded = execute_cmd(shell, path);
	if(execve(faded, shell->cmd_splited, shell->env.env) < 0)
		cmd_not_found(shell->cmd_splited[0]);
	ft_free_cmd(path);
	free(path);
}

void	next_execute_cmd(char	**cmd_path)
{
	char	*current_pth;

	current_pth = getcwd(NULL, sizeof(NULL));
	*cmd_path = ft_strjoin(current_pth, "/minishell");
	free(current_pth);
}

char	*execute_cmd(t_struct *shell, char **path)
{
	int		i;
	char	*cmd_path;
	char	*tmp;

	i = 0;
	cmd_path = NULL;
	while (path[i])
	{
		tmp = path[i];
		path[i] = ft_strjoin(path[i], "/");
		free (tmp);
		if (!ft_strcmp(shell->commands[0], "./minishell "))
			next_execute_cmd(&cmd_path);
		else
			cmd_path = ft_strjoin(path[i], shell->cmd_splited[0]);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}

void	execution(t_struct *shell)
{
	int		i;
	char	**path;

	i = 0;
	path = NULL;
	builtin_exist(shell);
	if (shell->builtin_exist == 1)
		run_builtin(shell);
	else if (!getenv("PATH"))
		print_cmd_not_f(shell);
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
			//signals(2);
			output_input(shell);
			if (shell->arguments[0] != NULL)
				process_shild_execute(path, shell);
		}
	}
}
