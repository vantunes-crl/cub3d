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

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_lenofnum_bonus(int n)
{
	int l;

	l = 1;
	while (n > 9)
	{
		n = n / 10;
		l++;
	}
	return (l);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		sign;
	int		len;

	sign = 0;
	if (n < 0)
	{
		n = n * -1;
		sign = 1;
	}
	len = ft_lenofnum_bonus(n);
	str = (char *)malloc(sizeof(char ) * (len + sign + 1));
	if (!str)
		return (NULL);
	str[len + sign] = '\0';
	while (len-- > 0)
	{
		str[len + sign] = 48 + n % 10;
		n = n / 10;
	}
	if (sign == 1)
		str[len + sign] = '-';
	return (str);
}

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}
int	ft_strlen(const char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	char	*s1_cpy;
	int		i;

	i = 0;
	s1_cpy = (char *)malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (s1_cpy == 0)
		return (0);
	while (s1[i])
	{
		s1_cpy[i] = s1[i];
		i++;
	}
	s1_cpy[i] = '\0';
	return (s1_cpy);
}