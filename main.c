#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("You need to provide file path you want to encrypt as program argument");
        return -1;
    }
    char *path = argv[1];
    char *password = argv[2];
    int passwordLength = strlen(password);

    FILE *file = fopen(path, "rb");

    char cwd[256];
    getcwd(cwd, sizeof(cwd));
    char *temp = tmpnam(cwd);
    FILE *encryptedFile = fopen(temp, "wb");

    char character;
    int counter = 0;
    while ((character = getc(file)) != EOF) {
        character ^= password[counter % (passwordLength)];
        counter++;
        putc(character, encryptedFile);
    }
    unlink(path);
    rename(temp, path);

    fclose(file);
    fclose(encryptedFile);
    printf("Hello, World!\n");
    return 0;
}
