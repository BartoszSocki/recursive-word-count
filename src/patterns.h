#ifndef _U_PATTERNS_H_
#define _U_PATTERNS_H_

typedef struct _StringNode {
	struct _StringNode* next;
	char* string;
} Node;

typedef struct _Patterns {
	Node* patterns;
	Node* last;
} Patterns;

Patterns* patterns_init();
void patterns_add_pattern(Patterns* self, char* pattern);
int patterns_is_match(Patterns* self, char* string);
void patterns_free(Patterns* patterns);

#endif
