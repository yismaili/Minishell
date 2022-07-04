/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:21:32 by souchen           #+#    #+#             */
/*   Updated: 2022/07/04 17:41:02 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "includes/minishell.h"

bool	there_is_home(t_struct *shell)
{
	if (find_envernement(shell, "HOME"))
		return (true);
	else
		return (false);
}

int	ft_cd(t_struct *shell)
{
	char	*arg_aux;
	bool	home;

	home = there_is_home(shell);
	if (shell->arguments[1])
	{
		arg_aux = ft_strdup(shell->arg.Lechemin);
	}
	else
	{
		if (home == true)
		{
			arg_aux = ft_strdup(shell->home);
		}
		else
		{
			printf("Error/ home not set\n");
			return (1);
		}
	}
	global_number = chdir(arg_aux); // change the current dir
	if (global_number == -1)
		printf("minishell: cd: %s: %s", shell->arguments[1], "no such file or directory\n");
	free(arg_aux);
	return (0);
}

