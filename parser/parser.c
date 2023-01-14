/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-mini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 14:07:36 by gle-mini          #+#    #+#             */
/*   Updated: 2023/01/14 18:32:42 by gle-mini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

void	print_map(char **map)
{
	int	i;

	i = 0;
	while (map[i] != NULL)
	{
		printf("%s ", map[i]);
		i++;
	}
}

/*
void	get_absolute_path(char **cmd)
{
	char	*path = ft_strdup(getenv("PATH"));
	char	*bin = NULL;
	char	**path_split = NULL;
	int		i;

	if (path == NULL) // si le path est null, on cree un path
		path = ft_strdup("/bin:/usr/local/bin:/usr/bin:/bin:/usr/local/sbin");

	// si cmd n'est pas le chemin absolue, on cherche le chemin absolue du
	// binaire grace a la variable d'environment PATH
	if (cmd[0][0] != '/' && strncmp(cmd[0], "./", 2) != 0)
	{
		// On split le path pour verifier ou ce trouve le binaire
		//path_split = ft_split(path, ":");
		//path_split = strtok(path, ":");
		free(path);
		path = NULL;

		i = 0;
		// On boucle sur chaque dossier du path pour trouver l'emplacement du binaire
		while (strtok(path, ":"))
		{
			bin = (char *)ft_calloc(sizeof(char), (ft_strlen(path_split[i]) + 1 + ft_strlen(cmd[0]) + 1));
			if (bin == NULL)
				break ;

			// On concat le path , le '/' et le nom du binaire
			ft_strlcat(bin, path_split[i], ft_strlen(path_split[i]) + ft_strlen(bin));
			ft_strlcat(bin, "/", ft_strlen(path_split[i])) + ft_strlen(bin);
			ft_strlcat(bin, cmd[0], ft_strlen(path_split[i]) + ft_strlen(bin));

			// On verfie l'existence du fichier et on quitte la boucle si access
			// renvoi 0
			if (access(bin, F_OK) == 0)
				break ;
			free(bin);
			bin = NULL;
		}
		//free_array(path_split);	

		// On remplace le binaire par le path absolue ou NULL si le binaire
		// n'existe pas
		free(cmd[0]);
		cmd[0] = bin;
	} else {
		free(path);
		path = NULL;
	}
}
*/


void	get_absolute_path(char **cmd)
{
	char	*path = strdup(getenv("PATH"));
	char	*bin = NULL;
	char	**path_split = NULL;

	if (path == NULL) // si le path est null, on cree un path
		path = ft_strdup("/bin:/usr/local/bin:/usr/bin:/bin:/usr/local/sbin");

	// si cmd n'est pas le chemin absolue, on cherche le chemin absolue du
	// binaire grace a la variable d'environment PATH
	if (cmd[0][0] != '/' && ft_strncmp(cmd[0], "./", 2) != 0)
	{
		// On split le path pour verifier ou ce trouve le binaire
		path_split = ft_split(path, ':');
		free(path);
		path = NULL;

		printf("\n");
		print_map(path_split);
		printf("\n");
		// On boucle sur chaque dossier du path pour trouver l'emplacement du binaire
		for (int i = 0; path_split[i]; i++) {
			// alloc len du path + '/' + len du binaire + 1 pour le '\0'
			bin = malloc(sizeof(char) * (strlen(path_split[i]) + 1 + strlen(cmd[0]) + 1));
			if (bin == NULL)
				break ;

			// On concat le path , le '/' et le nom du binaire
			ft_strlcat(bin, path_split[i], ft_strlen(path_split[i]) + ft_strlen(bin));
			ft_strlcat(bin, "/", ft_strlen("/") + ft_strlen(bin));
			ft_strlcat(bin, cmd[0], ft_strlen(cmd[0]) + ft_strlen(bin));


			// On verfie l'existence du fichier et on quitte la boucle si access
			// renvoi 0
			if (access(bin, F_OK) == 0)
				break ;

			// Nous sommes des gens propre :D
			free(bin);
			bin = NULL;
		}
		//free_array(path_split);

		// On remplace le binaire par le path absolue ou NULL si le binaire
		// n'existe pas
		free(cmd[0]);
		cmd[0] = bin;
	} else {
		free(path);
		path = NULL;
	}
}


char	**convert_to_map(t_list *lst_token)
{
	t_token	*token;
	char	**map;
	int		i;

	i = 0;
	map = malloc(sizeof(char *) * ft_lstsize(lst_token) + 1);
	while (lst_token != NULL)
	{
		token = lst_token->content;
		map[i] = token->text;
		lst_token = lst_token->next;
		i++;
	}
	map[i] = NULL;	
	print_map(map);
	get_absolute_path(map);
	print_map(map);
	return (map);
}



/*
void	get_absolute_path(char **cmd)
{
	char	*path = strdup(getenv("PATH"));
	char	*bin = NULL;
	char	**path_split = NULL;

	if (path == NULL) // si le path est null, on cree un path
		path = ft_strdup("/bin:/usr/local/bin:/usr/bin:/bin:/usr/local/sbin");

	// si cmd n'est pas le chemin absolue, on cherche le chemin absolue du
	// binaire grace a la variable d'environment PATH
	if (cmd[0][0] != '/' && strncmp(cmd[0], "./", 2) != 0)
	{
		// On split le path pour verifier ou ce trouve le binaire
		path_split = ft_split(path, ":");
		free(path);
		path = NULL;

		// On boucle sur chaque dossier du path pour trouver l'emplacement du binaire
		for (int i = 0; path_split[i]; i++) {
			// alloc len du path + '/' + len du binaire + 1 pour le '\0'
			bin = (char *)calloc(sizeof(char), (strlen(path_split[i]) + 1 + strlen(cmd[0]) + 1));
			if (bin == NULL)
				break ;

			// On concat le path , le '/' et le nom du binaire
			ft_strcat(bin, path_split[i]);
			ft_strcat(bin, "/");
			ft_strcat(bin, cmd[0]);

			// On verfie l'existence du fichier et on quitte la boucle si access
			// renvoi 0
			if (access(bin, F_OK) == 0)
				break ;

			// Nous sommes des gens propre :D
			free(bin);
			bin = NULL;
		}
		free_array(path_split);

		// On remplace le binaire par le path absolue ou NULL si le binaire
		// n'existe pas
		free(cmd[0]);
		cmd[0] = bin;
	} else {
		free(path);
		path = NULL;
	}
}
*/
