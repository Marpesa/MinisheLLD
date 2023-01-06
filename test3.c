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

int main(void)
{
	char *text = strdup("HI Lol$HELLO$$USER$$$$WORLD$$USER lol");
	char *start;
	char *end;

	end = text;
	while (custom_tokenizer(end, &start, &end) != 0)
		ft_putstr_fd_address(start, end, 1);
	ft_putstr_fd_address(start, end, 1);
	return (0);
}

