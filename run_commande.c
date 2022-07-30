/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commande.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <souchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:22:25 by souchen           #+#    #+#             */
/*   Updated: 2022/07/30 18:51:49 by souchen          ###   ########.fr       */
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
