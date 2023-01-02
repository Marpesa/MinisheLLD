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

/*
int	custom_tokenizer(char *str, char **start, char **end)
{
	int	i;

	i = 0;
	*start = str;
	if (str[i] == '$')
		i++;
	if (str[i] == '\'')
		i++;
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
		{
			*end = &str[i];
			return (1);
		}
		if (str[i - 1] == '\'')
		{
			while (str[i] != '\0' && str[i] != '\'')
			{
				i++;
				if (str[i] == '\0')
				{
					*end = &str[i];
					return (1);
				}
			}
			*end = &str[i + 1];
			return (1);
		}
		if (str[i] == '$')
		{
			*end = &str[i];
			return (1);
		}
		i++;
	}
	*end = &str[i];
	return (0);
}
*/

static int quote_tokenizer(char *str, char **end, char c, int i)
{
	if (str[i] == c)
	{
		*end = &str[i];
		return (1);
	}
	if (str[i - 1] == c)
	{
		while (str[i] != '\0' && str[i] != c)
		{
			i++;
			if (str[i] == '\0')
			{
				*end = &str[i];
				return (1);
			}
		}
		*end = &str[i + 1];
		return (1);
	}
	return (0);
}

int	custom_tokenizer(char *str, char **start, char **end)
{
	int	i;

	i = 0;
	*start = str;
	if (str[i] == '$' || str[i] == '\'' || str[i] == '\"')
		i++;
	while (str[i] != '\0')
	{
		if (quote_tokenizer(str, end, '\'', i))
			return (1);
		if (quote_tokenizer(str, end, '\"', i))
			return (1);
		if (str[i] == '$')
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
	//char *text = strdup("Lol$HELLO'$USER'$$LANG$USER$$");
	//char *text = strdup("Lol$HELLO$USER");
	char *text = strdup("Lol$HELLO'$USER'$\"$HI'$WORLD'LOL\"$LANG$USER$$\"$VERSION\"");
	char *start;
	char *end;

	end = text;
	while (custom_tokenizer(end, &start, &end) != 0)
		ft_putstr_fd_address(start, end, 1);

	return (0);
}

