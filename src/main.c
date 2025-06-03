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

#define MAX_FILES 100000

struct FileEntry {
    char *path;
    off_t size;
    unsigned char hash[32];
};

struct FileEntry *fileList = NULL;
int fileCount = 0;
int useSHA256 = 0;
int dryRun = 0;
int interactive = 0;
FILE *logFile = NULL;

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
    int recursive = 0;
    char *targetDir = NULL;
    char *logFilename = NULL;

    fileList = malloc(sizeof(struct FileEntry) * MAX_FILES);

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

    if (!targetDir) {
        printUsage(argv[0]);
        return 1;
    }

    if (logFilename) {
        logFile = fopen(logFilename, "w");
        if (!logFile) {
            perror("Failed to open log file");
            return 1;
        }
    }

    printf("Scanning %s...\n", targetDir);
    scan_directory(targetDir, recursive);
    handle_duplicates(dryRun, interactive, useSHA256, logFile);

    for (int i = 0; i < fileCount; i++) {
        free(fileList[i].path);
    }
    free(fileList);
    if (logFile) fclose(logFile);

    printf("Done. %d files scanned.\n", fileCount);
    return 0;
}