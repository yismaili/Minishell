/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_env_fun.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:20:07 by souchen           #+#    #+#             */
/*   Updated: 2022/08/15 22:33:36 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	malloc_env_tmp(t_struct *shell)
{
	shell->env.tmp_var = malloc(sizeof(char *) * (shell->env.len + 1));
	if (!shell->env.tmp_var)
		return (0);
	shell->env.tmp_con = malloc(sizeof(char *) * (shell->env.len + 1));
	if (!shell->env.tmp_con)
		return (0);
	return (1);
}

int	count_len_env(t_struct *shell)
{
	int	i;

	i = 0;
	while (shell->env.env[i])
		i++;
	shell->env.len = i;
	return (i);
}

void	ft_die(char *str)
{
	ft_putstr_fd(str, 1);
}

void	ft_die_malloc(char *str)
{
	ft_putstr_fd(str, 1);
	exit(1);
}

char	*find_env_tmp(t_struct *shell, char *search)
{
	int	i;

	i = 0;
	shell->env.position = 0;
	if (g_var.g_var == 0)
		return (NULL);
	while (shell->env.tmp_var[i] && i <= shell->env.len)
	{
		if (!ft_strcmp(shell->env.tmp_var[i], search))
		{
			shell->env.position = i;
			return (shell->env.tmp_var[i]);
		}
		i++;
	}
	return (NULL);
}
