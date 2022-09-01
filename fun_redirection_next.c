/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fun_redirection_next.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <yismaili@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 23:14:00 by yismaili          #+#    #+#             */
/*   Updated: 2022/09/01 17:37:54 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	cas_error_quote(t_struct *shell, int size)
{
	if (((shell->commands[shell->cmp][3] == '\"' && \
					shell->commands[shell->cmp][size - 1] == '\"' && \
					ft_strlen(&shell->commands[shell->cmp][3]) == 2) || \
				(shell->commands[shell->cmp][2] == '\"' && \
				shell->commands[shell->cmp][size - 1] == '\"' && \
				ft_strlen(&shell->commands[shell->cmp][2]) == 2)) || \
			(shell->quote_cmd % 2 != 0 || \
				shell->dquote_cmd % 2 != 0))
	{
		return (0);
	}
	if (((shell->commands[shell->cmp][3] == '\'' && \
				shell->commands[shell->cmp][size - 1] == '\'' && \
				ft_strlen(&shell->commands[shell->cmp][3]) == 2) || \
			(shell->commands[shell->cmp][2] == '\'' && \
			shell->commands[shell->cmp][size - 1] == '\'' && \
			ft_strlen(&shell->commands[shell->cmp][2]) == 2)) || \
			(shell->quote_cmd % 2 != 0 && \
			shell->dquote_cmd % 2 != 0))
	{
		return (0);
	}
	return (1);
}

void	remove_quote_to_file(t_struct *shell, int size)
{
	char	*tmp;

	if (((shell->commands[shell->cmp][3] == '\"' && \
					shell->commands[shell->cmp][size - 2] == '\"') || \
				(shell->commands[shell->cmp][2] == '\"' && \
				shell->commands[shell->cmp][size - 1] == '\"')))
	{
		tmp = shell->commands[shell->cmp];
		shell->commands[shell->cmp] = \
			ft_remove_quot(shell->commands[shell->cmp], '\"', shell);
		free(tmp);
	}
	else if (((shell->commands[shell->cmp][3] == '\'' && \
					shell->commands[shell->cmp][size - 1] == '\'' && \
					ft_strlen((&shell->commands[shell->cmp])[3]) != 0) ||
				(shell->commands[shell->cmp][2] == '\'' && \
				shell->commands[shell->cmp][size - 1] == '\'' && \
				ft_strlen((&shell->commands[shell->cmp])[2]) != 0)))
	{
		tmp = shell->commands[shell->cmp];
		shell->commands[shell->cmp] = \
			ft_remove_quot(shell->commands[shell->cmp], '\"', shell);
		free(tmp);
	}
}

void	ft_dup_rdtion(t_struct *shell)
{
	int	length;
	int	i;

	length = 0;
	i = 0;
	while (shell->commands[shell->cmp][i] != '\0')
	{
		if (shell->commands[shell->cmp][i] == ' ')
			length++;
		i++;
	}
	if (length == (int)ft_strlen(shell->commands[shell->cmp]))
	{
		shell->line_commande = ft_strdup(shell->commands[shell->cmp + 1]);
		shell->indice_space = 1;
	}
	else
	{
		shell->line_commande = ft_strdup(shell->commands[shell->cmp]);
		shell->space = 2;
	}
	if (shell->divise.number_command > 1)
		shell->cmp++;
}

int	fun_redirection(t_struct *shell)
{
	int	size;

	ft_dup_rdtion(shell);
	while (shell->commands[shell->cmp] && \
			(shell->commands[shell->cmp][0] == '<' || \
			shell->commands[shell->cmp][0] == '>'))
	{
		shell->not_alpha2 = 0;
		size = (int)ft_strlen(shell->commands[shell->cmp]);
		cmp_q(shell);
		if (ft_next_redirection(shell, size) == 0)
			return (0);
		shell->cmp++;
	}
	return (1);
}

void	cmd_not_found3(char *fichier)
{
	ft_putstr_fd("minishell:", 2);
	ft_putstr_fd(fichier, 2);
	ft_putstr_fd(": command not found\n", 2);
}
