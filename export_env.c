/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <souchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:22:25 by souchen           #+#    #+#             */
/*   Updated: 2022/08/28 17:22:55 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	ft_split_argu(t_struct *shell, char *arguments)
{
	int		m;
	int		n;
	int		p;
	int		j;

	m = 0;
	n = 0;
	p = 0;
	j = 0;
	while (arguments[j] != '\0')
	{
		if (arguments[j] != '=' && j == m)
			shell->frst[m++] = arguments[j];
		else
		{
			if (arguments[j] == '=' && p == 0)
				j++;
			if (arguments[j] == '\0')
				break ;
			shell->scnd[n] = arguments[j];
			p = 1;
			n++;
		}
		j++;
	}
}

int	len_ofarg(char *str)
{
	int	k;

	k = 0;
	while (str[k] != '\0')
	{
		if (str[k] == '=')
			break ;
		k++;
	}
	return (k);
}

void	next_export(t_struct *shell, char *new_elem_tab1, char *new_elem_tab2)
{
	shell->env_aux.tmp_var[shell->env.len - 1] = ft_strdup(new_elem_tab1);
	shell->env_aux.tmp_con[shell->env.len - 1] = ft_strdup(new_elem_tab2);
	ft_free_cmd(shell->env.tmp_var);
	ft_free_cmd(shell->env.tmp_con);
	shell->env.tmp_var = shell->env_aux.tmp_var;
	shell->env.tmp_con = shell->env_aux.tmp_con;
	shell->env.tmp_var[shell->env.len] = 0;
	shell->env.tmp_con[shell->env.len] = 0;
}

int	check_export(t_struct *export)
{
	if (export->arguments[export->i_for_chek][0] == '=')
	{
		ft_putstr_fd("not a valid identifier\n", 2);
		return (1);
	}
	return (check_export_tow(export));
}

void	exp_with_pipe(t_struct *shell)
{
	if (shell->arguments[0][0] == '|' && !shell->arguments[0][1])
	{
		shell->f_pipe = 1;
	}
	else if (shell->arguments[0][0] == '|' && shell->arguments[0][1])
		shell->arguments[0] = &shell->arguments[0][1];
}
