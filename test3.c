#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

typedef enum {
	false,
	true
} t_bool;


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

int	custom_tokenizer(char *str, char **start, char **end, t_bool *in_d_quote)
{
	int	i;

	i = 0;
	*start = str;
	if (str[i] == '$' || str[i] == ' ' || str[i] == '\"')
		i++;
	
	if (str[i] == '\'' && i == 0 && *in_d_quote == false)
	{
		i++;
		while (str[i] != '\0' && str[i] != '\'')
			i++;
		if (str[i] != '\0')
			i++;
	}
	while (str[i] != '\0')
	{
		if ((str[i] == '\'' && *in_d_quote == false) || (str[i] == '\'' && *in_d_quote == true && i != 0))
		{
			*end = &str[i];
			return (1);
		}
		if (str[i] == '$')
		{
			*end = &str[i];
			return (1);
		}

		if (str[i] == '\"')
		{
			*in_d_quote = !*in_d_quote;
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

int main(void)
{
	//char *text = strdup("HI Lol\"$HELLO\"$$USER$$'$USER'hello\"Louise'$USER'Gurvan\"$$WORLD$$USER lol");
	//char *text = strdup("hello \"'$USER'\"$USER\"$USER\"");
	char *text = strdup("hello \"'$USER'\"$USER\"$USER\"");
	//char *text = strdup("hello '$USER'");
	/*
	char *text = strdup("HI Lol
			\"$HELLO\"
			$
			$USER
			$
			$'$USER'hello\"Louise'$USER'Gurvan\"$$WORLD$$USER lol");
			*/
	//char *text = strdup("hello\"'$USER'\"$USER\"$USER\"");
	//char *text = strdup("'\"$USER\"'");
	//char *test = strdup("\"''\"\"'$USER'\"\"''\""); //Loulou's test ''$USER''
	//char *text = strdup("hello'$USER'");
	char *start;
	char *end;

	end = text;
	t_bool in_d_quote;
	in_d_quote = false;
	while (custom_tokenizer(end, &start, &end, &in_d_quote) != 0)
		ft_putstr_fd_address(start, end, 1);
	ft_putstr_fd_address(start, end, 1);
	return (0);
}

