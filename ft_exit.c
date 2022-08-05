/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:21:52 by souchen           #+#    #+#             */
/*   Updated: 2022/08/05 17:59:12 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	ft_exit(t_struct *shell)
{
	ft_free_env(shell->env.tmp_var);
	ft_free_env(shell->env.tmp_con);
	ft_putstr_fd("exit\n", shell->output_fd);
	exit(0);
}

void	get_exit_code(int status)
{
	if (WIFEXITED(status))
		g_status = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
		g_status = WTERMSIG(status) + 128;
}
