/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <souchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 23:14:00 by yismaili          #+#    #+#             */
/*   Updated: 2022/08/20 12:02:19 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	split_arg(t_struct *shell, char *cmd_joined)
{
	int		i;

	i = 0;
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
			ft_strncmp(shell->arguments[i], "echo", 4))
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
	char	*tmp;

	if (((fichier2[0] == '\"' || fichier2[0] == '\'') || \
				(fichier2[ft_strlen(fichier2) - 1] == '\"' || \
				fichier2[ft_strlen(fichier2) - 1] == '\'')) && \
			(ft_strlen(fichier2) > 2))
	{
		tmp = fichier2;
		fichier2 = ft_split_cmd2(fichier2, shell);
		free(tmp);
	}
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
