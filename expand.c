/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 11:14:45 by lmery             #+#    #+#             */
/*   Updated: 2023/01/08 17:31:47 by gle-mini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

int	custom_tokenizer(char *str, char **start, char **end)
{
	int	i;

	i = 0;
	*start = str;
	if (str[i] == '$' || str[i] == ' ')
		i++;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			*end = &str[i];
			return (1);
		}
		if (str[i] == ' ')
		{
			*end = &str[i];
			return (1);
		}
		i++;
	}
	*end = &str[i];
	return (0);
}

char* merge_strings(char* str1, char* str2)
{
	int	i;
	int	j;
	char* result;

	i = 0;
	j = 0;
	result = malloc(ft_strlen_secure(str1) + ft_strlen_secure(str2) + 1);
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

void ft_putstr_fd_address(char *start, char *end, int fd)
{
	if (!start)
		return ;
	if (!end)
		return ;
	if (start > end)
		return ;
	write(fd, start, end - start);
	write(fd, "\n", 1);
}

static char *env_var_find(char *start, char *end, char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(start, env[i], end - start) == 0 && env[i][end - start] == '=')
		{
			return (&env[i][end - start + 1]);
		}
		i++;
	}
	return (NULL);
}

static void expand_token(t_token *token, char **env)
{
	char *start;
	char *end;
	char *append_str;
	char *new_str;

	new_str = NULL;
	end = token->text;
	while (custom_tokenizer(end, &start, &end) != 0)
	{
		if (*start == '$')
		{
			append_str = env_var_find(start + 1, end, env);
			new_str = merge_strings(new_str, append_str);
		}
		else 
		{
			append_str = malloc(ft_strlen_secure(new_str) + (end - start) + 1);
			ft_bzero(append_str, ft_strlen_secure(new_str) + (end - start));
			ft_strlcpy_secure(append_str, new_str, ft_strlen_secure(new_str));
			ft_strlcat(append_str, start, end - start + 1);
			free(new_str);
			new_str = append_str;
		}
	}
	if (*start == '$')
	{
		append_str = env_var_find(start + 1, end, env);
		new_str = merge_strings(new_str, append_str);
	}
	else 
	{
		//ft_putstr_fd_address(start, end, 1);
		append_str = malloc(ft_strlen_secure(new_str) + (end - start) + 1);
		ft_bzero(append_str, ft_strlen_secure(new_str) + (end - start));
		ft_putstr_fd(append_str, 1);
		ft_strlcpy_secure(append_str, new_str, ft_strlen_secure(new_str));
		ft_strlcat(append_str, start, end - start + 1);
		free(new_str);
		new_str = append_str;
	}
	free(token->text);
	token->text = new_str;
}

void ft_expand(t_list *lst_token, char **env)
{
	t_token *token;
	while (lst_token != NULL)
	{
		token = lst_token->content;
		if (token->type == TOKEN_WORD || token->type == TOKEN_D_QUOTE)
			expand_token(token, env);	
		lst_token = lst_token->next;
	}
}

