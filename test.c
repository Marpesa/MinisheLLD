#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



#include <stdio.h>
#include <string.h>

typedef enum {
	false,
	true
} t_bool;

char	*ft_strdup(const char *s1)
{
	char	*str;
	size_t	i;

	str = (char *)malloc(sizeof(*s1) * (strlen(s1) + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = 0;
	return (str);
}

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


/*
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
*/

size_t	my_strcspn (const char *s, const char *reject)
{
	size_t count = 0;

	while (*s != '\0' || *s != '\'')
		if (ft_strchr (reject, *s) == NULL)
			++s, ++count;
		else
			return count;

	return count;
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
	printf("s: %c\n", *s);

	/* Find the end of the token.  */
	end = s + my_strcspn (s, delim);
	printf("end: %c\n", *end);
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

int main(void)
{
	char str[] = "Lol'$USER'$$LANG$USER$$";
	//char str[] = "Lol'$USER$$LANG$USER$$";
	char *save_ptr;
	char *token;

	token = ft_strtok_r(str, "$", &save_ptr);
	while (token != NULL)
	{
		printf("%s\n", token);
		token = ft_strtok_r(NULL, "$", &save_ptr);
	}
	return (0);
}


/*
int main(void)
{
	char first_str[] = "This is a test test string.";
	char *str;

	str = malloc(sizeof(char) * strlen(first_str));
	strncpy(str, first_str, strlen(first_str));

	char *search;
	search = ft_strdup("test");
	//printf("%s\n", search);
	//char search[] = "test";
	char replace[] = "example";
	char *new_str;
	char *p;

	// Search for the substring

	new_str = NULL;
	p = strstr(str, search);
	while (p != NULL)
	{
		new_str = malloc(sizeof(char) * strlen(str) - strlen(search) + strlen(replace));
		strncpy(new_str, str, p - str); // Copy characters from 'str' to 'buffer' up to the point where 'search' starts
		new_str[p - str] = '\0';

		strcat(new_str, replace); // Concatenate 'replace' to the end of 'buffer'
		strcat(new_str, p + strlen(search)); // Concatenate the rest of 'str' to the end of 'buffer'
		free(str);
		str = new_str;
		p = strstr(str, search);
		printf("%s\n", str);
	}
	if (strstr(str, search) == NULL)
		printf("NULL\n");
	printf("Result: %s\n", new_str);
	return (0);
}
*/

