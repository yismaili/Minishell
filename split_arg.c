/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <souchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:20:16 by souchen           #+#    #+#             */
/*   Updated: 2022/09/01 17:20:42 by souchen          ###   ########.fr       */
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

char	*ft_split_cmd3(char	*cmd, t_struct *shell)
{
	char	*join;
	int		i;

	join = NULL;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'')
		{
			join = ft_remove_quot(cmd, '\'', shell);
			break ;
		}
		else if (cmd[i] == '\"')
		{
			join = ft_remove_quot(cmd, '\"', shell);
			break ;
		}
		i++;
	}
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
	char	**strrm;
	char	*join;

	strrm = NULL;
	join = NULL;
	shell->chek_plc = 0;
	if (ft_strchr(shell->arguments[i - 1], '$') && shell->check == 0)
		shell->arguments[i - 1] = ft_strdup(ft_chek_dlr_arg \
		(shell->arguments[i - 1], shell, strrm, join));
	if (shell->arguments[i] != NULL)
	{
		if (ft_strchr(shell->arguments[i], '$') && shell->check == 0)
			shell->arguments[i - 1] = ft_strdup(ft_chek_dlr_arg \
			(shell->arguments[i], shell, strrm, join));
	}
	command = ft_strjoin(command, shell->arguments[i - 1]);
	if (shell->arguments[i - 1])
		if (shell->arguments[i - 1][0] != '.')
			execve(command, &shell->arguments[i - 1], shell->env.env);
	return (1);
}

char	*ft_chek_dlr_arg(char *arguments, t_struct *shell, char **strrm, \
char *join)
{
	char	*rm;
	char	*con;
	int		p;
	int		j;

	p = 0;
	j = 0;
	strrm = ft_splt_dlor_arg(arguments, shell);
	while (strrm[j])
	{
		rm = ft_strtrim(strrm[j], "$");
		if (!is_empty(rm) && ft_isalpha(rm[0]))
			con = find_env(shell, rm);
		else if (rm[0] == '?' )
			con = find_env(shell, rm);
		if (shell->chek_plc == 1)
			con = ft_strjoin(con, "+");
		shell->chek_plc = 0;
		join = ft_strjoin(join, con);
		if (arguments == NULL)
			exit(127);
		p = 1;
		j++;
	}
	return (join);
}

char	**ft_splt_dlor_arg(char	*arguments, t_struct *shell)
{
	char	**strrm;

	strrm = NULL;
	if (ft_strchr(arguments, '+'))
	{
		strrm = ft_split(arguments, '+');
		shell->chek_plc = 1;
	}
	else
		strrm = ft_split(arguments, '$');
	return (strrm);
}

void	cmd_not_found(t_struct *shell)
{
	if (shell->arguments[0])
	{
		if (shell->arguments[0][0] == '<' || shell->arguments[0][0] == '>')
			exit(127);
		if (shell->arguments[0][0] != '|' && \
			ft_strlen(shell->arguments[0]) != 0)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(shell->arguments[0], 2);
			ft_putstr_fd(": command not found\n", 2);
		}	
	}
	if (shell->arguments[1])
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(shell->arguments[1], 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	if (shell->arguments[0] == NULL)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(shell->arguments[0], 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	exit(127);
}
