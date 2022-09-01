/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <souchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:22:05 by souchen           #+#    #+#             */
/*   Updated: 2022/08/28 16:14:21 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	ft_unset(t_struct *shell)
{
	int	i;

	i = 1;
	if (!shell->arguments[1])
		return ;
	if (shell->arguments[1][0] == '?')
	{
		ft_putstr_fd("Minishell: unset: `?': not a valid identifier\n", 2);
		return ;
	}
	while (shell->arguments[i])
	{
		if (check_unset(shell->arguments[i]) != 0)
		{
			ft_putstr_fd("Minishell: unset: ` ': not a valid identifier\n", 2);
			return ;
		}
		if (find_env_tmp(shell, shell->arguments[i]))
			remove_env(shell);
		i++;
	}
}

int	check_unset(char *arg)
{
	if (arg[0] == '_')
		return (0);
	if (!ft_isalpha(arg[0]))
		return (1);
	return (0);
}

void	remove_env(t_struct *shell)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	shell->env.len--;
	g_var.g_var--;
	if (!malloc_env_aux_tmp(shell))
		ft_die_malloc("No spece lift\n");
	while (i < shell->env.len +1)
	{
		if (i != shell->env.position)
		{
			shell->env_aux.tmp_var[j] = ft_strdup(shell->env.tmp_var[i]);
			shell->env_aux.tmp_con[j] = ft_strdup(shell->env.tmp_con[i]);
			j++;
		}
		i++;
	}
	shell->env_aux.tmp_var[j] = NULL;
	shell->env_aux.tmp_con[j] = NULL;
	ft_free_env(shell->env.tmp_var);
	ft_free_env(shell->env.tmp_con);
	shell->env.tmp_var = shell->env_aux.tmp_var;
	shell->env.tmp_con = shell->env_aux.tmp_con;
}

int	malloc_env_aux_tmp(t_struct *shell)
{
	shell->env_aux.tmp_var = malloc(sizeof(char *) * (shell->env.len + 1));
	if (!shell->env_aux.tmp_var)
		return (0);
	shell->env_aux.tmp_con = malloc(sizeof(char *) * (shell->env.len + 1));
	if (!shell->env_aux.tmp_con)
		return (0);
	return (1);
}
