/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <souchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:22:12 by souchen           #+#    #+#             */
/*   Updated: 2022/06/22 11:24:26 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "includes/minishell.h"


int	initial_path(t_struct *shell)
{
	char	*path_next;
	int		i;
	path_next = ft_strdup(find_envernement(shell, "PATH"));
	if (!path_next)
		return (0);
	shell->path = ft_split(path_next, ':');
	i = 0;
	while (shell->path[i])
	{
		shell->path[i] = ft_strjoin(shell->path[i], "/");
		i++;
	}
	free(path_next);
	return (1);
}
void envernoment(t_struct *shell)
{
	extern char **environ;
	create_envernement(shell, environ);
	initial_path(shell);
	shell->home = ft_strdup(find_envernement(shell, "HOME"));
}
