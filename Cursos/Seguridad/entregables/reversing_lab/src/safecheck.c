#include <stdio.h>
#include <string.h>

int main() {
    char pass[64];
    printf("Ingrese la clave: ");
    if (scanf("%63s", pass) != 1) {
        return 1;
    }
    if (strcmp(pass, "Cyber2025") == 0) {
        printf("Acceso concedido\n");
    } else {
        printf("Acceso denegado\n");
    }
    return 0;
}