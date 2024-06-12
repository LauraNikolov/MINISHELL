
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void fonctionrecursive(int n, char *str) {
    int i = 0;
    if (n == 10)
        return;
    if (str)
        free(str);
    str = (char *)malloc(sizeof(char) * (n + 1)); // Taille n+1 pour le caractère nul '\0'
    if (str == NULL) {
        printf("Allocation de mémoire échouée\n");
        exit(1); // Sortie du programme en cas d'échec
    }
    while (i < n) {
        str[i] = 'K';
        i++;
    }
    str[i] = '\0'; 
    printf("(%d), je suis recursive\n", n + 1);
    fonctionrecursive(n + 1, str);
    printf("(%d), je peux aussi faire ca\n", n + 1);
    printf("mon appel récursif = (%d), la taille de mon malloc : (%lu)\n", n, strlen(str));
    
    str = realloc(str, n + 1);
    // if (temp == NULL) {
    //     printf("Réallocation de mémoire échouée\n");
    //     exit(1); 
    // }
    // *str = temp;
    i = 0;
    while (i < n) {
        str[i] = 'K';
        i++;
    }
    str[i] = '\0';

    printf("après = la taille de mon malloc : (%lu)\n", sizeof(char) * n);
}

// int main() {
//     char *str = NULL; // Initialisez str à NULL

//     // Appel de la fonction récursive
//     fonctionrecursive(0, str);

//     // Libération de la mémoire à la fin du programme
//     if (str)
//         free(str);

//     return 0;
// }