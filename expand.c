/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 11:14:45 by lmery             #+#    #+#             */
/*   Updated: 2022/12/20 12:43:28 by lmery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

char	**ft_get_env(char **env)
{
	return (env);
}

static void	ft_expand_one_token(t_token *token, char **env)
{
	char 	*new;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = NULL;
	len = ft_strlen(token->text);
	while (env[i])
	{
		if (ft_strncmp(token->text, env[i], len) == 0 && env[i][len] == '=')
		{
			// printf("char: %c\n", env[i][len +1]);
			//Souviens toi de gerer le fail de malloc
			if (!(new = malloc (sizeof (char) * (ft_strlen(env[i]) - (len)))))
				return ;
			ft_strlcpy(new, &env[i][len + 1], ft_strlen(env[i]) - (len));
		}
		i++;
	}
	free(token->text);
	token->text = new;
}

void ft_expand(t_list *lst_token, char **env)
{
	t_token *token;
	while (lst_token != NULL)
	{
		token = lst_token->content;
		if (token->type == TOKEN_ENV)
		{
			ft_expand_one_token(token, env);
		}
		lst_token = lst_token->next;
	}
}

