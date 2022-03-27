#include <stdio.h>
#include <stdlib.h>
#include <fnmatch.h>
#include "patterns.h"

Patterns* patterns_init() {
	Patterns* patterns = malloc(sizeof(*patterns));
	if (!patterns)
		return NULL;

	patterns->patterns = NULL;
	patterns->last = NULL;
	return patterns;
}

int patterns_add_pattern(Patterns* self, char* pattern) {
	if (!self)
		return 1;

	StringNode* new_pattern = malloc(sizeof(*(self->patterns)));
	if (!new_pattern)
		return 1;

	new_pattern->string = pattern;
	new_pattern->next = NULL;

	if (!self->patterns) {
		self->patterns = new_pattern;
		self->last = new_pattern;
		return 0;
	}

	self->last->next = new_pattern;
	self->last = new_pattern;
	return 0;
}

int patterns_is_match(Patterns* self, char* string) {
	if (self == NULL)
		return 0;

	if (self->patterns == NULL)
		return 0;

	if (string == NULL)
		return 0;

	StringNode* curr = self->patterns;
	while (curr) {
		if (fnmatch(curr->string, string, 0) == 0)
			return 1;
		curr = curr->next;
	}
	return 0;
}

void patterns_free(Patterns* self) {
	if (self == NULL)
		return;

	StringNode* prev;
	StringNode* node = self->patterns;
	while (node) {
		prev = node;
		node = node->next;
		free(prev);
	}
}
