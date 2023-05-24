#include "shell.h"

/**
 * befree - free a pointer and NULLifies the address
 * @ptr: address of the pointer that needs freeing
 * Return: 1 if free succesfully, if not 0
 */
int befree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
