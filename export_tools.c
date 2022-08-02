/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 12:56:27 by yismaili          #+#    #+#             */
/*   Updated: 2022/08/02 13:03:31 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"includes/minishell.h"

void	ft_export_tool(t_struct *shell)
{
	int		i;
	char	**env_aux;

	i = 1;
	while (shell->arguments[i] && check_export(shell) == 0)
	{
		env_aux = ft_split(shell->arguments[i], '=');
		if (env_aux[0] && shell->arguments[i]
			[ft_strlen(shell->arguments[1]) - 1] != '='
			&& env_aux[1] != NULL)
		{
			verify_if_env_exists(shell, env_aux);
		}
		else if (env_aux[0] && env_aux[1] == NULL )
		{
			env_aux[1] = ft_strdup("");
			verify_if_env_exists(shell, env_aux);
		}
		free(env_aux[0]);
		free(env_aux[1]);
		i++;
	}
}

void	ft_error_eprt(char *cmd)
{
	if (cmd)
	{
		ft_putstr_fd("export: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
	}
}

void	verify_if_env_exists(t_struct *shell, char **env_aux)
{
	if (find_env_tmp(shell, env_aux[0]))
	{
		free(shell->env.tmp_con[shell->env.position]);
		shell->env.tmp_con[shell->env.position] = ft_strdup(env_aux[1]);
	}
	else if (!find_env_tmp(shell, env_aux[0]))
	{
		export_to_env(shell, env_aux[0], env_aux[1]);
	}
}

void	export_to_env(t_struct *shell, char *new_elem_tab1, char *new_elem_tab2)
{
	int	i;

	if (!malloc_env_aux_tmp(shell))
		ft_die_malloc("No space left\n");
	i = 0;
	while (i < shell->env.len)
	{
		shell->env_aux.tmp_var[i] = ft_strdup(shell->env.tmp_var[i]);
		shell->env_aux.tmp_con[i] = ft_strdup(shell->env.tmp_con[i]);
		i++;
	}
	shell->env.len++;
	shell->env_aux.tmp_var[shell->env.len -1] = ft_strdup(new_elem_tab1);
	shell->env_aux.tmp_con[shell->env.len -1] = ft_strdup(new_elem_tab2);
	free1(shell->env.tmp_var);
	free1(shell->env.tmp_con);
	shell->env.tmp_var = shell->env_aux.tmp_var;
	shell->env.tmp_con = shell->env_aux.tmp_con;
	shell->env.tmp_var[shell->env.len] = 0;
	shell->env.tmp_con[shell->env.len] = 0;
}

int	check_export(t_struct *export)
{
	int		i;
	char	**splted;

	i = 0;
	if (export->arguments[1][0] == '=')
		return (1);
	if (g_var == 0)
		return (0);
	splted = ft_split(export->arguments[1], '=');
	while (splted[0][i])
	{
		if (!ft_isalpha(splted[0][i]))
			return (1);
		i++;
	}
	i = 0;
	free(splted);
	return (0);
}