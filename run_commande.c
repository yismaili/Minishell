/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commande.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:22:25 by souchen           #+#    #+#             */
/*   Updated: 2022/08/10 16:44:44 by yismaili         ###   ########.fr       */
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
	shell->path = get_path(shell);
	while (i < shell->divise.pipe)
	{
		if (pipe(fd) == -1)
			ft_die("pipe error\n");
		shell->output_fd = fd[1];
		next_run_commands(shell);
		close(shell->output_fd);
		if (shell->input_fd != 0)
			close(shell->input_fd);
		shell->input_fd = fd[0];
		i++;
	}
	next_run_commands(shell);
	ft_wait_pid(shell);
	ft_cmd(shell->commands);
	if (shell->path)
		ft_free_cmd(shell->path);
}

void	ft_wait_pid(t_struct *shell)
{
	int	j;

	j = 0;
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
