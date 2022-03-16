#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fts.h>
#include "wc.h"
#include "patterns.h"

/* 10 MB */
#define MAX_GOOD_SIZE 10000000

int main(int argc, char** argv) {
	int opt;
	char* path = ".";
	Patterns* whitelist = patterns_init();

	while ((opt = getopt(argc, argv, "d:w:")) != -1) {
		switch (opt) {
			case 'd':
				path = optarg;
				break;
			case 'w':
				patterns_add_pattern(whitelist, optarg);
				break;
			default:
				break;
		}
	}
	
	int options = FTS_PHYSICAL;
	char* paths[] = {path, NULL};
	FTS* fs = fts_open(paths, options, NULL);
	FTSENT* node = NULL;

	struct stat file_stats;
	WcResult total = {0, 0, 0};
	while ((node = fts_read(fs)) != NULL) {
		if (node->fts_info == FTS_F) {
			if (whitelist->patterns && !patterns_is_match(whitelist, node->fts_path))
				continue;

			stat(node->fts_accpath, &file_stats);
			if (file_stats.st_size >= MAX_GOOD_SIZE) {
				WcResult big_file_results = {0, 0, file_stats.st_size};
				total.chars += file_stats.st_size;

				wc_print_result(&big_file_results, node->fts_path);
				continue;
			}

			rwc(node, &total);
		}
	}
	wc_print_result(&total, "total");
}
