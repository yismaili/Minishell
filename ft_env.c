/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <souchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:21:46 by souchen           #+#    #+#             */
/*   Updated: 2022/06/22 22:11:53 by souchen          ###   ########.fr       */
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
