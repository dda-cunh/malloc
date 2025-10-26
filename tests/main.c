/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:21:23 by dda-cunh          #+#    #+#             */
/*   Updated: 2025/10/26 13:54:24 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

typedef enum	e_test_type
{
	TT_STRING_TINY,
	TT_STRING_SMALL,
	TT_STRING_LARGE,
	TT_INT,
	TT_STRUCT,
	TT_STRUCT_ARR,
	TT_SIZE
}	TestType;

typedef struct	s_long_trio
{
	long	a;
	long	b;
	long	c;
}	LongTrio;

static char	*test_type_to_str(TestType tt)
{
	switch (tt)
	{
		case TT_STRING_TINY:
			return ("TINY Allocations (<= 128 bytes)");
		case TT_STRING_SMALL:
			return ("SMALL Allocations (<= 1024 bytes)");
		case TT_STRING_LARGE:
			return ("LARGE Allocations (> 1024 bytes)");
		case TT_INT:
			return ("Simple INT & Edge Cases");
		case TT_STRUCT:
			return ("Struct Allocation");
		case TT_STRUCT_ARR:
			return ("Struct Array & Realloc");
		default:
			return ("Unknown Test");
	}
}

static void	test_string_tiny()
{
	char *s1;

	// 1. Basic alloc, write, and free
	s1 = malloc(10);
	if (!s1) {
		printf(CLI_COLORS_RED "TINY test 1: malloc(10) failed!\n" CLI_COLORS_RESET);
		return;
	}
	ft_strcpy(s1, "Hello");
	printf("TINY test 1: Value: \"%s\" at %p\n", s1, s1);
	free(s1);
	printf("TINY test 1: Freed.\n");

	// 2. Test block reuse
	printf(CLI_COLORS_YELLOW "TINY test 2 (Reuse): Allocating p1(8) and p2(8)\n" CLI_COLORS_RESET);
	char *p1 = malloc(8);
	char *p2 = malloc(8);
	printf("p1: %p, p2: %p\n", p1, p2);
	printf("Freeing p1...\n");
	free(p1);
	char *p3 = malloc(8);
	printf("Allocating p3(8): %p\n", p3);
	if (p1 == p3)
		printf(CLI_COLORS_GREEN "  SUCCESS: p3 reused p1's slot.\n" CLI_COLORS_RESET);
	else
		printf(CLI_COLORS_CYAN "  NOTE: p3 did not reuse p1's slot (might be ok depending on algo).\n" CLI_COLORS_RESET);
	free(p2);
	free(p3);
	
	// 3. Realloc (grow, TINY -> TINY)
	printf(CLI_COLORS_YELLOW "TINY test 3 (Realloc Grow T->T):\n" CLI_COLORS_RESET);
	char *s2 = malloc(20);
	ft_strcpy(s2, "Tiny alloc");
	printf("  Original: \"%s\" at %p\n", s2, s2);
	char *s3 = realloc(s2, 50); // Should trigger new malloc, copy, free
	printf("  Realloc'd: \"%s\" at %p\n", s3, s3);
	if (s2 != s3 && ft_strcmp(s3, "Tiny alloc") == 0)
		printf(CLI_COLORS_GREEN "  SUCCESS: Pointer changed, data preserved.\n" CLI_COLORS_RESET);
	else
		printf(CLI_COLORS_RED "  FAILURE: Pointer same or data lost.\n" CLI_COLORS_RESET);
	
	// 4. Realloc (grow, TINY -> SMALL)
	printf(CLI_COLORS_YELLOW "TINY test 4 (Realloc Grow T->S):\n" CLI_COLORS_RESET);
	ft_strcpy(s3, "Original data");
	printf("  Original: \"%s\" at %p\n", s3, s3);
	char *s4 = realloc(s3, 200); // Should trigger new SMALL malloc
	printf("  Realloc'd: \"%s\" at %p\n", s4, s4);
	if (s3 != s4 && ft_strcmp(s4, "Original data") == 0)
		printf(CLI_COLORS_GREEN "  SUCCESS: Pointer changed, data preserved.\n" CLI_COLORS_RESET);
	else
		printf(CLI_COLORS_RED "  FAILURE: Pointer same or data lost.\n" CLI_COLORS_RESET);
	free(s4);

	// 5. Zone Exhaustion (TINY_BLOCKS is 288)
	printf(CLI_COLORS_YELLOW "TINY test 5 (Zone Exhaustion):\n" CLI_COLORS_RESET);
	int num_blocks = 300; // More than TINY_BLOCKS
	void *ptrs[num_blocks];
	int i;
	for (i = 0; i < num_blocks; i++) {
		ptrs[i] = malloc(10);
		if (!ptrs[i]) {
			printf(CLI_COLORS_RED "  Exhaustion test failed at allocation %d\n" CLI_COLORS_RESET, i);
			break;
		}
	}
	if (i == num_blocks)
		printf("  Allocated %d tiny blocks successfully.\n", num_blocks);
	
	// Check if the last block is NOT fixed (i.e., it's a large mmap)
	_size_t *h1 = GET_HEADER(GET_BLOCK(ptrs[0]));
	_size_t *h_last = GET_HEADER(GET_BLOCK(ptrs[num_blocks - 1]));
	printf("  First block (zone) IS_FIXED: %ld (expected 1)\n", IS_FIXED(h1));
	printf("  Last block (mmap'd) IS_FIXED: %ld (expected 0)\n", IS_FIXED(h_last));

	for (i = 0; i < num_blocks; i++) {
		free(ptrs[i]);
	}
	printf("  Freed %d tiny blocks.\n", num_blocks);
}

static void	test_string_small()
{
	// 1. Basic alloc, write, and free
	printf(CLI_COLORS_YELLOW "SMALL test 1 (Basic):\n" CLI_COLORS_RESET);
	size_t small_size = 500;
	char *s1 = malloc(small_size);
	if (!s1) {
		printf(CLI_COLORS_RED "  malloc(500) failed!\n" CLI_COLORS_RESET);
		return;
	}
	ft_memset(s1, 'A', small_size - 1);
	s1[small_size - 1] = '\0';
	printf("  Allocated 500 bytes at %p. s1[0] = %c, s1[498] = %c\n", s1, s1[0], s1[498]);
	
	// 2. Realloc (shrink, SMALL)
	printf(CLI_COLORS_YELLOW "SMALL test 2 (Realloc Shrink):\n" CLI_COLORS_RESET);
	char *s2 = realloc(s1, 200);
	printf("  Realloc'd to 200 bytes at %p.\n", s2);
	if (s1 == s2 && s2[0] == 'A' && s2[198] == 'A')
		printf(CLI_COLORS_GREEN "  SUCCESS: Pointer is same, data preserved.\n" CLI_COLORS_RESET);
	else
		printf(CLI_COLORS_RED "  FAILURE: Pointer changed or data lost.\n" CLI_COLORS_RESET);
	free(s2); // s2 is same as s1, so this frees the block.
}

static void	test_string_large()
{
	// 1. Basic alloc, write, and free
	printf(CLI_COLORS_YELLOW "LARGE test 1 (Basic):\n" CLI_COLORS_RESET);
	size_t large_size = 5000; // > SMALL_BLOCK_SIZE
	char *s1 = malloc(large_size);
	if (!s1) {
		printf(CLI_COLORS_RED "  malloc(5000) failed!\n" CLI_COLORS_RESET);
		return;
	}
	ft_memset(s1, 'B', large_size - 1);
	s1[large_size - 1] = '\0';
	printf("  Allocated 5000 bytes at %p. s1[0] = %c, s1[4998] = %c\n", s1, s1[0], s1[4998]);

	// 2. Realloc (grow, LARGE -> LARGE)
	printf(CLI_COLORS_YELLOW "LARGE test 2 (Realloc Grow L->L):\n" CLI_COLORS_RESET);
	char *s2 = realloc(s1, large_size * 2);
	printf("  Realloc'd to 10000 bytes at %p.\n", s2);
	if (s1 != s2 && s2[0] == 'B' && s2[4998] == 'B')
		printf(CLI_COLORS_GREEN "  SUCCESS: Pointer changed, data preserved.\n" CLI_COLORS_RESET);
	else
		printf(CLI_COLORS_RED "  FAILURE: Pointer same or data lost.\n" CLI_COLORS_RESET);
	
	// 3. Realloc (shrink, LARGE)
	// Your realloc attempts to munmap the difference, but the pointer should stay
	printf(CLI_COLORS_YELLOW "LARGE test 3 (Realloc Shrink L->L):\n" CLI_COLORS_RESET);
	char *s3 = realloc(s2, large_size / 2);
	printf("  Realloc'd to 2500 bytes at %p.\n", s3);
	if (s2 == s3 && s3[0] == 'B' && s3[2498] == 'B')
		printf(CLI_COLORS_GREEN "  SUCCESS: Pointer is same, data preserved.\n" CLI_COLORS_RESET);
	else
		printf(CLI_COLORS_RED "  FAILURE: Pointer changed or data lost.\n" CLI_COLORS_RESET);
	
	free(s3);
}

static void	test_int()
{
	// 1. Simple int alloc
	printf(CLI_COLORS_YELLOW "INT test 1 (Basic):\n" CLI_COLORS_RESET);
	int *i = malloc(sizeof(int));
	if (!i) {
		printf(CLI_COLORS_RED "  malloc(sizeof(int)) failed!\n" CLI_COLORS_RESET);
		return;
	}
	*i = 12345;
	printf("  Value: %d at %p\n", *i, i);
	free(i);

	// 2. Test free(NULL)
	printf(CLI_COLORS_YELLOW "INT test 2 (free(NULL)):\n" CLI_COLORS_RESET);
	printf("  Calling free(NULL)...\n");
	free(NULL);
	printf(CLI_COLORS_GREEN "  ...free(NULL) did not crash.\n" CLI_COLORS_RESET);

	// 3. Test realloc(NULL, size)
	printf(CLI_COLORS_YELLOW "INT test 3 (realloc(NULL, size)):\n" CLI_COLORS_RESET);
	int *i2 = realloc(NULL, sizeof(int));
	if (!i2) {
		printf(CLI_COLORS_RED "  realloc(NULL, ...) failed!\n" CLI_COLORS_RESET);
		return;
	}
	*i2 = 54321;
	printf("  Value: %d at %p (should be like malloc)\n", *i2, i2);
	free(i2);
}

static void	test_struct()
{
	printf(CLI_COLORS_YELLOW "STRUCT test 1 (Basic):\n" CLI_COLORS_RESET);
	LongTrio *t = malloc(sizeof(LongTrio)); // 3 * 8 = 24 bytes (TINY)
	if (!t) {
		printf(CLI_COLORS_RED "  malloc(sizeof(LongTrio)) failed!\n" CLI_COLORS_RESET);
		return;
	}
	t->a = 111111111L;
	t->b = 222222222L;
	t->c = 333333333L;
	printf("  Struct at %p: a=%ld, b=%ld, c=%ld\n", t, t->a, t->b, t->c);
	free(t);
}

static void	test_struct_arr()
{
	printf(CLI_COLORS_YELLOW "STRUCT_ARR test 1 (Basic):\n" CLI_COLORS_RESET);
	int count = 50;
	// 50 * 24 bytes = 1200 bytes (LARGE allocation)
	LongTrio *arr = malloc(sizeof(LongTrio) * count);
	if (!arr) {
		printf(CLI_COLORS_RED "  malloc(sizeof(LongTrio) * 50) failed!\n" CLI_COLORS_RESET);
		return;
	}

	for (int i = 0; i < count; i++)
	{
		arr[i].a = i;
		arr[i].b = i * 2;
		arr[i].c = i * 3;
	}
	printf("  Allocated array at %p.\n", arr);
	printf("  arr[10]: a=%ld, b=%ld, c=%ld\n", arr[10].a, arr[10].b, arr[10].c);
	printf("  arr[49]: a=%ld, b=%ld, c=%ld\n", arr[49].a, arr[49].b, arr[49].c);
	
	// 2. Realloc (grow)
	printf(CLI_COLORS_YELLOW "STRUCT_ARR test 2 (Realloc Grow):\n" CLI_COLORS_RESET);
	int new_count = 100;
	LongTrio *arr2 = realloc(arr, sizeof(LongTrio) * new_count);
	if (!arr2) {
		printf(CLI_COLORS_RED "  realloc to %d elements failed!\n" CLI_COLORS_RESET, new_count);
		free(arr); // Free original block
		return;
	}
	
	printf("  Realloc'd array at %p.\n", arr2);
	
	// Check old data
	if (arr2[10].a == 10 && arr2[10].b == 20 && arr2[49].a == 49)
		printf(CLI_COLORS_GREEN "  SUCCESS: Old data preserved after realloc.\n" CLI_COLORS_RESET);
	else
		printf(CLI_COLORS_RED "  FAILURE: Old data lost after realloc.\n" CLI_COLORS_RESET);

	// Add new data
	for (int i = count; i < new_count; i++)
	{
		arr2[i].a = i;
		arr2[i].b = i * 2;
		arr2[i].c = i * 3;
	}
	printf("  arr2[99]: a=%ld, b=%ld, c=%ld\n", arr2[99].a, arr2[99].b, arr2[99].c);

	free(arr2);
}

static void	do_test(TestType test_type)
{
	printf(CLI_COLORS_CYAN "--------- Starting Test for %s ---------\n" CLI_COLORS_RESET, test_type_to_str(test_type));

	switch (test_type)
	{
		case TT_STRING_TINY:
			test_string_tiny();
			break;
		case TT_STRING_SMALL:
			test_string_small();
			break;
		case TT_STRING_LARGE:
			test_string_large();
			break;
		case TT_INT:
			test_int();
			break;
		case TT_STRUCT:
			test_struct();
			break;
		case TT_STRUCT_ARR:
			test_struct_arr();
			break;
		default:
			printf(CLI_COLORS_RED "Unknown test type!\n" CLI_COLORS_RESET);
			break;
	}

	printf(CLI_COLORS_CYAN "------------------------------------------------\n\n" CLI_COLORS_RESET);
}

int	main(void)
{
	for (int i = 0; i < TT_SIZE; i++)
	{
		do_test(i);
	}

	return (0);
}