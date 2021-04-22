#include "cub3d.h"

int	ft_atoi(const char *str)
{
	int i;
	int n;

	i = 0;
	n = 0;
	while (str[i] >= 48 && str[i] <= 57)
	{
		n = n * 10 + (str[i] - 48);
		i++;
	}
	return (n);
}