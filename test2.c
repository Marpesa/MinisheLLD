#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

typedef enum {
	false,
	true
} t_bool;

int		trim_len(char *str)
{
	int	i;
	int	len;
	t_bool in_d_quote;
	t_bool in_s_quote;

	i = 0;
	len = 0;
	in_d_quote = false;
	in_s_quote = false;
	while (str[i])
	{
		if (str[i] == '\"' && in_s_quote == false)
		{
			in_d_quote = !in_d_quote;	
			len++;
		}
		if (str[i] == '\'' && in_d_quote == false)
		{
			in_s_quote = !in_s_quote;	
			len++;
		}
		i++;
	}
	return (len);
}

char	*trim(char *str)
{
	int	i;
	int	j;
	int len;
	char *new_str;
	t_bool in_d_quote;
	t_bool in_s_quote;

	i = 0;
	j = 0;
	in_d_quote = false;
	in_s_quote = false;
	if (str == NULL)
		return (NULL);
	len = trim_len(str);
	new_str = malloc(sizeof(char) * (strlen(str) - len + 1));
	while (str[i])
	{
		if (str[i] == '\"' && in_s_quote == false)
		{
			in_d_quote = !in_d_quote;	
			i++;
		}
		if (str[i] == '\'' && in_d_quote == false)
		{
			in_s_quote = !in_s_quote;	
			i++;
		}
		new_str[j] = str[i];
		j++;
		i++;
	}
	return (new_str);
}

int main(void)
{
	//char *text = strdup("HI Lol\"$HELLO\"$$USER$$'$USER'hello\"Louise'$USER'Gurvan\"$$WORLD$$USER lol");
	//char *text = strdup("\"'$USER'\"");
	//char *text = strdup("'\"$USER\"'");
	//char *test = strdup("\"''\"\"'$USER'\"\"''\""); //Loulou's test ''$USER''
	
	char *text = strdup("Salut $'USER' \"Hello 'Lwize'\" $\"USER\" \"gle-mini\"");
					   //Salut USER Hello 'Lwize' $USER gle-mini
					   //		2 + 	2 +			0 +	2 +				2  = 6
	
	printf("%s\n", trim(text));
	return (0);
}

