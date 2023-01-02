/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 11:14:45 by lmery             #+#    #+#             */
/*   Updated: 2023/01/01 14:01:17 by gle-mini         ###   ########.fr       */
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



char *ft_strchr (const char *s, int c)
{
	const char ch = c;

	while(*s != ch)
	{
		if (*s == '\0')
			return (NULL);
		s++;
	}
	return (char *) s;
}



size_t	my_strcspn (const char *s, const char *reject)
{
	size_t count = 0;
	t_bool in_quote;

	in_quote = false;
	while (*s != '\0')
	{
		if (*s == '\'')
			in_quote = !in_quote;
		if ((ft_strchr (reject, *s) == NULL) || in_quote == true)
			++s, ++count;
		else
			return (count);
	}

	return (count);
}


size_t	ft_strcspn (const char *s, const char *reject)
{
	size_t count = 0;

	while (*s != '\0')
		if (ft_strchr (reject, *s) == NULL)
			++s, ++count;
		else
			return count;

	return count;
}

size_t	ft_strspn (const char *s, const char *accept)
{
	size_t count = 0;

	while (*s != '\0')
		if (ft_strchr (accept, *s++) != NULL)
			++count;
		else
			return count;

	return count;
}

char *ft_strtok_r (char *s, const char *delim, char **save_ptr)
{
	char *end;

	if (s == NULL)
		s = *save_ptr;

	if (*s == '\0')
	{
		*save_ptr = s;
		return NULL;
	}

	/* Scan leading delimiters.  */
	s += ft_strspn (s, delim);
	if (*s == '\0')
	{
		*save_ptr = s;
		return NULL;
	}

	/* Find the end of the token.  */
	end = s + my_strcspn (s, delim);
	if (*end == '\0')
	{
		*save_ptr = end;
		return s;
	}

	/* Terminate the token and make *SAVE_PTR point past it.  */
	*end = '\0';
	*save_ptr = end + 1;
	return s;
}

static char *env_var_find(char *to_find, char **env)
{
	int i;
	int len;

	i = 0;
	len = ft_strlen(to_find);
	
	//len = 0;
	//while (to_find [len] != '\0' && to_find[len] != '\'' && to_find[len] != '"')
	//	len++;
	//printf("find: %s\nft_strcspn: %zu\n, len: %d\n", to_find, ft_strcspn(to_find, "\"\'"), len);
	i = 0;
	while (env[i])
	{
		//printf("ft_strncmp: %d\n", ft_strncmp(to_find, env[i], ft_strcspn(to_find, "\"\'")));
		if (ft_strncmp(to_find, env[i], ft_strcspn(to_find, "\"\'")) == 0 && env[i][len] == '=')
		{
			//printf("i = %d\n", i);
			return (&env[i][len + 1]);
		}
		i++;
	}
	return (NULL);
}

char* merge_strings(char* str1, char* str2)
{
	int	i;
	int	j;
	char* result;

	i = 0;
	j = 0;
	result = malloc(ft_secure_strlen(str1) + ft_secure_strlen(str2) + 1);
	if (result == NULL) {
		return NULL;
	}

	if (str1 != NULL)
	{
		while (str1[i] != '\0') {
			result[i] = str1[i];
			i++;
		}
		free(str1);
	}
	if (str2 != NULL)
	{
		while (str2[j] != '\0')
		{
			result[i + j] = str2[j];
			j++;
		}
	}
	result[i + j] = '\0';

	return (result);
}

static void expand_token(t_token *token, char **env)
{
	char *str;
	char *save_ptr;
	char *new_str;
	char *find;

	new_str = NULL;
	str = token->text;
	str = ft_strtok_r(str, "$", &save_ptr);
	printf("str: %s\n", str);
	if (token->text[0] != '$')
		new_str = merge_strings(new_str, str);
	else
	{
		find = env_var_find(str, env);
		//printf("find: %s\n", find);
		new_str = merge_strings(new_str, find);
	}
	while (1)
	{
		str = ft_strtok_r(NULL, "$", &save_ptr);
		printf("str: %s\n", str);
		if (str == NULL)
			break;
		find = env_var_find(str, env);
		//printf("find: %s\n", find);
		new_str = merge_strings(new_str, find);
	}
	free(token->text);
	token->text = new_str;
}

/*
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
	printf("%s\n", new_env_var);
	//Add my function
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
*/

/*
static	t_bool is_env_var(char *str)
{
	int i;
	
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'')
				i++;
		}
		if (str[i] == '\0')
		{
			write(1, "test1\n", 6);
			return (false);
		}
		if (str[i] == '$')
		{
			write(1, "test2\n", 6);
			return (true);
		}
		i++;
	}
		write(1, "test3\n", 6);
	return (false);
}
*/

/*
static	t_bool is_env_var(char *str)
{
	int i;
	t_bool in_quote;

	i = 0;
	in_quote = false;
	while (str[i])
	{
		if (str[i] == '\'')
			in_quote = !in_quote;
		if (str[i] == '$' && in_quote == false)
			return (true);	
		i++;
	}
	return (false);
}
*/

/*
static t_bool	is_simple_quotes(char *str)
{
	int i;
	
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			while (str[i] && str[i] != '\'')
				i++;
			if (str[i] == '\'')
				return (true);
			else
				return (false);
		}
		i++;
	}
	return (false);
}

static int	count_pair_quotes(char *str)
{
	int i;
	int nb_quote;

	i = 0;
	nb_quote = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			nb_quote++;
		i++;
	}
	if (nb_quote % 2 == 1)
		nb_quote--;
	return (nb_quote);
}

static void	expand_simple_quotes(t_token *token)
{
	char *new_str;
	int	nb_quote;
	int i;
	int	j;

	i = 0;
	j = 0;
	nb_quote = count_pair_quotes(token->text);
	new_str = malloc(sizeof(char) * ft_strlen(token->text) - nb_quote);
	while (token->text[i])
	{
		if (token->text[i] == '\'')
		{
			nb_quote--;
			i++;
		}
		new_str[j] = token->text[i];
		j++;
		i++;
	}
	free(token->text);
	token->text = new_str;
}
*/

void ft_expand(t_list *lst_token, char **env)
{
	t_token *token;
	while (lst_token != NULL)
	{
		token = lst_token->content;
		//if (is_env_var(token->text))
			expand_token(token, env);	
		//if (is_simple_quotes(token->text))
			//expand_simple_quotes(token);
		lst_token = lst_token->next;
	}
}

