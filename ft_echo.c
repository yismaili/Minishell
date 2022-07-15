/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:21:38 by souchen           #+#    #+#             */
/*   Updated: 2022/07/16 00:03:59 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "includes/minishell.h"

void	ft_echo(t_struct *shell)
{
	if (shell->arguments[1])
	{
		print_echo(shell, shell->arguments[1]);
		ft_putstr_fd("\n", shell->output_fd);
	}
	else
		ft_putstr_fd("\n", shell->output_fd);
}


void	print_echo(t_struct *shell ,char *echo_print)
{
	char **test = NULL;
	size_t i;
	int q1;
	int q2;
	char **splted;

	i = 0;
	q1 = 0;
	q2 = 0;
	if (!ft_strncmp(echo_print, "$?", 2))
		printf("%d\n",0);
	else
	{
		if (!ft_strncmp(echo_print, "$", 1))
		{
			splted = ft_split(echo_print, '$');
			while (shell->env.tab1[i])
			{
				if (!ft_strncmp(shell->env.tab1[i], splted[0], ft_strlen(splted[0])))
				{
					ft_putstr_fd(shell->env.tab2[i], shell->output_fd);
					printf("\n");
					return ;
				}
				i++;
			}
		}
		i = 0;
		while(i < ft_strlen(echo_print))
		{
			if(echo_print[i] == QUOTE)
			{
				q1++;
			}else if(echo_print[i] == Double_Quote)
			{
				q2++;
			}
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
	}
}
