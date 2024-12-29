/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merilhan <merilhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 14:16:05 by merilhan          #+#    #+#             */
/*   Updated: 2024/12/24 15:52:42 by merilhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

size_t ft_strlen(char *str)
{
	size_t i;
	i = 0;
	if (!str)
		return (0);
	while(str[i])
		i++;
	return (i);
}
char	*ft_strchr(char *s, int c)
{
	size_t i;
	
	if (!s)
		return (NULL);
	i = 0;
	while(i < ft_strlen(s) + 1)
	{
		if (*(s + i) == (char)c)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*buffer;
	char	*res;
	char 	*s3;
	
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	buffer = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!buffer)
		return (NULL);
	s3 = s1;
	res = buffer;
	while (*s1)
		*buffer++ = *s1++;
	while (*s2)
		*buffer++ = *s2++;
	*buffer = '\0';
	free(s3);
	return (res);
}
char	*ft_strdup(char *str)
{
	char *buffer;
	char *res;
	
	if (!str)
		return (NULL);
	buffer = malloc(ft_strlen(str) + 1);
	if (!buffer)
		return (NULL);
	res = buffer;
	while (*str)
		*buffer++ = *str++;
	*buffer = '\0';
	return (res);
}