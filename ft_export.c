/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <yismaili@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:19:21 by souchen           #+#    #+#             */
/*   Updated: 2022/08/27 21:17:39 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"includes/minishell.h"

void	ft_print_export(char **exp, t_struct *shell)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	while (exp[++i])
	{
		j = 0;
		if (ft_strlen(exp[i]) != 1 && exp[i][0] != '?')
		{
				k = 0;
			ft_putstr_fd("declare -x ", shell->output_fd);
			while (exp[i][j])
			{
				ft_putchar_fd(exp[i][j], shell->output_fd);
				if (exp[i][j] == '=' && k == 0)
				{
					ft_putchar_fd('"', shell->output_fd);
					k = 1;
				}
				j++;
			}
			ft_print_qot(shell);
		}
	}
}

void	ft_print_qot(t_struct *shell)
{
	ft_putchar_fd('"', shell->output_fd);
	ft_putchar_fd('\n', shell->output_fd);
}

void	ft_export(t_struct *shell)
{
	int	j;

	j = 0;
	shell->f_pipe = 0;
	shell->i_for_chek = 1;
	if (shell->arguments[0][0] == '|')
		shell->f_pipe = 1;
	while (shell->variable == 1 && shell->arguments[j] != NULL && \
	shell->f_pipe != 0)
	{
		shell->arguments[j] = shell->arguments[j + 1];
		j++;
	}
	if (!shell->arguments[1])
		sort_env(shell);
	while (shell->arguments[shell->i_for_chek])
	{
		if (shell->arguments[shell->i_for_chek] && \
		check_export(shell) != 1 && shell->f_pipe == 0)
			export_with_arg(shell, shell->arguments[shell->i_for_chek]);
		else if (shell->arguments[shell->i_for_chek] && \
		check_export(shell) == 1)
			ft_identifier_export(shell);
		shell->i_for_chek++;
	}	
}

void	ft_malloc_tmp(t_struct *shell, char *arguments)
{
	shell->scnd = NULL;
	shell->frst = NULL;
	shell->frst = malloc(sizeof(char) * len_ofarg(arguments));
	if ((int)ft_strlen(arguments) != len_ofarg(arguments))
		shell->scnd = malloc(sizeof(char) * ft_strlen(arguments) - \
		len_ofarg(arguments) - 1);
}

void	export_with_arg(t_struct *shell, char *arguments)
{
	int		i;
	char	*ptr;
	int		j;

	i = 1;
	j = 0;
	ft_malloc_tmp(shell, arguments);
	ft_split_argu(shell, arguments);
	if (check_export(shell) == 2)
	{
		ptr = shell->frst;
		shell->frst = ft_strtrim(shell->frst, "+");
		free(ptr);
	}
	if (check_export(shell) == 3)
	{
		shell->frst = ft_strdup(ft_return_con(shell));
		if (ft_with_dlr(shell) == 1)
			return ;
	}
	if (ft_else(shell, i) == 1)
		return ;
	free(shell->frst);
	free(shell->scnd);
}
