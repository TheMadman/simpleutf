#include "simpleutf.h"
#include <stdio.h>
#include <assert.h>

#define print(template, ...) fprintf(stderr, "%s:%d" template, __FILE__, __LINE__, __VA_ARGS__)

int main()
{
	{
		const char string[] = "a";
		int result = sutf8_len(string, sizeof(string));
		int expected = 1;
		if (expected != result) {
			print("Unexpected result: %d\n", result);
			return 1;
		}
	}

	{
		const char string[] = "💩";
		int result = sutf8_len(string, sizeof(string));
		int expected = 4;
		if (expected != result) {
			print("Unexpected result: %d\n", result);
			return 1;
		}
	}

	{
		const char string[] = "💩💩";
		int result = sutf8_len(string, sizeof(string));
		int expected = 4;
		if (expected != result) {
			print("Unexpected result: %d\n", result);
			return 1;
		}
	}

	{
		// invalid - two starter bytes
		const char string[] = "\xf0\xf0";
		int result = sutf8_len(string, sizeof(string));
		int expected = 0;
		if (expected != result) {
			print("Unexpected result: %d\n", result);
			return 1;
		}
	}

	{
		// invalid - starts with continuation bit
		const char string[] = "\x9f\x92\xa9";
		int result = sutf8_len(string, sizeof(string));
		int expected = 0;
		if (expected != result) {
			print("Unexpected result: %d\n", result);
			return 1;
		}
	}

	return 0;
}
