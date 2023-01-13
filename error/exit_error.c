/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 03:29:09 by lmery             #+#    #+#             */
/*   Updated: 2023/01/13 03:48:56 by lmery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

void	exit_error(char *msg)
{
	printf(_ORANGE _BOLD "Error detected : %s\n"_END, msg);
	// Utitiser ici le garbage collector pour tout clean et 
	// quitter MinisheLLD proprement"
	exit (0);
	return ;
}
