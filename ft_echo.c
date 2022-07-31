/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:21:38 by souchen           #+#    #+#             */
/*   Updated: 2022/07/31 19:37:21 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	ft_echo(t_struct *shell)
{
	int	i;

	i = 1;
	while (shell->arguments[i])
	{
		if (!ft_strcmp(shell->arguments[1], "-n"))
			i++;
		if (shell->arguments[i])
		{
			print_echo(shell, shell->arguments[i]);
			ft_putstr_fd(" ", shell->output_fd);
		}
		i++;
	}
	if (ft_strcmp(shell->arguments[1], "-n"))
		ft_putstr_fd("\n", shell->output_fd);
}

void	print_echo(t_struct *shell, char *echo_print)
{
	if (!ft_strcmp(echo_print, "$?"))
	{
		ft_putnbr_fd(g_status, shell->output_fd);
		printf("\n");
	}
	else
	{
		ft_echo_tool(shell, echo_print);
	}
}

void	ft_echo_tool(t_struct *shell, char *echo_print)
{
	int			i;
	char		**splted;

	i = 0;
	if (!ft_strncmp(echo_print, "$", 1))
	{
		splted = ft_split(echo_print, '$');
		if (!getenv(splted[0]))
			return ;
		while (shell->env.tmp_var[i])
		{
			if (!ft_strcmp(shell->env.tmp_var[i], splted[0]))
			{
				ft_free_cmd(splted);
				free(splted);
				ft_putstr_fd(shell->env.tmp_con[i], shell->output_fd);
				return ;
			}
			i++;
		}
		ft_free_cmd(splted);
		free(splted);
	}
	else
		ft_putstr_fd(echo_print, shell->output_fd);
}
