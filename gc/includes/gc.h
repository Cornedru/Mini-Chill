/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 01:16:39 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/15 21:41:51 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GC_H
# define GC_H

/* includes ***************************************************************** */

# include <stdlib.h>
# include "../../libft/includes/libft.h"

/* typedef ****************************************************************** */

typedef struct s_mem
{
	void			*mem;
	struct s_mem	*next;
}	t_mem;

/* prototypes *************************************************************** */

void	*gc_malloc(size_t size);
void	gc_free(void *mem);
void	gc_free_array(void **mem);
void	gc_destroy(void);
t_mem	**gc_get_head(void);
void	gc_free_node(t_mem **node);
char	*gc_strdup(const char *s);
char	*gc_strjoin(char *s1, char *s2);
char	*gc_strjoin_free_s1(char const *s1, char const *s2);
char	*gc_strjoin_free_s2(char const *s1, char const *s2);
char	*gc_strjoin_free_s1_s2(char const *s1, char const *s2);
char	**gc_split(char const *s, char c);
char	*gc_substr(char const *s, unsigned int start, size_t len);
void	gc_lstdelone(t_list *lst, void (*del)(void *));
void	gc_lstclear(t_list **lst, void (*del)(void *));
void	*gc_track(void *ptr);
void	gc_print_leaks(void);
char	*gc_itoa(int n);

#endif