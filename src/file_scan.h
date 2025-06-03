// file_scan.h: Header for directory scanning and file registration routines.
// Declares the interface for scanning directories and processing files.

#ifndef FILE_SCAN_H
#define FILE_SCAN_H

#include <sys/stat.h>
#include <ftw.h>

// Called for each file found by nftw().
int processFile(const char *path, const struct stat *sb, int typeflag, struct FTW *ftwbuf);
// Starts a directory scan (recursive or not).
void scan_directory(const char *targetDir, int recursive);

#endif // FILE_SCAN_H