/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarakus <ckarakus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 00:36:37 by ckarakus          #+#    #+#             */
/*   Updated: 2023/05/03 18:34:50 by ckarakus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../checker_bonus.h"

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*to_return;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = ft_read(fd, stash);
	if (!stash)
		return (NULL);
	to_return = ft_get_line(stash);
	stash = ft_new_stash(stash);
	return (to_return);
}

char	*ft_read(int fd, char *stash)
{
	char	*buff;
	int		check;

	check = 1;
	buff = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	while (check != 0 && !ft_strchr(stash))
	{
		check = read(fd, buff, BUFFER_SIZE);
		if (check == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[check] = '\0';
		stash = ft_strjoin(stash, buff);
	}
	free(buff);
	return (stash);
}

char	*ft_get_line(char *stash)
{
	char	*to_return;
	int		i;

	i = 0;
	if (!stash[i])
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	to_return = malloc(sizeof(char) * (i + 2));
	if (!to_return)
		return (NULL);
	ft_strcpy(to_return, stash, i + 1);
	return (to_return);
}

char	*ft_new_stash(char *stash)
{
	int		i;
	char	*to_return;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	to_return = malloc(sizeof(char) * (ft_strlen(stash) - i + 1));
	if (!to_return)
		return (NULL);
	i++;
	ft_strcpy(to_return, stash + i, ft_strlen(stash + i));
	free(stash);
	return (to_return);
}
