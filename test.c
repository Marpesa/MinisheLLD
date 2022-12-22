#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



#include <stdio.h>
#include <string.h>

/*
int main(void) {
    char str[] = "This is a test string.";
    char search[] = "test";
    char replace[] = "example";
    char buffer[100];
    char *p;

    // Search for the substring
    p = strstr(str, search);

    // If the substring is found, copy the string up to the substring
    // into the buffer, then concatenate the replacement string and the rest of the original string
    // into the buffer
    if (p) {
        strncpy(buffer, str, p - str); // Copy characters from 'str' to 'buffer' up to the point where 'search' starts
        buffer[p - str] = '\0';

		printf("%s\n", buffer);
        strcat(buffer, replace); // Concatenate 'replace' to the end of 'buffer'
        strcat(buffer, p + strlen(search)); // Concatenate the rest of 'str' to the end of 'buffer'
    }

    printf("Result: %s\n", buffer);

    return 0;
}
*/

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
    p = strstr(str, search);

    // If the substring is found, copy the string up to the substring
    // into the buffer, then concatenate the replacement string and the rest of the original string
    // into the buffer
	new_str = NULL;
    if (p != NULL)
	{
		if (new_str != NULL)
		{
			free(new_str);
		}
		new_str = malloc(sizeof(char) * strlen(str) - strlen(search) + strlen(replace));
        strncpy(new_str, str, p - str); // Copy characters from 'str' to 'buffer' up to the point where 'search' starts
        new_str[p - str] = '\0';

        strcat(new_str, replace); // Concatenate 'replace' to the end of 'buffer'
        strcat(new_str, p + strlen(search)); // Concatenate the rest of 'str' to the end of 'buffer'
    	p = strstr(new_str, search);
		free(str);
		//str = new_str;
    }
	str = ft_strdup(new_str);

    if (p != NULL)
	{
		if (new_str != NULL)
		{
			free(new_str);
			new_str = NULL;
		}
		printf("%s\n", str);
		printf("%s\n", p);
		new_str = malloc(sizeof(char) * strlen(str) - strlen(search) + strlen(replace));
        strncpy(new_str, str, p - str); // Copy characters from 'str' to 'buffer' up to the point where 'search' starts
        new_str[p - str] = '\0';
		printf("%s\n", new_str);

        strcat(new_str, replace); // Concatenate 'replace' to the end of 'buffer'
        strcat(new_str, p + strlen(search)); // Concatenate the rest of 'str' to the end of 'buffer'
    	p = strstr(new_str, search);
		printf("%s\n", p);
		free(str);
		str = new_str;
    }
    printf("Result: %s\n", new_str);
    return (0);
}
