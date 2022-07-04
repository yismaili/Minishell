/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:22:00 by souchen           #+#    #+#             */
/*   Updated: 2022/07/04 17:41:17 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "includes/minishell.h"
void	ft_pwd(void)
{
	char	*buf;

	buf = get_current_dir();
	if (!buf)
		return ;
	printf("%s\n", buf);
	free(buf);
}

