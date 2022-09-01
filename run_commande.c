/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commande.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <yismaili@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:22:25 by souchen           #+#    #+#             */
/*   Updated: 2022/08/31 19:33:26 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	get_exit_status(t_struct *shell)
{
	int		status;
	char	*ascii;

	status = 0;
	waitpid(shell->pid, &status, 0);
	if (!WIFEXITED(status) && WIFSIGNALED(status))
	{
		g_var.g_status = WTERMSIG(status) + 128;
	}
	else
		g_var.g_status = WEXITSTATUS(status);
	ascii = ft_itoa(g_var.g_status);
	if (find_env_tmp(shell, "?"))
	{
		free(shell->env.tmp_con[shell->env.position]);
		shell->env.tmp_con[shell->env.position] = ft_strdup(ascii);
	}
	free(ascii);
	ft_wait_pid(shell);
}

void	run_commands(t_struct *shell)
{
	int	i;
	int	end[2];

	i = 0;
	shell->last = 0;
	if (g_var.g_var == 0)
		ft_remplir_env(shell);
	shell->path = get_path(shell);
	while (i < shell->divise.pipe)
	{
		if (pipe(end) == -1)
			ft_die("pipe error\n");
		shell->output_fd = end[1];
		shell->t = end[1];
		shell->last_in = end[0];
		if (run_commande_next1(shell) == 0)
			return ;
		for_close(shell);
		shell->input_fd = end[0];
		i++;
	}
	run_commands_next(shell);
	get_exit_status(shell);
}

void	for_close(t_struct *shell)
{
	close(shell->t);
	close(shell->output_fd);
	if (shell->input_fd != 0)
		close(shell->input_fd);
}

void	ft_wait_pid(t_struct *shell)
{
	int	j;

	j = 0;
	while (j <= shell->divise.pipe + 1)
	{
		wait(NULL);
		j++;
	}
}

int	next_run_commands(t_struct	*shell)
{
	int	io[2];

	io[0] = dup(0);
	io[1] = dup(1);
	if (fun_redirection(shell) == 0)
		return (1);
	if (arguments_func(shell) == 0)
		return (1);
	if (execution(shell) == 1)
		return (1);
	dup2(io[1], 1);
	dup2(io[0], 0);
	close(io[1]);
	close(io[0]);
	return (0);
}
