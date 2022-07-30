/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <souchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:21:52 by souchen           #+#    #+#             */
/*   Updated: 2022/07/30 15:10:42 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "includes/minishell.h"

void	ft_exit(t_struct *shell)
{
	free2(shell->commands);
	// if (shell->path)
	// 	free1(shell->path);
	free (shell->home);
	printf("exit\n");
	exit(0);
}