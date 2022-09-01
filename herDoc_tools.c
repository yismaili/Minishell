/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herDoc_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <yismaili@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 23:14:54 by yismaili          #+#    #+#             */
/*   Updated: 2022/09/01 17:38:32 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	ft_play_herdoc(t_struct *shell, char *fichier2, char *line)
{
	int		j;

	shell->fd = open(fichier2, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	while (ft_strcmp(line, fichier2))
	{
		j = 0;
		free(line);
		line = readline("herDoc> ");
		if (!line)
			return (0);
		line = herdoc_with_dolars(line, fichier2, shell);
		if (shell->inc1 == 2)
			ft_print_msg(shell, line);
		else if (shell->inc2 == 2)
			ft_print_msg(shell, line);
	}
	close(shell->fd);
	free(line);
	return (1);
}

void	ft_print_msg(t_struct *shell, char	*line)
{
	ft_putchar_fd('\"', shell->fd);
	ft_putstr_fd(line, shell->fd);
	ft_putchar_fd('\"', shell-> fd);
	ft_putstr_fd("\n", shell->fd);
	return ;
}

char	*herdoc_with_dolars(char *line, char *fic, t_struct *shell)
{
	int		j;
	char	*tmp;

	shell->inc1 = 0;
	shell->inc2 = 0;
	j = ft_count_len_ofqut(shell, line, fic);
	tmp = ft_hndl_qot(shell, fic, line, j);
	tmp = search_in_env(j, fic, line, shell);
	return (tmp);
}

char	*ft_hndl_qot(t_struct *shell, char *line, char *fic, int j)
{
	char	*tmp;

	tmp = NULL;
	if (line[ft_strlen(&line[j])] == '\"')
	{
		shell->inc1++;
		tmp = line;
		if (shell->inc1 == 2)
			line = ft_split_cmd2(&line[j], shell);
		if (!ft_strcmp(fic, line))
		{
			line = ft_strdup(tmp);
			shell->inc1 = 0;
		}
	}
	if (line[ft_strlen(&line[j])] == '\'')
		tmp = ft_hndl_qot_next(shell, fic, line, j);
	return (tmp);
}

char	*ft_hndl_qot_next(t_struct *shell, char *line, char *fic, int j)
{
	char	*tmp;

	tmp = NULL;
	if (line[ft_strlen(&line[j])] == '\'')
	{
		shell->inc2++;
		tmp = line;
		if (shell->inc2 == 2)
			line = ft_split_cmd2(&line[j], shell);
		if (!ft_strcmp(fic, line))
		{
			line = ft_strdup(tmp);
			shell->inc2 = 0;
		}
	}
	return (tmp);
}
