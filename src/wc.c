#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <fts.h>

#include "wc.h"

/* this is simpler (no flags) linux wc program */
void wc(char* filename, WcResult* result) {
	if (result == NULL)
		exit(EXIT_FAILURE);
	
	FILE* in = (filename == NULL) ? stdin : fopen(filename, "r");
	int ch;
	int prev = ' ';

	if (in == NULL) {
		fprintf(stderr, "cannot open file %s\n", filename);
		exit(EXIT_FAILURE);
	}

	while((ch = fgetc(in)) != EOF) {
		if (ch == '\n')
			result->lines++;
		if (isspace(prev) && !isspace(ch))
			result->words++;
		prev = ch;
		result->chars++;
	}

	fclose(in);
}

void wc_print_result(WcResult* result, char* path) {
	printf("%8ld %9ld %11ld %s\n", result->lines, result->words, result->chars, path);
}

void rwc(FTSENT* fts_ent, WcResult* total) {
	WcResult curr = {0, 0, 0};
	wc(fts_ent->fts_accpath, &curr);
	total->lines += curr.lines;
	total->words += curr.words;
	total->chars += curr.chars;

	wc_print_result(&curr, fts_ent->fts_path);
}
