/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:21:46 by souchen           #+#    #+#             */
/*   Updated: 2022/07/26 11:36:06 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "includes/minishell.h"

void ft_env(t_struct *shell)
{
	int n;
	n = 0;
	if (glob_var == 0)
	{
		ft_die("environment not fuond\n");
		return ;
	}
	while(n < shell->env.len)
	{
		if ( shell->env.tmp_con[n])
		{
			ft_putstr_fd(shell->env.tmp_var[n], shell->output_fd);
			ft_putchar_fd('=',shell->output_fd);
			ft_putstr_fd(shell->env.tmp_con[n], shell->output_fd);
			ft_putstr_fd("\n", shell->output_fd);
		}
	   n++;
	}
}
