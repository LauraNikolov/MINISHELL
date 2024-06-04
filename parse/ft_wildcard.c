#include "../minishell.h"

int	ft_count_dir(void)
{
	int				i;
	DIR				*dir;
	struct dirent	*entry;

	i = 0;
	dir = opendir(".");
	entry = readdir(dir);
	while (entry)
	{
		i++;
		entry = readdir(dir);
	}
	closedir(dir);
	return (i);
}

char	*ft_match(char *cmd, char *dir)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (cmd[i] && cmd[i] != '*')
		i++;
	if (!ft_strncmp(cmd, dir, i))
	{
		printf("i = %d\n", i);
		while (cmd[i + 1] && dir[j] && cmd[i + 1] != dir[j])
			j++;
		if (!dir[i + 1] && !dir[j])
			return (dir);
		ft_match(&cmd[i + 1], &dir[j]);
	}
	return (NULL);
}

char	*ft_find_dir(char *cmd, char **dir)
{
	int		i;
	char	*s;

	s = NULL;
	i = 0;
	while (!s && dir[i])
	{
		s = ft_match(cmd, dir[i]);
		i++;
	}
	return (s);
}

char	**ft_save_dir(void)
{
	char			**curr_dir;
	struct dirent	*entry;
	DIR				*dir;
	int				i;

	entry = NULL;
	curr_dir = malloc(sizeof(char *) * ft_count_dir() + 1);
	curr_dir[ft_count_dir() + 1] = NULL;
	dir = opendir(".");
	i = 0;
	entry = readdir(dir);
	while (entry)
	{
		curr_dir[i] = entry->d_name;
		i++;
		entry = readdir(dir);
	}
	closedir(dir);
	return (curr_dir);
}

char	**ft_wildcard(t_cmd **lst)
{
	t_cmd	*curr;
	char	*s;
	char	**curr_dir;
	int		i;
	int		j;
	int		k;
	char	**wildcard;
	int		f;

	s = NULL;
	wildcard = malloc(sizeof(char *) * ft_count_dir() + 1);
	if (!wildcard)
		return (NULL);
	curr_dir = ft_save_dir();
	k = 0;
	curr = *lst;
	while (curr)
	{
		i = 1;
		while (curr->cmd[i])
		{
			j = 0;
			while (curr->cmd[i][j])
			{
				if (curr->cmd[i][j] == '*' && (j != 0 || curr->cmd[i][j + 1]))
				{
					s = ft_find_dir(curr->cmd[i], curr_dir);
					if (s)
						wildcard[k++] = ft_strdup(s);
					printf("wildcard[k] %s\n", wildcard[k]);
					printf("JE SUIS SORTIE DE LA BOUCLE JE REPARS POUR UN TOUR AVEC UNE AUTRE OPTION\n");
					exit(0);
				}
				j++;
			}
			i++;
		}
		curr = curr->next;
	}
	wildcard[k] = NULL;
	i = 0;
	while (wildcard[i])
	{
		printf("wild[%d] = %p\n", i + 1, wildcard[i]);
		i++;
	}
	exit(0);
	return (wildcard);
}

/* -------------------------- */

/* int ft_count_dir(void) {
	DIR *dir = opendir(".");
	if (!dir) {
		return (-1);
	}

	int count = 0;
	struct dirent *entry;

	while ((entry = readdir(dir)) != NULL) {
		count++;
	}

	closedir(dir);
	return (count);
} */

/*
// Fonction pour trouver les fichiers correspondant au motif cmd et stocker les résultats dans result
void	ft_find_dir(char *cmd, char *result, size_t size) {
	DIR *dir = opendir(".");
	if (!dir) {
		return ;
	}

	struct dirent *entry;
	int i, j;
	size_t len = 0;

	while ((entry = readdir(dir)) != NULL && len < size) {
		i = 0;
		j = 0;
		// Trouver le premier '*' dans cmd
		while (cmd[i] && cmd[i] != '*') {
			i++;
		}
		// Correspondance de la partie initiale de cmd avec entry->d_name
		if (!strncmp(cmd, entry->d_name, i)) {
			// Passer après '*' dans cmd et continuer la correspondance
			while (cmd[i + 1] && entry->d_name[i + j] && cmd[i
				+ 1] != entry->d_name[i + j]) {
				j++;
			}
			if (!cmd[i + 1] || (cmd[i + 1] && entry->d_name[i + j] == cmd[i
					+ 1])) {
				size_t entry_len = strlen(entry->d_name);
				if (len + entry_len + 1 < size) {
					strcat(result, entry->d_name);
					strcat(result, "\n");
					len += entry_len + 1;
				}
			}
		}
	}

	closedir(dir);
} */

// start of chat gpt_code ----------------------------------------------------

// Fonction pour traiter les commandes et utiliser ft_find_dir pour trouver les fichiers correspondants
// Fonction pour compter le nombre d'entrées dans le répertoire
/* int ft_count_dir(void) {
	DIR *dir = opendir(".");
	if (!dir) {
		return (-1);
	}

	int count = 0;
	struct dirent *entry;

	while ((entry = readdir(dir)) != NULL) {
		count++;
	}

	closedir(dir);
	return (count);
}

// Fonction pour trouver les fichiers correspondant au motif cmd et stocker les résultats dans result
void	ft_find_dir(char *cmd, char *result, size_t size) {
	DIR *dir = opendir(".");
	if (!dir) {
		return ;
	}
	struct dirent *entry;
	int i, j;
	size_t len = 0;

	while ((entry = readdir(dir)) != NULL && len < size) {
		i = 0;
		j = 0;
		// Trouver le premier '*' dans cmd
		while (cmd[i] && cmd[i] != '*') {
			i++;
		}
		// Correspondance de la partie initiale de cmd avec entry->d_name
		if (!strncmp(cmd, entry->d_name, i)) {
			// Passer après '*' dans cmd et continuer la correspondance
			while (cmd[i + 1] && entry->d_name[i + j] && cmd[i
				+ 1] != entry->d_name[i + j]) {
				j++;
			}
			if (!cmd[i + 1] || (cmd[i + 1] && entry->d_name[i + j] == cmd[i
					+ 1])) {
				size_t entry_len = strlen(entry->d_name);
				if (len + entry_len + 1 < size) {
					strcat(result, entry->d_name);
					strcat(result, "\n");
					len += entry_len + 1;
				}
			}
		}
	}

	closedir(dir);
}

// Fonction pour traiter les commandes et utiliser ft_find_dir pour trouver les fichiers correspondants
char	**ft_wildcard(t_cmd **lst) {
	t_cmd *curr = *lst;
	char *result;
	size_t size = 1024;  // Taille arbitraire, ajustez selon vos besoins

	result = malloc(size);
	if (!result) {
		return (NULL);
	}
	result[0] = '\0';  // Initialiser la chaîne vide

	while (curr) {
		for (int i = 0; curr->cmd[i]; i++) {
			for (int j = 0; curr->cmd[i][j]; j++) {
				if (curr->cmd[i][j] == '*') {
					ft_find_dir(curr->cmd[i], result, size);
					break ;
				}
			}
		}
		curr = curr->next;
	}

	printf("strlen(result) %s", result);

	free(result);
	return (NULL);
} */

// ---------------------------------------------------  end of chatgpt code

/* #include "../minishell.h"

int	ft_count_dir(void)
{
	int				i;
	DIR				*dir;
	struct dirent	*entry;

	i = 0;
	dir = opendir(".");
	entry = readdir(dir);
	while (entry)
	{
		i++;
		entry = readdir(dir);
	}
	closedir(dir);
	return (i);
}

char	**ft_find_dir(char *cmd, char **curr_dir)
{
	int			i;
	int			j;
	int			k;
	static char	**wildcard = NULL;

	if (!wildcard)
		wildcard = malloc(sizeof(char *) * ft_count_dir() + 1);
	k = 0;
	j = 0;
	i = 0;
	if (!cmd && !d_name)
	{
		wildcard[k++] = ft_strdup(entry->d_name);
		return (NULL);
	}
	if (!entry && cmd)
		return (NULL);
	if (!d_name)
	{
		printf("d_name = %s\n", d_name);
		entry = readdir(dir);
		printf("d_name = %s\n", d_name);
		d_name = entry->d_name;
	}
	while (cmd[i] && cmd[i] != '*')
		i++;
	printf("i = %d\n", i);
	if (!ft_strncmp(cmd, d_name, i))
	{
		while (cmd[i + 1] && d_name[i + j] && cmd[i + 1] != d_name[i + j])
			j++;
		ft_find_dir(&cmd[i + 1], &d_name[i + j]);
	}
	else
		ft_find_dir(cmd, NULL, entry, dir);
	return (NULL);
}

char	**ft_save_dir(void)
{
	char			**curr_dir;
	struct dirent	*entry;
	DIR				*dir;
	int				i;

	entry = NULL;
	curr_dir = malloc(sizeof(char *) * ft_count_dir() + 1);
	curr_dir[ft_count_dir() + 1] = NULL;
	dir = opendir(".");
	i = 0;
	while (entry)
	{
		entry = readdir(dir);
		curr_dir[i] = entry->d_name;
		i++;
	}
	closedir(dir);
	return (curr_dir);
}

char	**ft_wildcard(t_cmd **lst)
{
	t_cmd	*curr;
	char	**curr_dir;
	int		i;
	int		j;
	char	**wildcard;

	curr = *lst;
	// if (dir == NULL)
	// 	return (ft_putstr_cmd_fd("Error while accessing directory\n", 2, NULL),
	// 		NULL);
	wildcard = malloc(sizeof(char *) * ft_count_dir() + 1);
	wildcard[ft_count_dir() + 1] = NULL;
	curr_dir = ft_save_dir();
	i = 1;
	while (curr)
	{
		i = 0;
		while (curr->cmd[i])
		{
			j = 0;
			while (curr->cmd[i][j])
			{
				if (curr->cmd[i][j] == '*' && (j != 0 || curr->cmd[i][j + 1]))
				{
					wildcard = ft_find_dir(curr->cmd[i], curr_dir);
					printf("JE SUIS SORTIE DE LA BOUCLE JE REPARS POUR UN TOUR AVEC UNE AUTRE OPTION\n");
					closedir(dir);
					break ;
				}
				j++;
			}
			i++;
		}
		curr = curr->next;
	}
	i = 0;
	while (wildcard[i])
	{
		printf("wild[%d] = %p\n", i + 1, wildcard[i]);
		i++;
	}
	closedir(dir);
	exit(0);
	return (wildcard);
}
 */