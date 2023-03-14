/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 20:03:26 by lmery             #+#    #+#             */
/*   Updated: 2023/03/14 20:54:37 by gle-mini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

int	builtin_lld(char **cmd)
{
	if (ft_maplen_secure(cmd) > 1)
		ft_print_error(_BLUE_LLD "Builtin LLD : No options available yet\n" \
		_END, "", "");
	else
	{
		ft_putstr_fd(_ORANGE2 \
		"\n----------------------------------------------------\
		-------\n", STDOUT_FILENO);
		ft_putstr_fd(_BLUE_LLD _BOLD \
		"\n\t***   You have found an easter egg !   ***\n\n", STDOUT_FILENO);
		ft_putstr_fd(_END _ORANGE \
		" \t     Wanna join the amazing BDE LLD ? \n", STDOUT_FILENO);
		ft_putstr_fd(_BOLD \
		"   \t      Send us a message on Discord\n\n", STDOUT_FILENO);
		ft_putstr_fd(_END \
		"  \t      >>>> s.bde42.fr/discord <<<<\n", STDOUT_FILENO);
		ft_putstr_fd(_ORANGE2 \
		"\n-----------------------------------------------------------\n\n" \
		_END, STDOUT_FILENO);
	}
	return (42);
}
