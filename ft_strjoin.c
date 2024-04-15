#include "minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	int		total;
	char	*s3;

	if (!s1 || !s2)
		return (NULL);
	total = strlen(s1) + strlen(s2);
	s3 = malloc(sizeof(char) * total + 2);
	if (!s3)
		return (NULL);
	i = 0;
	while (s1[i] && i < total)
	{
		s3[i] = s1[i];
		i++;
	}
    s3[i] = '/';
    i++;
	j = 0;
	while (s2[j] && i < total)
		s3[i++] = s2[j++];
    s3[i] = '\0';
    printf ("%s\n", s3);
    free(s1);
	return (s3);
}