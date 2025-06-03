// prompt.c: User prompt utility for DIA.
// Asks the user for confirmation before deleting a file (if interactive mode is enabled).

#include "prompt.h"
#include <stdio.h>

// Prompts the user to confirm deletion of a file.
// Returns 1 if the user confirms, 0 otherwise.
int prompt_user(const char *filename) {
    printf("❓ Delete %s? [y/N]: ", filename);
    char answer[10];
    if (!fgets(answer, sizeof(answer), stdin)) return 0;
    return (answer[0] == 'y' || answer[0] == 'Y');
}