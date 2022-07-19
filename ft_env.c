/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:21:46 by souchen           #+#    #+#             */
/*   Updated: 2022/07/19 14:40:24 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "includes/minishell.h"

void ft_env(t_struct *shell)
{
	int n;
	n = 0;
	while(n < shell->env.len)
	{
	   ft_putstr_fd(shell->env.tab1[n], shell->output_fd);
	   ft_putchar_fd('=',shell->output_fd);
	   ft_putstr_fd(shell->env.tab2[n], shell->output_fd);
	   ft_putstr_fd("\n", shell->output_fd);
	   n++;
	}
}
