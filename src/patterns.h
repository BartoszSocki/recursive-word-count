#ifndef _U_PATTERNS_H_
#define _U_PATTERNS_H_

typedef struct StringNode_t {
	struct StringNode_t* next;
	char* string;
} StringNode;

typedef struct _Patterns {
	StringNode* patterns;
	StringNode* last;
} Patterns;

Patterns* patterns_init();
int patterns_add_pattern(Patterns* self, char* pattern);
int patterns_is_match(Patterns* self, char* string);
void patterns_free(Patterns* self);

#endif
