#include "image3d.h"

char	*ft_strdup(const char *s)
{
	char	*result;
	size_t	i;

	result = malloc(strlen(s) + 1);
	if (result == 0)
		return (0);
	i = 0;
	while (s[i])
	{
		result[i] = s[i];
		i++;
	}
	result[i] = 0;
	return (result);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	slen;
	size_t	i;

	if (!s)
		return (0);
	if (start > strlen(s))
		return (ft_strdup(""));
	slen = strlen(s);
	if (slen < start + len)
		len = slen - start;
	result = malloc(len + 1);
	if (!result)
		return (0);
	i = 0;
	while (i < len)
	{
		result[i] = s[start + i];
		i++;
	}
	result[i] = 0;
	return (result);
}

static size_t	count_words(char const *s, char c)
{
	size_t			i;
	size_t			j;
	unsigned int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		j = 0;
		while (s[i + j] && s[i + j] != c)
			j++;
		if (j > 0)
		{
			count++;
			i += j;
		}
		if (s[i])
			i++;
	}
	return (count);
}

static int	free_list(char **result, unsigned int count)
{
	unsigned int	i;

	i = 0;
	while (i < count)
	{
		free(result[i]);
		i++;
	}
	free(result);
	return (0);
}

static int	cpy_strs(char const *s, char c, char **result)
{
	size_t			i;
	size_t			j;
	unsigned int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		j = 0;
		while (s[i + j] && s[i + j] != c)
			j++;
		if (j > 0)
		{
			result[count] = ft_substr(s, i, j);
			if (!result[count])
				return (free_list(result, count));
			count++;
			i += j;
		}
		if (s[i])
			i++;
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	size_t	len;
	char	**result;

	if (!s)
		return (0);
	len = count_words(s, c);
	result = malloc((len + 1) * sizeof(char *));
	if (result == 0)
		return (0);
	if (!cpy_strs(s, c, result))
		return (0);
	result[len] = 0;
	return (result);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	i;
	size_t	l1;
	size_t	l2;

	if (!s1 || !s2)
		return (0);
	l1 = strlen(s1);
	l2 = strlen(s2);
	result = malloc(l1 + l2 + 1);
	if (result == 0)
		return (0);
	i = 0;
	while (i < l1)
	{
		result[i] = s1[i];
		i++;
	}
	while (i < l1 + l2)
	{
		result[i] = s2[i - l1];
		i++;
	}
	result[i] = 0;
	return (result);
}