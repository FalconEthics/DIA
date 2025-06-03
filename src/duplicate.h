#ifndef DUPLICATE_H
#define DUPLICATE_H

#include <stdio.h> // Add this line for FILE
#include "file_scan.h"
#include "hash.h"

void handle_duplicates(int dryRun, int interactive, int useSHA256, FILE *logFile);

#endif // DUPLICATE_H