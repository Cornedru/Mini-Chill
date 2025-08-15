/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 09:00:49 by oligrien          #+#    #+#             */
/*   Updated: 2025/06/29 23:58:20 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

/* includes ***************************************************************** */
# include <stddef.h>
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include <errno.h>

/* typedef ****************************************************************** */
typedef struct s_list
{
	void			*content;
	struct s_list	*prev;
	struct s_list	*next;
}	t_list;

/* <ctype.h> **************************************************************** */
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);

/* <string.h> *************************************************************** */
size_t	ft_strlen(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strdup(const char *s);

void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);

/* <bsd/string.h> *********************************************************** */
char	*ft_strnstr(const char *big, const char *little, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);

/* <stdlib.h> *************************************************************** */
int		ft_atoi(const char *nptr);

void	*ft_calloc(size_t nmemb, size_t size);
void	ft_free(void **ptr);
void	ft_free_strarr(void ***ptr);

/* libft ******************************************************************** */
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin_free_s1(char const *s1, char const *s2);
char	*ft_strjoin_free_s2(char const *s1, char const *s2);
char	*ft_strjoin_free_s1_s2(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));

/* put ********************************************************************** */
int		ft_putstr(char *s);
int		ft_putstr_fd(char *s, int fd);
int		ft_putchar(char c);
int		ft_putchar_fd(char c, int fd);
int		ft_putendl(char *s);
int		ft_putendl_fd(char *s, int fd);
int		ft_putnbr(int nb);
int		ft_putnbr_fd(int nb, int fd);
int		ft_putnbr_base(long int nb, int base);
int		ft_putnbr_base_fd(long int nb, int base, int fd);
int		ft_putulnbr(unsigned long long n);
int		ft_putulnbr_fd(unsigned long long n, int fd);

/* lists ******************************************************************** */
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstfirst(t_list *lst);

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);

void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));

void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/* ************************************************************************** */
int		ft_printf(const char *input, ...);
char	*get_next_line(int fd);

#endif