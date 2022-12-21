/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 11:14:45 by lmery             #+#    #+#             */
/*   Updated: 2022/12/21 02:01:51 by gle-mini         ###   ########.fr       */
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

char *env_var_find(char *to_find, char **env)
{
	char *new;
	int i;

	i = 0;
	new = NULL;
	while (env[i])
	{
		if (ft_strncmp(to_find, env[i], ft_strlen(to_find)) == 0 && env[i][ft_strlen(to_find)] == '=')
		{
			//Souviens toi de gerer le fail de malloc
			new = malloc(sizeof(char) * (ft_strlen(env[i]) - (ft_strlen(to_find))));
			ft_strlcpy(new, &env[i][ft_strlen(to_find) + 1], ft_strlen(env[i]) - ft_strlen(to_find));
			break;
		}
		i++;
	}
	if (new == NULL)
	{
		new = malloc(sizeof(char) * 1);
		new[0] = '\0';
	}
	return (new);
}

char *ft_strcpy(char *dest, const char *src)
{
  return ft_memcpy(dest, src, ft_strlen(src) + 1);
}


char *ft_strncpy(char *dst, const char *src, register size_t n)
{
	if (n != 0) {
		register char *d = dst;
		register const char *s = src;

		do {
			if ((*d++ = *s++) == 0) {
				/* NUL pad the remaining n-1 bytes */
				while (--n != 0)
					*d++ = 0;
				break;
			}
		} while (--n != 0);
	}
	return (dst);
}

char *ft_strncat(char *s1, const char *s2, size_t n)
{
    size_t len1 = ft_strlen(s1);
    size_t len2 = ft_strlen(s2);

    if (len2 < n) {
	ft_strcpy(&s1[len1], s2);
    } else {
	ft_strncpy(&s1[len1], s2, n);
	s1[len1 + n] = '\0';
    }
    return s1;
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
	//If the env variable exist
	new_env_var = env_var_find(&text[i + 1], env);
	//Souviens toi de gerer le fail de malloc
	new_text = malloc(sizeof(char) * (i + ft_strlen(new_env_var)));
	ft_strlcpy(new_text, text, i + 1);
	new_text = ft_strncat(new_text, new_env_var, ft_strlen(new_env_var)); 
	free(new_env_var);
	new_env_var = NULL;
	free(token->text);
	token->text = new_text;
	/*
	printf("text = %s", new_text);
	
	printf("new size = %zu\n", i + ft_strlen(new_env_var));
	printf ("new token  = %s\n", new_env_var);
	printf("text = %s\n", &text[i+1]);
	printf("env_var_len = %d\n", env_var_len);
	*/
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
		/*
		if (token->type == TOKEN_ENV)
		{
			//ft_expand_one_token(token, env);
		}
		*/
		lst_token = lst_token->next;
	}
}

