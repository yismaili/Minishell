/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:19:21 by souchen           #+#    #+#             */
/*   Updated: 2022/08/18 01:05:28 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"includes/minishell.h"

void	ft_print_export(char **exp, t_struct	*shell)
{
	int	i;
	int	j;

	i = 0;
	while (exp[i])
	{
		j = 0;
		if (ft_strlen(exp[i]) != 1 && exp[i][0] != '?')
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
	if (shell->arguments[i] && check_export(shell, &i) != 1)
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
	char	*ptr;

	i = 1;
	while (shell->arguments[i] && check_export(shell, &i) != 1)
	{
		env_aux = ft_split(shell->arguments[i], '=');
		if (check_export(shell, &i) == 2)
		{
			ptr = env_aux[0];
			env_aux[0] = ft_strtrim(env_aux[0], "+");
			free(ptr);
		}
		if (check_export(shell, &i) == 3)
			if (ft_with_dlr(env_aux, shell) == 1)
				return ;
		if (ft_else(shell, env_aux, i) == 1)
			return ;
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
	if (export->arguments[*i][0] == '=')
	{
		ft_putstr_fd("not a valid identifier\n", 2);
		return (1);
	}
	return (check_export_tow(export));
}
