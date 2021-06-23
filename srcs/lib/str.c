int	ft_strlen(char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

int	str_is_eq(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (1);
	return (0);
}

int	ft_atoi(char *s)
{
	int	ret;

	ret = 0;
	while (*s >= '0' && *s <= '9')
	{
		ret = 10 * ret + (*s - '0');
		if (ret < 0)
			return (-1);
		s++;
	}
	return (ret);
}

int	get_ni(char *s, int i)
{
	while (s[i] == ' ')
		i++;
	return (i);
}
