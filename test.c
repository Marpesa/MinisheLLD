#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



#include <stdio.h>
#include <string.h>

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

