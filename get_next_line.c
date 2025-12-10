/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jialhuan <jialhuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:54:36 by jialhuan          #+#    #+#             */
/*   Updated: 2025/11/20 18:04:02 by jialhuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	update_remainder(char *remainder, char *temp)
{
	int		current_posi;
	int		i;

	if (!ft_strchr(temp, '\n'))
	{
		remainder[0] = '\0';
		return ;
	}
	current_posi = ft_strchr(temp, '\n') - temp + 1;
	i = 0;
	while (temp[current_posi + i])
	{
		remainder[i] = temp[current_posi + i];
		i++;
	}
	remainder[i] = '\0';
}

static char	*r_around_newline(int fd, char *remainder, char *temp)
{
	int		count;
	char	*str_join;

	while (!ft_strchr(temp, '\n'))
	{
		count = read(fd, remainder, BUFFER_SIZE);
		if (count < 0)
		{
			free (temp);
			return (NULL);
		}
		if (count == 0)
			break ;
		remainder[count] = '\0';
		str_join = ft_strjoin(temp, remainder);
		if (!str_join)
		{
			free(temp);
			return (NULL);
		}
		free(temp);
		temp = str_join;
	}
	return (temp);
}

static char	*filling_line(char *temp)
{
	char	*str;
	int		len;
	char	*n_p;

	n_p = ft_strchr(temp, '\n');
	if (!n_p)
		return (ft_strdup(temp));
	len = n_p - temp + 1;
	str = ft_substr(temp, 0, len);
	if (!str)
		return (NULL);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	remainder[BUFFER_SIZE + 1];
	char		*temp;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	temp = ft_strdup(remainder);
	if (!temp)
		return (NULL);
	temp = r_around_newline(fd, remainder, temp);
	if (!temp)
	{
		remainder[0] = '\0';
		return (NULL);
	}
	if (temp[0] == '\0')
	{
		free(temp);
		return (NULL);
	}
	update_remainder(remainder, temp);
	line = filling_line(temp);
	free(temp);
	return (line);
}

// #include <fcntl.h>
// #include <stdio.h>
// int main()
// {
// 	int fd;
// 	fd = open("get_next_line_utils.c", O_RDONLY);
// 	// printf("first line: %s", get_next_line(fd));
// 	// printf("second line: %s", get_next_line(fd));
// 	// printf("third line: %s", get_next_line(fd));
// 	int i = 0;
// 	while (i < 40)
// 	{
// 		printf("Line: %s", get_next_line(fd));
// 		i++;
// 	}
// 	close(fd);
// }