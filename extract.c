#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float *data;
    size_t size;
} Fleurs;

typedef struct {
    Fleurs setosa;
    Fleurs versicolor;
    Fleurs virginica;
} DonneesFleurs;

void print_error_message(int code) {
    switch (code) {
        case 1:
            fprintf(stderr, "Erreur : problème de paramètre.\n");
            break;
        case 2:
            fprintf(stderr, "Erreur : problème de lecture du fichier.\n");
            break;
        default:
            fprintf(stderr, "Erreur inconnue.\n");
    }
}

Fleurs InfosFleurs(FILE *file, size_t count) {
    Fleurs species;
    species.data = malloc(count * sizeof(float));
    if (species.data == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire.\n");
        exit(EXIT_FAILURE);
    }
    species.size = count;
    size_t i;
    for (i = 0; i < count; ++i) {
        fread(&species.data[i], sizeof(float), 1, file);
    }
    return species;
}

float Moyenne(Fleurs species) {
    float sum = 0.0;
    size_t i;
    for (i = 0; i < species.size; ++i) {
        sum += species.data[i];
    }
    return sum / species.size;
}

float Minimum(Fleurs species) {
    float min = species.data[0];
    size_t i;
    for (i = 1; i < species.size; ++i) {
        if (species.data[i] < min) {
            min = species.data[i];
        }
    }
    return min;
}

float Maximum(Fleurs species) {
    float max = species.data[0];
    size_t i;
    for (i = 1; i < species.size; ++i) {
        if (species.data[i] > max) {
            max = species.data[i];
        }
    }
    return max;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        print_error_message(1);
        return 1;
    }
    FILE *file = fopen(argv[1], "rb");
    if (file == NULL) {
        print_error_message(2);
        return 2;
    }
    DonneesFleurs DonneesFleurs;
    DonneesFleurs.setosa = InfosFleurs(file, 50);
    DonneesFleurs.versicolor = InfosFleurs(file, 50);
    DonneesFleurs.virginica = InfosFleurs(file, 50);
    fclose(file);
    printf("Setosa - Moyenne : %.2f, Min : %.2f, Max : %.2f\n",Moyenne(DonneesFleurs.setosa),Minimum(DonneesFleurs.setosa),Maximum(DonneesFleurs.setosa));
    printf("Versicolor - Moyenne : %.2f, Min : %.2f, Max : %.2f\n",Moyenne(DonneesFleurs.versicolor),Minimum(DonneesFleurs.versicolor),Maximum(DonneesFleurs.versicolor));
    printf("Virginica - Moyenne : %.2f, Min : %.2f, Max : %.2f\n",Moyenne(DonneesFleurs.virginica),Minimum(DonneesFleurs.virginica),Maximum(DonneesFleurs.virginica));
    return 0;
}
