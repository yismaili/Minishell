/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commande_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <souchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 12:11:19 by souchen           #+#    #+#             */
/*   Updated: 2022/08/24 17:14:11 by souchen          ###   ########.fr       */
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
		return (0);
	}
	return (1);
}

void	run_commands_next(t_struct *shell)
{
	shell->last_in = -1;
	shell->last = 1;
	shell-> output_fd = 1;
	if (next_run_commands(shell) == 1)
	{
		if (shell->path)
			ft_free_cmd(shell->path);
		ft_cmd(shell->commands);
		return ;
	}
	if (shell->input_fd != 0)
		close(shell->input_fd);
	if (shell->path)
		ft_free_cmd(shell->path);
	ft_cmd(shell->commands);
}
