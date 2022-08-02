/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <souchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 12:56:27 by yismaili          #+#    #+#             */
/*   Updated: 2022/08/02 19:10:23 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"includes/minishell.h"

char	**ft_dup_env(t_struct *shell)
{
	char	**dup_str;
	char	*first_join;
	char	*second_join;
	int		i;

	i = 0;
	dup_str = (char **)malloc(sizeof(char *) * (shell->env.len + 1));
	if (!dup_str)
		return (NULL);
	dup_str[shell->env.len] = 0;
	while (i < shell->env.len)
	{
		first_join = ft_strjoin(shell->env.tmp_var[i], "=");
		second_join = ft_strjoin(first_join, shell->env.tmp_con[i]);
		dup_str[i] = ft_strdup(second_join);
		free(first_join);
		free(second_join);
		i++;
	}
	return (dup_str);
}

void	sort_env(t_struct *env)
{
	char	**dup_env;

	if (g_var == 0)
	{
		ft_die("environment not found\n");
		return ;
	}
	dup_env = ft_dup_env(env);
	swap_env(dup_env);
	ft_print_export(dup_env, env);
}

void	swap_env(char **dup_env)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	while (dup_env[i])
	{
		j = i + 1;
		while (dup_env[j])
		{
			if (ft_strcmp(dup_env[i], dup_env[j]) > 0)
			{
				tmp = dup_env[i];
				dup_env[i] = dup_env[j];
				dup_env[j] = tmp;
			}
			j++;
		}
		i++;
	}
}
