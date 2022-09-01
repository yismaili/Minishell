/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <yismaili@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:22:00 by souchen           #+#    #+#             */
/*   Updated: 2022/08/28 21:41:20 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include <limits.h>

char	*get_current_dir(void)
{
	char	buf[PATH_MAX];

	getcwd(buf, PATH_MAX);
	return (strdup(buf));
}

void	ft_pwd(t_struct *shell)
{
	char	*buf;

	buf = get_current_dir();
	if (!buf)
		return ;
	ft_putstr_fd(buf, shell->output_fd);
	ft_putstr_fd("\n", shell->output_fd);
	free(buf);
}

int	check_export_tow(t_struct *export)
{
	char	**splted;

	if (g_var.g_var == 0)
		return (0);
	splted = ft_split(export->arguments[export->i_for_chek], '=');
	if (splted[0][0] == '$')
	{
		ft_free_cmd(splted);
		return (3);
	}
	if (splted[0][ft_strlen(splted[0]) - 1] == '+')
	{
		ft_free_cmd(splted);
		return (2);
	}
	return (ft_loop(splted));
}

int	ft_loop(char **splted)
{
	int		j;

	j = 0;
	if (splted[0][0] == '_')
		return (0);
	if (!ft_isalpha(splted[0][0]))
	{
		ft_free_cmd(splted);
		return (1);
	}
	ft_free_cmd(splted);
	return (0);
}

int	check_export_con(char *export)
{
	int		j;

	j = 0;
	if (!export)
		return (3);
	if (export[0] == '_')
		return (0);
	if (export[ft_strlen(export) - 1] == '+')
		return (2);
	if (!ft_isalpha(export[0]))
		return (1);
	return (0);
}
