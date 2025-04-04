/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saylital <saylital@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 09:55:31 by saylital          #+#    #+#             */
/*   Updated: 2025/03/28 21:41:02 by saylital         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include "../libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50
# endif

char	*get_next_line(int fd);
char	*ft_strjoin_line(char *string, char *buffer);
char	*ft_strchrnl(const char *s, int c);
char	*ft_strdup_newline(char *s1);
size_t	ft_strlen_newline(const char *str);
size_t	ft_strlennl(const char *str);

#endif