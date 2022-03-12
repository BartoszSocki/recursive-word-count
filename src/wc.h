#ifndef _U_WC_H_
#define _U_WC_H_

#include <fts.h>

typedef struct _WcResult {
	long lines;
	long words;
	long chars;
} WcResult;

void wc(char* filename, WcResult* result);
void wc_print_result(WcResult* result, char* path);
void rwc(FTSENT* fts_ent, WcResult* total);

#endif
