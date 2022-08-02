/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <souchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:20:16 by souchen           #+#    #+#             */
/*   Updated: 2022/08/02 18:01:01 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*ft_split_cmd(char	*cmd)
{
	char	*join;

	join = NULL;
	if (ft_strchr(cmd, '\"'))
		join = ft_remove_quot(cmd, '\"');
	else if (ft_strchr(cmd, '\''))
		join = ft_remove_quot(cmd, '\'');
	return (join);
}

char	**split_arg(char **spl, char *cmd_joined, t_struct *shell)
{
	int		i;
	char	**spled;

	i = 0;
	spl = NULL;
	spled = NULL;
	cmd_joined = NULL;
	shell->arguments = ft_split(shell->line_commande, ' ');
	spl = ft_split(shell->line_commande, '|');
	while (spl[i])
	{
		cmd_joined = ft_strjoin(spl[i], spl[i + 1]);
		i++;
	}
	spled = ft_split(cmd_joined, ' ');
	ft_free_cmd(spl);
	free(spl);
	free(cmd_joined);
	return (spled);
}

void	cmd_splited(char **spled, t_struct *shell)
{
	int	i;

	i = 0;
	shell->cmd_splited = (char **)malloc(sizeof(char *) * 1000000);
	while (spled[i])
	{
		shell->cmd_splited[i] = ft_strdup(spled[i]);
		i++;
	}
}
