#include <stdio.h>
#include <string.h>

static void deobfuscate(char *s) {
    for (int i = 0; s[i] != '\0'; i++) {
        s[i] = (char)(s[i] - 1);
    }
}

int main() {
    char pass[64];
    char secret[] = "Dzcfs3136"; // Cada caracter = original + 1; al restar 1 -> "Cyber2025"
    deobfuscate(secret);

    printf("Ingrese la clave: ");
    if (scanf("%63s", pass) != 1) {
        return 1;
    }
    if (strcmp(pass, secret) == 0) {
        printf("Acceso concedido\n");
    } else {
        printf("Acceso denegado\n");
    }
    return 0;
}