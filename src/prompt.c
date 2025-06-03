#include "prompt.h"
#include <stdio.h>

int prompt_user(const char *filename) {
    printf("❓ Delete %s? [y/N]: ", filename);
    char answer[10];
    if (!fgets(answer, sizeof(answer), stdin)) return 0;
    return (answer[0] == 'y' || answer[0] == 'Y');
}