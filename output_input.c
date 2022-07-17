/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 14:56:43 by souchen           #+#    #+#             */
/*   Updated: 2022/07/16 18:25:30 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
void	outredirection(t_struct *shell)
{
	char	*fichier1;
	if (shell->commands[shell->cmp][1] == '>')
	{
		fichier1 = ft_strtrim(&shell->commands[shell->cmp][2], " ");
		shell->output_fd = open(fichier1, O_CREAT | O_WRONLY | 0777);
		if (shell->output_fd == -1)
		{
			printf("Open Error\n");
			exit(0);
		}
		free(fichier1);
	}
	else
	{
		fichier1 = ft_strtrim(&shell->commands[shell->cmp][1], " ");
		shell->output_fd = open(fichier1, O_CREAT |O_WRONLY, 0777);
		if (shell->output_fd == -1)
		{
			printf("Open error\n");
			exit(0);
		}
		free(fichier1);
	}
}

void	inredirection(t_struct *shell)
{
	char	*fichier2;
	char	*line;
	int		fd;
	
	if (shell->commands[shell->cmp][1] == '<')
	{
		fichier2 = ft_strtrim(&shell->commands[shell->cmp][2], " ");
		line = ft_strdup("");
		fd = open(fichier2, O_CREAT | O_WRONLY, 0777);
		if (fd == -1)
		{
			printf("Open error\n");
			exit(0);
		}
		while (ft_strncmp(line, fichier2, ft_strlen(fichier2) \
					|| ft_strlen(line) != ft_strlen(fichier2)))
		{
			free(line);
			line = readline("herDoc> ");
		}
		close(fd);
		free(line);
	}
	else
	{
		fichier2 = ft_strtrim(&shell->commands[shell->cmp][1], " ");
		shell->input_fd = open(fichier2, O_RDONLY, 0777);
		if (shell->input_fd == -1)
		{
			printf("Open error\n");
			exit(0);
		}
	}
}

void output_input(t_struct *shell)
{
	if(shell->output_fd != 1)
	{
		dup2(shell->output_fd, STDOUT_FILENO);
		close(shell->output_fd);
	}
	if(shell->input_fd != 0)
	{
		dup2(shell->input_fd, STDIN_FILENO);
		close(shell->input_fd);
	}
}
