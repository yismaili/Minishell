/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <souchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:20:16 by souchen           #+#    #+#             */
/*   Updated: 2022/08/25 00:18:25 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*ft_split_cmd(char	*cmd, t_struct *shell)
{
	char	*join;

	join = NULL;
	if (cmd[shell->pos] == '\"')
		join = ft_remove_quot(cmd, '\"', shell);
	else if (cmd[shell->pos] == '\'')
		join = ft_remove_quot(cmd, '\'', shell);
	return (join);
}

char	*ft_split_cmd2(char	*cmd, t_struct *shell)
{
	char	*join;

	join = NULL;
	shell->qot = 0;
	if (ft_strchr(cmd, '\"'))
		join = ft_remove_quot(cmd, '\"', shell);
	else if (ft_strchr(cmd, '\''))
	{
		join = ft_remove_quot(cmd, '\'', shell);
	}
	return (join);
}

void	cmd_not_found2(t_struct *shell)
{
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

int	next_execute_commands(t_struct *shell, int i, char *command)
{
	char	*strrm;
	int		k;

	k = 0;
	strrm = NULL;
	if (ft_strchr(shell->arguments[i - 1], '$') && shell->check == 0)
	{
		printf("here nop\n");
		strrm = ft_strtrim(shell->arguments[i - 1], "$");
		shell->arguments[i - 1] = find_env(shell, strrm);
		if(shell->arguments[i - 1] == NULL)
			return 0;
	}
	command = ft_strjoin(command, shell->arguments[i - 1]);

	execve(command, &shell->arguments[i - 1], shell->env.env);
	return 1;
}

void	cmd_not_found(t_struct *shell)
{
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
	exit(127);
}
