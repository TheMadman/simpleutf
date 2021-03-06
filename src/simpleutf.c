#include "simpleutf.h"

#define MARKER_BIT_FIRST (1 << 7)
#define MARKER_BIT_SECOND (1 << 6)
#define MARKER_BITS (MARKER_BIT_FIRST | MARKER_BIT_SECOND)

static int continuation_bytes(const char *bytes, size_t max_length)
{
	int result = 2;
	for (; max_length; max_length--) {
		switch (*bytes & MARKER_BITS) {
			case 0:
			case MARKER_BIT_SECOND:
			case MARKER_BIT_FIRST | MARKER_BIT_SECOND:
				return result;
			case MARKER_BIT_FIRST:
				++result;
				++bytes;
				break;
		}
	}
}

static int first_continuation_byte(const char *bytes, size_t max_length)
{
	switch (*bytes & MARKER_BITS) {
		case 0:
		case MARKER_BIT_SECOND:
		case MARKER_BIT_FIRST | MARKER_BIT_SECOND:
			return 0;
		case MARKER_BIT_FIRST:
			return continuation_bytes(bytes + 1, max_length - 1);
	}
}

int sutf8_len(const char *bytes, size_t max_length)
{
	switch (*bytes & MARKER_BITS) {
		case 0:
		case MARKER_BIT_SECOND:
			return 1;
		case MARKER_BIT_FIRST | MARKER_BIT_SECOND:
			return first_continuation_byte(bytes + 1, max_length - 1);
		case MARKER_BIT_FIRST:
			return 0;
	}
}
