/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:19:21 by souchen           #+#    #+#             */
/*   Updated: 2022/08/16 16:38:51 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"includes/minishell.h"

void	ft_print_export(char **exp, t_struct	*shell)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (exp[i])
	{
		j = 0;
		if (ft_strlen(exp[i]) != 1)
		{
			ft_putstr_fd("declare -x ", shell->output_fd);
			while (exp[i][j])
			{
				ft_putchar_fd(exp[i][j], shell->output_fd);
				if (exp[i][j] == '=')
					ft_putchar_fd('"', shell->output_fd);
				j++;
			}
			ft_putchar_fd('"', shell->output_fd);
			ft_putchar_fd('\n', shell->output_fd);
		}
		i++;
	}
}

void	ft_export(t_struct *shell)
{
	int		i;

	i = 1;
	if (!shell->arguments[1])
		sort_env(shell);
	// if (ft_strchr(shell->arguments[1], '+'))
	// {
	// 	printf("hey\n");
	// }
	if (shell->arguments[i] && check_export(shell, &i) == 0)
		export_with_arg(shell);
	else if (shell->arguments[i] && check_export(shell, &i) == 1)
	{
		ft_putstr_fd("Export: ", 2);
		ft_putstr_fd(shell->arguments[1], 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
	}
}

void	export_with_arg(t_struct *shell)
{
	char	**env_aux;
	int		i;

	i = 1;
	while (shell->arguments[i] && check_export(shell, &i) == 0)
	{
		env_aux = ft_split(shell->arguments[i], '=');
		if (g_var.g_var == 0)
		{
			verify_if_env_exists(shell, env_aux);
			ft_free_cmd(env_aux);
			return ;
		}
		if (env_aux[0] && shell->arguments[i] \
				[ft_strlen(shell->arguments[1]) - 1] != '=' && \
				env_aux[1] != NULL)
			verify_if_env_exists(shell, env_aux);
		else if (env_aux[0] && env_aux[1] == NULL)
		{
			env_aux[1] = NULL;
			verify_if_env_exists(shell, env_aux);
		}
		ft_free_cmd(env_aux);
		i++;
	}
}

void	next_export(t_struct *shell, char *new_elem_tab1, char *new_elem_tab2)
{
	ft_free_cmd(shell->env.tmp_var);
	ft_free_cmd(shell->env.tmp_con);
	shell->env_aux.tmp_var[shell->env.len - 1] = ft_strdup(new_elem_tab1);
	shell->env_aux.tmp_con[shell->env.len - 1] = ft_strdup(new_elem_tab2);
	shell->env.tmp_var = shell->env_aux.tmp_var;
	shell->env.tmp_con = shell->env_aux.tmp_con;
	shell->env.tmp_var[shell->env.len] = 0;
	shell->env.tmp_con[shell->env.len] = 0;
}

int	check_export(t_struct *export, int *i)
{
	int		j;
	char	**splted;

	j = 0;
	if (export->arguments[*i][0] == '=')
	{
		ft_putstr_fd("not a valid identifier\n", 2);
		return (1);
	}
	if (g_var.g_var == 0)
		return (0);
	splted = ft_split(export->arguments[1], '=');
	while (splted[0][j])
	{
		if (!ft_isalpha(splted[0][j]))
		{
			ft_free_cmd(splted);
			return (1);
		}
		j++;
	}
	ft_free_cmd(splted);
	return (0);
}
