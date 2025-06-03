// duplicate.c: Handles detection and removal (or reporting) of duplicate files in DIA.
// Compares files by size and hash, and deletes or logs duplicates as needed.

#include "duplicate.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "log.h"
#include "prompt.h"
#include "hash.h"

// Externs for shared state (populated in main.c)
extern struct FileEntry {
    char *path;
    off_t size;
    unsigned char hash[32];
} *fileList;
extern int fileCount;
extern int useSHA256;
extern int dryRun;
extern int interactive;
extern FILE *logFile;

// Scans the file list for duplicates and handles them (delete, prompt, or log)
// dryRunFlag: if set, only reports duplicates, doesn't delete
// interactiveFlag: if set, prompts before deleting
// useSHA256Flag: determines hash length (MD5 or SHA256)
// logFilePtr: file pointer for logging actions
void handle_duplicates(int dryRunFlag, int interactiveFlag, int useSHA256Flag, FILE *logFilePtr) {
    for (int i = 0; i < fileCount; i++) {
        for (int j = i + 1; j < fileCount; j++) {
            // Only consider files with the same size
            if (fileList[i].size != fileList[j].size) continue;
            int hashLen = useSHA256Flag ? 32 : 16;
            // Compare hashes to confirm duplicate
            if (memcmp(fileList[i].hash, fileList[j].hash, hashLen) == 0) {
                printf("⚠️  Duplicate: %s\n", fileList[j].path);
                log_msg(logFilePtr, "Duplicate: %s\n", fileList[j].path);
                if (!dryRunFlag) {
                    // If interactive, prompt user before deleting
                    if (interactiveFlag && !prompt_user(fileList[j].path)) {
                        printf("🚫 Skipped: %s\n", fileList[j].path);
                        continue;
                    }
                    // Attempt to delete the duplicate file
                    if (remove(fileList[j].path) == 0) {
                        printf("🗑️  Deleted: %s\n", fileList[j].path);
                        log_msg(logFilePtr, "Deleted: %s\n", fileList[j].path);
                    } else {
                        perror("❌ Error deleting");
                    }
                }
            }
        }
    }
}