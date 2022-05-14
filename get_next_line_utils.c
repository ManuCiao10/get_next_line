/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eardingh <eardingh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 13:25:52 by eardingh          #+#    #+#             */
/*   Updated: 2022/04/22 13:54:10 by eardingh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char *container_str, char *buff)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!container_str)
	{
		container_str = (char *)malloc(1 * sizeof(char));
		container_str[0] = '\0';
	}
	if (!container_str || !buff)
		return (NULL);
	str = malloc(sizeof(char) * ((ft_strlen(container_str) + ft_strlen(buff))
				+ 1));
	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (container_str)
		while (container_str[++i] != '\0')
			str[i] = container_str[i];
	while (buff[j] != '\0')
		str[i++] = buff[j++];
	str[ft_strlen(container_str) + ft_strlen(buff)] = '\0';
	free(container_str);
	return (str);
}

/*
Used to loop over the container untill we find the '\n'
*/

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

/*
Read the input file fd and loop inside it until the program will find a \n 
(So until the end of the line).
ret == -1 means that an error occurred, so free the buffer to prevent memory leak
and return NUll. We assign '\0' at the end of the string and 
Strjoin concatenete the buffer,the string, in the container and return it.
*/

char	*ft_read_fd(int fd, char *container)
{
	int		ret;
	char	*buff;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	ret = 1;
	while (ret != 0 && !ft_strchr(container, '\n'))
	{
		ret = read(fd, buff, BUFFER_SIZE);
		if (ret == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[ret] = '\0';
		container = ft_strjoin(container, buff);
	}
	free(buff);
	return (container);
}

/*
Check if the Container is NULL to prevent KO when in the input there is NULL
later on the program calculate the lenght of the first line, where is assigned 
with the letter i. Malloc the size of the string + 1 (for the '\0') and copy the 
string into the Variable 'str' and return it.
*/

char	*ft_get_line(char *container)
{
	int		i;
	char	*str;

	i = 0;
	if (!*container)
		return (NULL);
	while (container[i] && container[i] != '\n')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 1 + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (container[i] && container[i] != '\n')
	{
		str[i] = container[i];
		i++;
	}
	if (container[i] == '\n')
	{
		str[i] = container[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

/*
Now we calculate the lenghh of the string, assigned with i.
MAlloc the lengh of all the line (with strlen) minus the first line
To malloc only the size of the second line. later on we save the 
second string with i (is the lengh of the string) and J at position 0 
in 'str'. Free the container and return the string.
*/

char	*ft_delete_fisrtline(char *container)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (container[i] && container[i] != '\n')
		i++;
	if (!container[i])
	{
		free(container);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(container) - i + 1));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (container[i])
		str[j++] = container[i++];
	str[j] = '\0';
	free(container);
	return (str);
}
