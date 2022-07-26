/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:21:38 by souchen           #+#    #+#             */
/*   Updated: 2022/07/26 16:19:09 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "includes/minishell.h"

void	ft_echo(t_struct *shell)
{
	int i = 1;

	while (shell->arguments[i])
	{
		if (!ft_strncmp(shell->arguments[1], "-n", 2) && i == 1)
		{
			i++;
		}
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


void	print_echo(t_struct *shell ,char *echo_print)
{
	char **test = NULL;
	size_t i;
	int q1;
	int q2;
	char **splted;
	char **splt_quot;

	i = 0;
	q1 = 0;
	q2 = 0;
	splt_quot = ft_split(echo_print, '"');
	if (!ft_strncmp(echo_print, "$?", 2))
		printf("%d\n",0);
	else 
	{
		if (!ft_strncmp(splt_quot[0], "$", 1))
		{
				splted = ft_split(splt_quot[0], '$');
				ft_free_cmd(splt_quot);
				free(splt_quot);
				if (!getenv(splted[0]))
					return	;
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
		{

			i = 0;
			while(i < ft_strlen(echo_print))
			{
				if(echo_print[i] == QUOTE)
					q1++;
				else if(echo_print[i] == Double_Quote)
					q2++;
					i++;
			}
			if(q1 >= 1)
			{
				test = ft_split(echo_print, QUOTE);
				printf("%s\n", test[0]);
			}
			else if(q2 >= 1)
			{
				test = ft_split(echo_print, Double_Quote);
				ft_putstr_fd(test[0], shell->output_fd);
			}
			else
				ft_putstr_fd(echo_print,shell->output_fd);
			 free(test);
		}
	}
	ft_free_cmd(splt_quot);
	free(splt_quot);
}
