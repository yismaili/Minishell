/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commande_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <souchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 12:11:19 by souchen           #+#    #+#             */
/*   Updated: 2022/09/02 03:04:45 by souchen          ###   ########.fr       */
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

void	ft_print_msg(t_struct *shell, char	*line)
{
	ft_putchar_fd('\"', shell->fd);
	ft_putstr_fd(line, shell->fd);
	ft_putchar_fd('\"', shell-> fd);
	ft_putstr_fd("\n", shell->fd);
	return ;
}

void	ft_print_msg_qot(t_struct *shell, char	*line)
{
	ft_putchar_fd('\'', shell->fd);
	ft_putstr_fd(line, shell->fd);
	ft_putchar_fd('\'', shell-> fd);
	ft_putstr_fd("\n", shell->fd);
	return ;
}

void	ft_change_data(t_struct	*shell, char *ptr, char **file, int check)
{
	if (check == 1)
	{
		shell->line_commande = ft_strdup(file[1]);
		free(ptr);
	}
	if (check == 2)
	{
		shell->line_commande = ft_strjoin(shell->line_commande, file[1]);
		free(ptr);
	}
}
