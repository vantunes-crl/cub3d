#include "cub3d.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (str1[i] != '\0' && str1[i] == str2[i] && i < n - 1)
		i++;
	return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*mem;
	size_t	i;

	i = 0;
	mem = (char *)malloc(count * size);
	if (mem == 0)
		return (0);
	while (i < count * size)
	{
		mem[i] = 0;
		i++;
	}
	return ((void *)mem);
}

int	ismap(char c)
{
	if (c == ' ' || c == '1')
		return (1);
	return (0);
}

int	create_trgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	error(void)
{
	printf("error");
	exit(0);
}
