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

void patterns_add_pattern(Patterns* self, char* pattern) {
	if (!self)
		exit(EXIT_FAILURE);

	Node* new_pattern = malloc(sizeof(*(self->patterns)));
	if (!new_pattern)
		exit(EXIT_FAILURE);

	new_pattern->string = pattern;
	new_pattern->next = NULL;

	if (!self->patterns) {
		self->patterns = new_pattern;
		self->last = new_pattern;
		return;
	}

	self->last->next = new_pattern;
	self->last = new_pattern;
}

int patterns_is_match(Patterns* self, char* string) {
	if (!self)
		exit(EXIT_FAILURE);

	if (!self->patterns)
		return 0;

	Node* curr = self->patterns;
	while (curr) {
		if (fnmatch(curr->string, string, 0) == 0)
			return 1;
		curr = curr->next;
	}
	return 0;
}

void patterns_free(Patterns* patterns) {}

