// duplicate.h: Header for duplicate detection and handling in DIA.
// Declares the interface for finding and processing duplicate files.

#ifndef DUPLICATE_H
#define DUPLICATE_H

#include <stdio.h> // Needed for FILE type
#include "file_scan.h"
#include "hash.h"

// Scans the file list for duplicates and handles them (delete, prompt, or log)
void handle_duplicates(int dryRun, int interactive, int useSHA256, FILE *logFile);

#endif // DUPLICATE_H