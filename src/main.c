#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fts.h>
#include "wc.h"
#include "patterns.h"

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

	WcResult total = {0, 0, 0};
	while ((node = fts_read(fs)) != NULL) {
		if (node->fts_info == FTS_F) {
			if (!patterns_is_match(whitelist, node->fts_path))
				continue;
			/* printf("%s is a match\n", node->fts_path); */
			/* printf("%s\n", node->fts_path); */
			/* printf("%s\n", node->fts_accpath); */
			rwc(node, &total);
		}
	}
	wc_print_result(&total, "total");
}
