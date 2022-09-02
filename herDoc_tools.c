/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herDoc_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <yismaili@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 23:14:54 by yismaili          #+#    #+#             */
/*   Updated: 2022/09/02 01:41:52 by yismaili         ###   ########.fr       */
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
		shell->inc1 = 0;
		shell->inc2 = 0;
		free(line);
		line = readline("herDoc> ");
		if (!line)
			return (0);
		if (ft_strchr(line, '$'))
			line = herdoc_with_dolars(line, fichier2, shell);
		else if (!ft_strchr(line, '$'))
			if (ft_strcmp(line, fichier2))
				ft_putendl_fd(line, shell->fd);		
		if (shell->inc1 >= 1)
			ft_print_msg(shell, line);
		else if (shell->inc2 >= 1)
			ft_print_msg_qot(shell, line);
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

void	ft_print_msg_qot(t_struct *shell, char	*line)
{
	ft_putchar_fd('\'', shell->fd);
	ft_putstr_fd(line, shell->fd);
	ft_putchar_fd('\'', shell-> fd);
	ft_putstr_fd("\n", shell->fd);
	return ;
}

char	*herdoc_with_dolars(char *line, char *fic, t_struct *shell)
{
	int		j;
	char	*tmp;
	char	*ptr;

	shell->inc1 = 0;
	shell->inc2 = 0;
	j = ft_count_len_ofqut(shell, line, fic);
	tmp = NULL;
	
		if (shell->inc1 >= 1)
		{
			printf("HERE\n");
			ptr = line;
			line = ft_hndl_qot(shell, line, fic);
			free(ptr);
		}
		else if (shell->inc2 >= 1)
		{
			ptr = line;
			line = ft_hndl_qot_next(shell, line, fic);
			free(ptr);
		}
	
	tmp = search_in_env(j, fic, line, shell);
	return (tmp);
}

char	*ft_hndl_qot(t_struct *shell, char *line, char *fic)
{
	char	*tmp;
	char *temp;

	tmp = NULL;
		tmp = line;
		line = ft_split_cmd2(line, shell);
		if (!ft_strcmp(fic, line))
		{
			temp = line;
			line = ft_strdup(tmp);
			free(temp);
		}
	return (line);
}

char	*ft_hndl_qot_next(t_struct *shell, char *line, char *fic)
{
	char	*tmp;

	tmp = NULL;
		tmp = line;
		line = ft_split_cmd2(line, shell);
		if (!ft_strcmp(fic, line))
		{
			line = ft_strdup(tmp);
		}
	return (line);
}
