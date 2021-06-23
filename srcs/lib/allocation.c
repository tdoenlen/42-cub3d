#include "cub3d.h"

void	*safe_free(void *ptr)
{
	if (ptr)
		free(ptr);
	return (NULL);
}

char	**safe_free_str_tab(char **tab)
{
	int	i;

	if (tab == NULL)
		return (NULL);
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

char	*set_str_len(char *str, int new_len)
{
	int		i;
	char	*new_str;

	new_str = malloc(sizeof(*new_str) * (new_len + 1));
	if (new_str == NULL)
		return (NULL);
	i = 0;
	while (str[i] && i < new_len)
	{
		new_str[i] = str[i];
		i++;
	}
	while (i < new_len)
	{
		new_str[i] = ' ';
		i++;
	}
	free(str);
	new_str[i] = '\0';
	return (new_str);
}

char	**append_str_tab(char **tab, char *str)
{
	int		i;
	char	**new_tab;

	i = 0;
	while (tab && tab[i])
		i++;
	new_tab = malloc(sizeof(*new_tab) * (i + 2));
	if (new_tab == NULL)
		return (NULL);
	i = 0;
	while (tab && tab[i])
	{
		new_tab[i] = tab[i];
		i++;
	}
	safe_free(tab);
	new_tab[i] = str;
	new_tab[i + 1] = NULL;
	return (new_tab);
}

char	**pop_str_tab(char **tab)
{
	int		i;
	char	**new_tab;

	i = 0;
	if (!tab[i])
		return (NULL);
	while (tab[i])
		i++;
	new_tab = malloc(sizeof(*new_tab) * i);
	if (new_tab == NULL)
		return (NULL);
	i = 0;
	while (tab[i + 1])
	{
		new_tab[i] = tab[i];
		i++;
	}
	free(tab[i]);
	free(tab);
	new_tab[i] = NULL;
	return (new_tab);
}
