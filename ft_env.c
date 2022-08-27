/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <yismaili@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:21:46 by souchen           #+#    #+#             */
/*   Updated: 2022/08/27 16:20:51 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	ft_env(t_struct *shell)
{
	int	n;

	if (g_var.g_var == 0)
	{
		ft_die("environment not found\n");
		return ;
	}
	n = 0;
	while (n < shell->env.len)
	{
		if (shell->env.tmp_con[n] && ft_strlen(shell->env.tmp_con[n]) != 0 && \
		shell->env.tmp_var[n][0] != '?')
		{
			ft_putstr_fd(shell->env.tmp_var[n], shell->output_fd);
			ft_putchar_fd('=', shell->output_fd);
			ft_putstr_fd(shell->env.tmp_con[n], shell->output_fd);
			ft_putstr_fd("\n", shell->output_fd);
		}
		n++;
	}
}

void	ft_check_env(char	**env)
{
	int	i;

	i = 0;
	if (!env)
		g_var.g_var = 0;
	while (env[i])
		i++;
	g_var.g_var = i;
}

int	is_empty(char	*input)
{
	int	i;

	i = -1;
	while (input[++i])
		if (input[i] != '\t' && input[i] != '\v' && input[i] != '\f' \
				&& input[i] != '\n' && input[i] != ' ' && input[i] != '\r')
			return (0);
	return (1);
}

void	verify_if_env_exists(t_struct *shell)
{
	char	*ptr;

	ptr = NULL;
	if (find_env_tmp(shell, shell->frst))
	{
		ptr = shell->env.tmp_con[shell->env.position];
		if (check_export_tow(shell) == 2)
			shell->env.tmp_con[shell->env.position] = \
			ft_strjoin(shell->env.tmp_con[shell->env.position], shell->scnd);
		else
			shell->env.tmp_con[shell->env.position] = ft_strdup(shell->scnd);
		free(ptr);
	}
	else if (!find_env_tmp(shell, shell->frst))
		export_to_env(shell, shell->frst, shell->scnd);
}

void	export_to_env(t_struct *shell, char *new_elem_tab1, char *new_elem_tab2)
{
	int	i;

	shell->env.len++;
	i = 0;
	if (g_var.g_var == 0)
	{
		if (!malloc_env_tmp(shell))
			ft_die_malloc("No space left\n");
		shell->env.tmp_var[0] = ft_strdup(new_elem_tab1);
		shell->env.tmp_con[0] = ft_strdup(new_elem_tab2);
		shell->env.tmp_var[1] = 0;
		shell->env.tmp_con[1] = 0;
		g_var.g_var++;
		return ;
	}
	if (!malloc_env_aux_tmp(shell))
		ft_die_malloc("No space left\n");
	while (i < shell->env.len - 1)
	{
		shell->env_aux.tmp_var[i] = ft_strdup(shell->env.tmp_var[i]);
		shell->env_aux.tmp_con[i] = ft_strdup(shell->env.tmp_con[i]);
		i++;
	}
	next_export (shell, new_elem_tab1, new_elem_tab2);
}
