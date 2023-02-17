/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 04:20:53 by lmery             #+#    #+#             */
/*   Updated: 2023/02/17 04:29:54 by lmery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

void	builtin_exit()
{
	printf( _ORANGE "exit\n" _END);
	exit(0);
	//trouver le moyen d'appeler free all
}