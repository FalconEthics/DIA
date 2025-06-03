// DIA - Duplicate Image Analyzer
// main.c: Entry point and command-line interface for the duplicate image finder.
// Handles argument parsing, setup, and program orchestration.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <ftw.h>
#include "file_scan.h"
#include "hash.h"
#include "duplicate.h"
#include "log.h"
#include "prompt.h"

#define MAX_FILES 100000 // Maximum number of files to track in memory

// Represents a file found during scanning
struct FileEntry {
    char *path;                // Full path to the file
    off_t size;                // File size in bytes
    unsigned char hash[32];    // MD5 or SHA256 hash of file contents
};

// Global state shared across modules
struct FileEntry *fileList = NULL;
int fileCount = 0;
int useSHA256 = 0;     // 0 = MD5, 1 = SHA256
int dryRun = 0;        // 1 = don't delete, just show
int interactive = 0;   // 1 = prompt before delete
FILE *logFile = NULL;  // Log file pointer (if logging enabled)

// Prints usage instructions and options
void printUsage(const char *prog) {
    printf("\nDIA - Duplicate Image Analyzer\n");
    printf("Usage: %s [-r] [--dry-run] [--log logfile] [--sha256] [--interactive] <directory>\n\n", prog);
    printf("Options:\n");
    printf("  -r             Recursively scan directories\n");
    printf("  --dry-run      Show duplicates without deleting\n");
    printf("  --log FILE     Log output to FILE\n");
    printf("  --sha256       Use SHA256 instead of MD5\n");
    printf("  --interactive  Prompt before each deletion\n");
    printf("\nExample: ./dia -r --interactive --log log.txt ./demo\n\n");
}

int main(int argc, char *argv[]) {
    int recursive = 0;         // Whether to scan directories recursively
    char *targetDir = NULL;    // Directory to scan
    char *logFilename = NULL;  // Log file name (if any)

    // Allocate memory for file entries
    fileList = malloc(sizeof(struct FileEntry) * MAX_FILES);

    // Parse command-line arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-r") == 0) {
            recursive = 1;
        } else if (strcmp(argv[i], "--dry-run") == 0) {
            dryRun = 1;
        } else if (strcmp(argv[i], "--sha256") == 0) {
            useSHA256 = 1;
        } else if (strcmp(argv[i], "--interactive") == 0) {
            interactive = 1;
        } else if (strcmp(argv[i], "--log") == 0 && i + 1 < argc) {
            logFilename = argv[++i];
        } else if (argv[i][0] != '-') {
            targetDir = argv[i];
        } else {
            printUsage(argv[0]);
            return 1;
        }
    }

    // Must specify a directory to scan
    if (!targetDir) {
        printUsage(argv[0]);
        return 1;
    }

    // Open log file if requested
    if (logFilename) {
        logFile = fopen(logFilename, "w");
        if (!logFile) {
            perror("Failed to open log file");
            return 1;
        }
    }

    printf("Scanning %s...\n", targetDir);
    // Scan the directory and build the file list
    scan_directory(targetDir, recursive);
    // Find and handle duplicates (delete or show)
    handle_duplicates(dryRun, interactive, useSHA256, logFile);

    // Clean up memory
    for (int i = 0; i < fileCount; i++) {
        free(fileList[i].path);
    }
    free(fileList);
    if (logFile) fclose(logFile);

    printf("Done. %d files scanned.\n", fileCount);
    return 0;
}