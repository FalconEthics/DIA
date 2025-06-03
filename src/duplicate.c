#include "duplicate.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "log.h"
#include "prompt.h"
#include "hash.h"

// Externs for shared state
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

void handle_duplicates(int dryRunFlag, int interactiveFlag, int useSHA256Flag, FILE *logFilePtr) {
    for (int i = 0; i < fileCount; i++) {
        for (int j = i + 1; j < fileCount; j++) {
            if (fileList[i].size != fileList[j].size) continue;
            int hashLen = useSHA256Flag ? 32 : 16;
            if (memcmp(fileList[i].hash, fileList[j].hash, hashLen) == 0) {
                printf("⚠️  Duplicate: %s\n", fileList[j].path);
                log_msg(logFilePtr, "Duplicate: %s\n", fileList[j].path);
                if (!dryRunFlag) {
                    if (interactiveFlag && !prompt_user(fileList[j].path)) {
                        printf("🚫 Skipped: %s\n", fileList[j].path);
                        continue;
                    }
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