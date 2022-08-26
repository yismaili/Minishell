/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <souchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:21:38 by souchen           #+#    #+#             */
/*   Updated: 2022/08/25 00:41:16 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	ft_echo(t_struct *shell)
{
	int	i;
	int j;

	i = 1;
	j = 0;
	shell->q1 = 0;
	shell->q2 = 0;
	shell->i = 0;
	shell->f_pipe=0;
	if(shell->arguments[0][0] == '|')
	{
		shell->f_pipe=1;
	}
	while(shell->variable == 1 && shell->arguments[j] != NULL && shell->f_pipe != 0)
	{
		shell->arguments[j] = shell->arguments[j + 1];
		j++;
	}
	if (shell->arguments[1] == NULL)
	{
		ft_putstr_fd("\n", shell->output_fd);
		return ;
	}
	while (!ft_strncmp(shell->arguments[i], "-n", 2))
			i++;
	while (shell->arguments[i] && shell->qot % 2 == 0)
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
	while(echo_print[i] != '$' && echo_print[i] != '\0')
	{
		ft_putchar_fd(echo_print[i], shell->output_fd);
		i++;
	}
	if (!ft_strncmp(&echo_print[i], "$", 1))
	{
			echo_with_dollar(shell, (&echo_print[i]));
	}
}

void	echo_with_dollar(t_struct *shell, char *echo_print)
{
	char	**splted;
	int		i;
	int		j;
	int		indice;

	i = 0;
	j = 0;
	if (!shell->path)
			return ;
			splted = ft_split(echo_print, '$');
		while(splted[i] != NULL)
		{
			while(splted[i][j] != '?' && splted[i][j] != '\0')
			{
				j++;
			}
			if(splted[i][j] == '?')
			{
				indice = j;
				printf("indice = %d\n", indice);
				break ;
			}
			i++;
		}
		if(&splted[0][j] != NULL)
		{
			printf("ere\n");
			ft_putstr_fd(&splted[0][j + 1], shell->output_fd);
		}
			j = 0;
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
