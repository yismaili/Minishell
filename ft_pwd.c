/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:22:00 by souchen           #+#    #+#             */
/*   Updated: 2022/08/18 17:07:44 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*get_current_dir(void)
{
	size_t	size;
	char	*buf;

	size = 2000;
	buf = NULL;
	buf = getcwd(buf, size);
	return (buf);
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
	splted = ft_split(export->arguments[1], '=');
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
	while (splted[0][j])
	{
		if (!ft_isalpha(splted[0][j]))
		{
			ft_free_cmd(splted);
			return (1);
		}
		j++;
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
	if (export[ft_strlen(export) - 1] == '+')
		return (2);
	while (export[j])
	{
		if (!ft_isalpha(export[j]))
			return (1);
		j++;
	}
	return (0);
}
