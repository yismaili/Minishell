/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <yismaili@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 23:14:00 by yismaili          #+#    #+#             */
/*   Updated: 2022/08/26 15:43:40 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	split_arg(t_struct *shell, char *cmd_joined)
{
	if ((((&shell->line_commande[shell->pos])[0] == '\"') || \
		((&shell->line_commande[shell->pos])[0] == '\'')) || \
		(((&shell->line_commande[shell->pos])[shell->size - 1] == '\"') || \
		((&shell->line_commande[shell->pos])[shell->size - 1] == '\'')))
	{
		cmd_joined = ft_split_cmd(shell->line_commande, shell);
		shell->arguments = ft_split(cmd_joined, ' ');
		to_remove_quotes(shell);
		free(cmd_joined);
	}
	else
		shell->arguments = ft_split(shell->line_commande, ' ');
}

void	to_remove_quotes(t_struct *shell)
{
	char	*tmp;
	char	*tmp_tow;
	int		i;

	i = 0;
	while (shell->arguments[i] != NULL && \
		(ft_strncmp(shell->arguments[i], "echo", 4) && \
		ft_strncmp(&shell->arguments[0][1], "echo", 4)))
	{
		tmp = shell->arguments[i];
		shell->arguments[i] = ft_remove_quot(shell->arguments[i], '\"', shell);
		tmp_tow = shell->arguments[i];
		shell->arguments[i] = ft_remove_quot(shell->arguments[i], '\'', shell);
		free(tmp);
		free(tmp_tow);
		i++;
	}
}

int	split_and_cas_error(t_struct *shell, char *fichier2)
{
	shell->input_fd = open(fichier2, O_RDONLY, 0777);
	if (shell->input_fd == -1)
		return (ft_putstr_fd("Open Error\n", 2), free(fichier2), 0);
	return (1);
}

void	arg_func(t_struct *shell)
{
	char	*cmd_joined;

	shell->indice = 0;
	shell->quote = 0;
	shell->double_quote = 0;
	cmd_joined = NULL;
	ft_check_quote(shell);
	shell->size = ft_strlen(&shell->line_commande[shell->pos]);
	ft_check_space(shell);
	ft_check_quote_pos(shell, cmd_joined);
}
