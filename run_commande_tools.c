/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commande_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <yismaili@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 12:11:19 by souchen           #+#    #+#             */
/*   Updated: 2022/08/29 12:14:17 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	run_commande_next1(t_struct *shell)
{
	if (next_run_commands(shell) == 1)
	{
		if (shell->path)
			ft_free_cmd(shell->path);
		ft_cmd(shell->commands);
		free(shell->line_commande);
		return (0);
	}
	return (1);
}

void	run_commands_next(t_struct *shell)
{
	shell->last_in = -1;
	shell->last = 1;
	if (next_run_commands(shell) == 1)
	{
		if (shell->path)
			ft_free_cmd(shell->path);
		ft_cmd(shell->commands);
		free(shell->line_commande);
		return ;
	}
	if (shell->input_fd != 0)
		close(shell->input_fd);
	if (shell->output_fd != 1)
		close(shell->output_fd);
	if (shell->path)
		ft_free_cmd(shell->path);
	ft_cmd(shell->commands);
}
