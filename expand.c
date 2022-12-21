/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 11:14:45 by lmery             #+#    #+#             */
/*   Updated: 2022/12/21 23:32:11 by gle-mini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

char	**ft_get_env(char **env)
{
	return (env);
}

/*
static void	expand_one_token(t_token *token, char **env)
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
*/


static char *env_var_find(char *to_find, char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(to_find, env[i], ft_strlen(to_find)) == 0 && env[i][ft_strlen(to_find)] == '=')
		{
			return (&env[i][ft_strlen(to_find) + 1]);
		}
		i++;
	}
	return (NULL);
}


static void	expand_token(t_token *token, char **env)
{
	int	env_var_len;
	int i;
	char *text;
	char *new_text;
	char *new_env_var;

	i = 0;
	env_var_len = 0;
	text = token->text;
	while (text[i] != '$')
		i++;
	while (text[i + env_var_len] != '\0' && text[i + env_var_len] != ' ' && text[i + env_var_len] != is_special(text[i + env_var_len]))
		env_var_len++;
	env_var_len--;
	// If the $ is only
	if (env_var_len == 0)
		return;
	new_env_var = env_var_find(&text[i + 1], env);
	if (new_env_var == NULL)
		new_text = malloc(sizeof(char) * (i + 0));
	//Souviens toi de gerer le fail de malloc
	else 
		new_text = malloc(sizeof(char) * (i + ft_strlen(new_env_var)));
	ft_strlcpy(new_text, text, i + 1);
	if (new_env_var != NULL)
		new_text = ft_strncat(new_text, new_env_var, ft_strlen(new_env_var)); 
	free(token->text);
	token->text = new_text;
}

static t_bool is_env_var(char *str)
{
	int i;
	
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (true);
		i++;
	}
	return (false);
}

void ft_expand(t_list *lst_token, char **env)
{
	t_token *token;
	while (lst_token != NULL)
	{
		token = lst_token->content;
		if (is_env_var(token->text))
			expand_token(token, env);	
		lst_token = lst_token->next;
	}
}

