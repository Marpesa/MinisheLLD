/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-mini <gle-mini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 04:19:58 by gle-mini          #+#    #+#             */
/*   Updated: 2023/03/14 20:46:45 by gle-mini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# define INT_MIN -2147483648
# define INT_MAX 2147483647
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/stat.h>

typedef enum s_bool
{
	false,
	true
}	t_bool;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

typedef struct s_split_next
{
	size_t	start;
	size_t	length;
}				t_split_next;

int				ft_isspace(char c);

int				ft_atoi(const char *str);

void			ft_bzero(void *s, size_t n);

void			*ft_calloc(size_t count, size_t size);

int				ft_isalnum(int c);

int				ft_isalpha(int c);

int				ft_isascii(int c);

int				ft_isdigit(int c);

int				ft_isprint(int c);

char			*ft_itoa(int n);

void			*ft_memchr(const void *s, int c, size_t n);

int				ft_memcmp(const void *s1, const void *s2, size_t n);

void			*ft_memcpy(void *dst, const void *src, size_t n);

void			*ft_memmove(void *dst, const void *src, size_t len);

void			*ft_memset(void *b, int c, size_t len);

void			ft_putchar_fd(char c, int fd);

void			ft_putendl_fd(char *s, int fd);

void			ft_putnbr_fd(int n, int fd);

void			ft_putstr_fd(char *s, int fd);

void			ft_putstr_fd_address(char *start, char *end, int fd);

char			**ft_split(char const *s, char c);

size_t			ft_maplen(char **map);

size_t			ft_maplen_secure(char **map);

char			*ft_strchr(const char *s, int c);

char			*ft_strdup(const char *s1);

char			*ft_strjoin(char const *s1, char const *s2);

char			*ft_str_merge_secure(char *str1, char *str2);

size_t			ft_strlcat(char *dst, const char *src, size_t size);

size_t			ft_strlcat_secure(char *dst, const char *src, size_t size);

size_t			ft_strlcat_secure(char *dst, const char *src, size_t size);

size_t			ft_strlcpy(char *dst, const char *src, size_t size);

size_t			ft_strlcpy_secure(char *dst, const char *src, size_t size);

size_t			ft_strlen(const char *s);

size_t			ft_strlen_secure(const char *s);

char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));

int				ft_strncmp(const char *s1, const char *s2, size_t n);

char			*ft_strncpy(char *dest, const char *src, size_t n);

char			*ft_strnstr(const char *haystack, const char *needle,
					size_t len);

char			*ft_strrchr(const char *s, int c);

char			*ft_strtrim(char const *s1, char const *set);

void			ft_striteri(char *s, void (*f)(unsigned int, char*));

char			*ft_strncat(char *s1, const char *s2, size_t n);

char			*ft_substr(char const *s, unsigned int start, size_t len);

int				ft_tolower(int c);

int				ft_toupper(int c);

t_list			*ft_lstnew(void *content);

int				ft_lstsize(t_list *lst);

t_list			*ft_lstlast(t_list *lst);

void			ft_lstadd_front(t_list **alst, t_list *new);

void			ft_lstadd_back(t_list **alst, t_list *new);

void			ft_lstdelone(t_list *lst, void (*del)(void*));

void			ft_lstclear(t_list **lst, void (*del)(void*));

void			ft_lstiter(t_list *lst, void (*f)(void*));

t_list			*ft_lstmap(t_list *lst, void *(*f)(void*), void (*del)(void *));

char			*ft_strtok_r(char *s, const char *delim, char **save_ptr);

size_t			ft_strspn(const char *s1, const char *s2);

size_t			ft_strcspn(const char *s1, const char *s2);

t_bool			ft_is_directory(const char *str);

t_bool			ft_is_file_exist(const char *str);

#endif
