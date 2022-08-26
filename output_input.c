/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <yismaili@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 14:56:43 by souchen           #+#    #+#             */
/*   Updated: 2022/08/26 17:48:54 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	outredirection(t_struct *shell)
{
	char	*fichier1;

	if (shell->commands[shell->cmp][1] == '>')
	{
		fichier1 = ft_strtrim(&shell->commands[shell->cmp][2], " ");
		if (ft_check_file(shell, fichier1) == 0)
			return (0);
		shell->output_fd = open(fichier1, O_CREAT | O_WRONLY | O_APPEND, 0777);
		if (shell->output_fd == -1)
			return (ft_putstr_fd("Open Error\n", 2), free(fichier1), 0);
	}
	else
	{
		fichier1 = ft_strtrim(&shell->commands[shell->cmp][1], " ");
		if (!fichier1)
			return (0);
		shell->output_fd = open(fichier1, O_CREAT | O_WRONLY | O_TRUNC, 0777);
		if (shell->output_fd == -1)
			return (ft_putstr_fd("Open Error\n", 2), free(fichier1), 0);
	}
	free(fichier1);
	return (1);
}

int	inredirection(t_struct	*shell)
{
	char	**fichier2;
	char	*line;

	line = NULL;
	fichier2 = NULL;
	if (shell->commands[shell->cmp][1] == '<')
	{
		fichier2 = ft_split(&shell->commands[shell->cmp][2], ' ');
		if (!fichier2)
			return (0);
		line = ft_strdup("");
		if (ft_play_herdoc(shell, fichier2[0], line) == 0)
			return (0);
		shell->input_fd = open(fichier2[0], O_RDONLY | O_CREAT, 0777);
		shell->name = ft_strdup(fichier2[0]);
		free(fichier2);
	}
	else
	{
		if (next_inredirection(shell) == 0)
			return (0);
	}
	return (1);
}

int	next_inredirection(t_struct *shell)
{
	char	*fichier2;

	fichier2 = ft_strtrim(&shell->commands[shell->cmp][2], " ");
	if (split_and_cas_error(shell, fichier2) != 1)
		return (0);
	free(fichier2);
	return (1);
}

int	fun_redirection(t_struct *shell)
{
	int	i;
	int	size;
	int	length;

	i = 0;
	size = 0;
	length = 0;
	shell->indice_space = 0;
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
	while (shell->commands[shell->cmp] && \
			(shell->commands[shell->cmp][0] == '<' || \
			shell->commands[shell->cmp][0] == '>'))
	{
		size = ft_strlen(shell->commands[shell->cmp]);
		if (((shell->commands[shell->cmp][3] == '\"' && \
		shell->commands[shell->cmp][size - 1] == '\"' && \
		ft_strlen(&shell->commands[shell->cmp][3]) == 0) ||
		(shell->commands[shell->cmp][2] == '\"' && \
		shell->commands[shell->cmp][size - 1] == '\"' && \
		ft_strlen(&shell->commands[shell->cmp][2]) == 0)))
		{
			return (0);
		}
		if ((shell->commands[shell->cmp][3] == '\'' && \
		shell->commands[shell->cmp][size - 1] == '\'' && \
		ft_strlen(&shell->commands[shell->cmp][3]) == 0) ||
		(shell->commands[shell->cmp][2] == '\'' && \
		shell->commands[shell->cmp][size - 1] == '\'' && \
		ft_strlen(&shell->commands[shell->cmp][2]) == 0))
		{
			return (0);
		}
		if (((shell->commands[shell->cmp][3] == '\"' && \
		shell->commands[shell->cmp][size - 1] == '\"') ||
		(shell->commands[shell->cmp][2] == '\"' && \
		shell->commands[shell->cmp][size - 1] == '\"')) && \
		(shell->quote_cmd % 2 == 0 && shell->dquote_cmd % 2 == 0))
		{
			shell->commands[shell->cmp] = \
			ft_remove_quot(shell->commands[shell->cmp], '\"', shell);
		}
		else if (((shell->commands[shell->cmp][3] == '\'' && \
		shell->commands[shell->cmp][size - 1] == '\'' && \
		ft_strlen((&shell->commands[shell->cmp])[3]) != 0) ||
		(shell->commands[shell->cmp][2] == '\'' && \
		shell->commands[shell->cmp][size - 1] == '\'' && \
		ft_strlen((&shell->commands[shell->cmp])[2]) != 0)) && \
		(shell->quote_cmd % 2 == 0 && shell->dquote_cmd % 2 == 0))
		{
			shell->commands[shell->cmp] = \
			ft_remove_quot(shell->commands[shell->cmp], '\"', shell);
		}
		if (shell->commands[shell->cmp][0] == '>')
		{
			if (outredirection(shell) == 0)
				return (0);
		}
		else if (shell->commands[shell->cmp][0] == '<')
		{
			if (inredirection(shell) == 0)
				return (0);
		}
		shell->cmp++;
	}
	return (1);
}

void	output_input(t_struct	*shell)
{
	if (shell->last_in != -1)
	{
		close(shell->last_in);
	}
	if (shell->output_fd != 1)
	{
		dup2(shell->output_fd, STDOUT_FILENO);
		close(shell->output_fd);
		close(shell->last_in);
	}
	if (shell->input_fd != 0)
	{
		dup2(shell->input_fd, STDIN_FILENO);
		close(shell->input_fd);
	}
}
