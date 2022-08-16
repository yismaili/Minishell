/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:21:38 by souchen           #+#    #+#             */
/*   Updated: 2022/08/16 14:51:54 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	ft_echo(t_struct *shell)
{
	int	i;

	i = 1;
	shell->q1 = 0;
	shell->q2 = 0;
	shell->i = 0;
	if (shell->arguments[1] == NULL)
	{
		ft_putstr_fd("\n", shell->output_fd);
		return ;
	}
	if (!ft_strncmp(shell->arguments[1], "-n", 2))
			i++;
	while (shell->arguments[i])
	{
		if (shell->arguments[i])
		{
			print_echo(shell, shell->arguments[i]);
			ft_putstr_fd(" ", shell->output_fd);
		}
		i++;
	}
	if (ft_strncmp(shell->arguments[1], "-n", 2))
		ft_putstr_fd("\n", shell->output_fd);
}

void	print_echo(t_struct *shell, char *echo_print)
{
	size_t	i;

	i = 0;
	if (echo_print == NULL)
	{
		ft_putstr_fd(" ", shell->output_fd);
		return ;
	}
	if (!ft_strcmp(echo_print, "$?"))
	{
		ft_putnbr_fd(g_var.g_status, shell->output_fd);
		g_var.g_status = 0;
	}
	else if (!ft_strncmp(echo_print, "$", 1) && shell->check == 0)
		echo_with_dollar(shell, echo_print);
	else if (echo_print != NULL)
		ft_putstr_fd(echo_print, shell->output_fd);
}

void	echo_with_dollar(t_struct *shell, char *echo_print)
{
	char	**splted;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!shell->path)
		return ;
	splted = ft_split(echo_print, '$');
	while (splted[j])
	{
		i = 0;
		while (shell->env.tmp_var[i])
		{
			if (!ft_strcmp(shell->env.tmp_var[i], splted[j]))
			{
				ft_putstr_fd(shell->env.tmp_con[i], shell->output_fd);
			}
			i++;
		}
		j++;
	}
	ft_free_cmd(splted);
	return ;
}
