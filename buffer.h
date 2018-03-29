#ifndef BUFFER_H
#define BUFFER_H

typedef struct char_array {
	char* *grid;
	struct char_array *char_ptr;
	int numRows;
	int numCols;
} buffer;

#endif