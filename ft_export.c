/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <souchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:19:21 by souchen           #+#    #+#             */
/*   Updated: 2022/08/02 15:28:24 by souchen          ###   ########.fr       */
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
	if (shell->arguments[i] && check_export(shell) == 0)
		export_with_arg(shell);
	else if (shell->arguments[i] && check_export(shell) == 1)
		printf("export: %s: not a valid identifier\n", shell->arguments[1]);
}

void	export_with_arg(t_struct *shell)
{
	char	**env_aux;
	int		i;

	i = 1;
	while (shell->arguments[i] && check_export(shell) == 0)
	{
		env_aux = ft_split(shell->arguments[i], '=');
		if (env_aux[0] && shell->arguments[i] \
				[ft_strlen(shell->arguments[1]) - 1] != '=' && \
				env_aux[1] != NULL)
			verify_if_env_exists(shell, env_aux);
		else if (env_aux[0] && env_aux[1] == NULL)
		{
			env_aux[1] = ft_strdup("");
			verify_if_env_exists(shell, env_aux);
		}
		free(env_aux[0]);
		free(env_aux[1]);
		free(env_aux);
		env_aux = NULL;
		i++;
	}
}

void	next_export(t_struct *shell, char *new_elem_tab1, char *new_elem_tab2)
{
	int	i;

	i = 0;
	if (g_var == 0)
	{
		shell->env_aux.tmp_var[0] = ft_strdup(new_elem_tab1);
		shell->env_aux.tmp_con[0] = ft_strdup(new_elem_tab2);
		shell->env.tmp_var = shell->env_aux.tmp_var;
		shell->env.tmp_con = shell->env_aux.tmp_con;
		return ;
	}
	while (i < shell->env.len)
	{
		shell->env_aux.tmp_var[i] = ft_strdup(shell->env.tmp_var[i]);
		shell->env_aux.tmp_con[i] = ft_strdup(shell->env.tmp_con[i]);
		i++;
	}
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
	free(splted);
	return (0);
}
