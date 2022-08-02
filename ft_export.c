/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:19:21 by souchen           #+#    #+#             */
/*   Updated: 2022/08/02 13:05:24 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"includes/minishell.h"

void	ft_print_export(char **export, t_struct	*shell)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (export[i])
	{
		j = 0;
		if (ft_strlen(export[i]) != 1)
		{
			ft_putstr_fd("declare -x ", shell->output_fd);
			while (export[i][j])
			{
				ft_putchar_fd(export[i][j], shell->output_fd);
				if (export[i][j] == '=')
					ft_putchar_fd('"', shell->output_fd);
				j++;
			}
			ft_putchar_fd('"', shell->output_fd);
			ft_putchar_fd('\n', shell->output_fd);
		}
		i++;
	}
}

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
	char	**tmp;

	if (g_var == 0)
	{
		ft_die("environment not found\n");
		return ;
	}
	dup_env = ft_dup_env(env);
	tmp = dup_env;
	dup_env = ft_swap_env(dup_env);
	ft_print_export(dup_env, env);
	ft_free_cmd(tmp);
	free(tmp);
}

void	ft_export(t_struct *shell)
{
	int		i;

	i = 1;
	if (!shell->arguments[1])
		sort_env(shell);
	if (shell->arguments[i] && check_export(shell) == 0)
		ft_export_tool(shell);
	else if (shell->arguments[i] && check_export(shell) == 1)
		ft_error_eprt(shell->arguments[1]);
}
