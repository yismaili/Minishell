/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:21:38 by souchen           #+#    #+#             */
/*   Updated: 2022/08/02 13:06:42 by yismaili         ###   ########.fr       */
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
	while (shell->arguments[i])
	{
		if (!ft_strncmp(shell->arguments[1], "-n", 2) && i == 1)
			i++;
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
	char	**test;
	size_t	i;
	char	**splt_quot;

	test = NULL;
	i = 0;
	splt_quot = ft_split(echo_print, '"');
	if (!ft_strncmp(echo_print, "$?", 2))
	{
		ft_putnbr_fd(g_status, shell->output_fd);
		printf("\n");
	}
	else 
	{
	    if (!ft_strncmp(splt_quot[0], "$", 1))
			echo_with_dollar(shell, splt_quot);
		
		else
			echo_with_quote(echo_print,test, shell);
	}
}

void echo_with_dollar(t_struct *shell, char **splt_quot)
{
	char **splted;
	int i;
	i = 0;
		splted = ft_split(splt_quot[0], '$');
		if(!getenv(splted[0]))
			return ;
		while(shell->env.tmp_var[i])
		{
			if(!ft_strcmp(shell->env.tmp_var[i], splted[0]))
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

void echo_with_quote(char *echo_print, char **test, t_struct *shell)
{
	while(shell->i < (int)ft_strlen(echo_print))
	{
		if(echo_print[shell->i] == QUOTE)
			shell->q1++;
		else if(echo_print[shell->i] == DOUBLE_QUOTE)
			shell->q2++;
		shell->i++;
	}
	if(shell->q1 >= 1)
	{
		test=ft_split(echo_print, QUOTE);
		printf("%s\n", test[0]);
	}
	else if(shell->q2 >= 1)
	{
		test = ft_split(echo_print, DOUBLE_QUOTE);
		ft_putstr_fd(test[0], shell->output_fd);
	}
	else
		ft_putstr_fd(echo_print, shell->output_fd);
}
