/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:21:46 by souchen           #+#    #+#             */
/*   Updated: 2022/07/31 19:44:35 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	ft_env(t_struct *shell)
{
	int	n;

	if (g_var == 0)
	{
		ft_die("environment not found\n");
		return ;
	}
	n = 0;
	while (n < shell->env.len)
	{
		if (shell->env.tmp_con[n] && ft_strlen(shell->env.tmp_con[n]) != 0)
		{
			ft_putstr_fd(shell->env.tmp_var[n], shell->output_fd);
			ft_putchar_fd('=', shell->output_fd);
			ft_putstr_fd(shell->env.tmp_con[n], shell->output_fd);
			ft_putstr_fd("\n", shell->output_fd);
		}
		n++;
	}
}

void	ft_check_env(char	**env)
{
	int	i;

	i = 0;
	if (!env)
		g_var = 0;
	while (env[i])
		i++;
	g_var = i;
}

int	line_empty(char	*input)
{
	int	i;

	i = -1;
	while (input[++i])
		if (input[i] != '\t' && input[i] != '\v' && input[i] != '\f' \
				&& input[i] != '\n' && input[i] != ' ' && input[i] != '\r')
			return (0);
	return (1);
}
