/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:21:23 by dda-cunh          #+#    #+#             */
/*   Updated: 2025/10/27 13:06:57 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

typedef enum e_test_type
{
	TT_BASIC_ALLOC_FREE,
	TT_REALLOC_BEHAVIOR,
	TT_ZONE_MANAGEMENT,
	TT_MEMORY_REUSE,
	TT_EDGE_CASES,
	TT_STRESS_EXHAUSTION,
	TT_ALIGNMENT_BOUNDARY,
	TT_SIZE
}	TestType;

static char	*test_type_to_str(TestType tt)
{
	switch (tt)
	{
		case TT_BASIC_ALLOC_FREE:
			return ("Basic Allocation and Freeing");
		case TT_REALLOC_BEHAVIOR:
			return ("Reallocation Behavior (Grow/Shrink/NULL)");
		case TT_ZONE_MANAGEMENT:
			return ("Zone Management (TINY/SMALL/LARGE boundaries)");
		case TT_MEMORY_REUSE:
			return ("Memory Reuse and Fragmentation");
		case TT_EDGE_CASES:
			return ("Edge Cases (NULL, 0-size, double free)");
		case TT_STRESS_EXHAUSTION:
			return ("Stress/Exhaustion (mass allocations)");
		case TT_ALIGNMENT_BOUNDARY:
			return ("Alignment and Boundary Behavior");
		default:
			return ("Unknown Test");
	}
}


static void	test_basic_alloc_free(void)
{
	printf(CLI_COLORS_YELLOW "BASIC test 1 (malloc/free):\n" CLI_COLORS_RESET);

	void *a = malloc(16);
	void *b = malloc(512);
	void *c = malloc(5000);

	if (!a || !b || !c)
	{
		printf(CLI_COLORS_RED "\tAllocation failed!\n" CLI_COLORS_RESET);
		return;
	}

	printf("\tAllocated: %p (16B), %p (512B), %p (5000B)\n", a, b, c);
	ft_memset(a, 0xAA, 16);
	ft_memset(b, 0xBB, 512);
	ft_memset(c, 0xCC, 5000);

	free(a);
	free(b);
	free(c);

	printf(CLI_COLORS_GREEN "\tSUCCESS: Freed all without crash.\n" CLI_COLORS_RESET);
}


static void	test_realloc_behavior(void)
{
	printf(CLI_COLORS_YELLOW "REALLOC test 1 (grow/shrink):\n" CLI_COLORS_RESET);

	char *p = malloc(64);
	if (!p)
	{
		printf(CLI_COLORS_RED "\tmalloc(64) failed!\n" CLI_COLORS_RESET);
		return;
	}
	ft_memset(p, 'X', 63);
	p[63] = '\0';

	char *p2 = realloc(p, 128);
	printf("\tGrow: old=%p new=%p\n", p, p2);
	printf("\tPreserved data: %.10s...\n", p2);

	char *p3 = realloc(p2, 32);
	printf("\tShrink: %p -> %p\n", p2, p3);

	free(p3);

	printf(CLI_COLORS_YELLOW "REALLOC test 2 (NULL):\n" CLI_COLORS_RESET);
	char *p4 = realloc(NULL, 50);
	if (p4)
	{
		printf(CLI_COLORS_GREEN "\tSUCCESS: realloc(NULL, n) behaves like malloc (%p)\n" CLI_COLORS_RESET, p4);
		free(p4);
	}
	else
		printf(CLI_COLORS_RED "\tFAILURE: realloc(NULL, n) returned NULL.\n" CLI_COLORS_RESET);
}

static void	test_zone_management(void)
{
	printf(CLI_COLORS_YELLOW "ZONE test (boundary allocations):\n" CLI_COLORS_RESET);

	void *tiny = malloc(TINY_BLOCK_SIZE);
	void *small = malloc(SMALL_BLOCK_SIZE);
	void *large = malloc(SMALL_BLOCK_SIZE + 1);

	if (!tiny || !small || !large)
	{
		printf(CLI_COLORS_RED "\tAllocation failed!\n" CLI_COLORS_RESET);
		return;
	}

	printf("\tTINY  at %p | is Fixed:%ld\n", tiny, IS_FIXED(GET_HEADER(GET_BLOCK(tiny))));
	printf("\tSMALL at %p | is Fixed:%ld\n", small, IS_FIXED(GET_HEADER(GET_BLOCK(small))));
	printf("\tTINY  at %p | is Fixed:%ld\n", large, IS_FIXED(GET_HEADER(GET_BLOCK(large))));

	free(tiny);
	free(small);
	free(large);

	printf(CLI_COLORS_GREEN "\tSUCCESS: Freed all zones.\n" CLI_COLORS_RESET);
}

static void	test_memory_reuse(void)
{
	printf(CLI_COLORS_YELLOW "MEMORY REUSE test:\n" CLI_COLORS_RESET);

	void *a = malloc(64);
	if (!a)
	{
		printf(CLI_COLORS_RED "\tmalloc(64) failed!\n" CLI_COLORS_RESET);
		return;
	}
	free(a);
	void *b = malloc(64);
	if (a == b)
		printf(CLI_COLORS_GREEN "\tSUCCESS: Freed block reused (same pointer: %p).\n" CLI_COLORS_RESET, b);
	else
		printf(CLI_COLORS_YELLOW "\tNOTE: Different pointer (no reuse or defragmentation logic).\n" CLI_COLORS_RESET);
	free(b);
}

static void	test_edge_cases(void)
{
	printf(CLI_COLORS_YELLOW "EDGE CASES test:\n" CLI_COLORS_RESET);

	printf("\tfree(NULL)...\n");
	free(NULL);

	void *p = malloc(10);
	free(p);
	printf("\tDouble-free test...\n");
	free(p);

	void *z = malloc(0);
	if (!z)
		printf(CLI_COLORS_GREEN "\tmalloc(0) returned NULL as expected.\n" CLI_COLORS_RESET);
	else
	{
		printf(CLI_COLORS_YELLOW "\tmalloc(0) returned non-NULL pointer: %p\n" CLI_COLORS_RESET, z);
		free(z);
	}
}

static void	test_stress_exhaustion(void)
{
	printf(CLI_COLORS_YELLOW "STRESS test (many tiny allocations):\n" CLI_COLORS_RESET);

	const int n = 500;
	void *ptrs[n];
	int i;

	for (i = 0; i < n; i++)
	{
		ptrs[i] = malloc(32);
		if (!ptrs[i])
		{
			printf(CLI_COLORS_RED "\tFailed at allocation %d!\n" CLI_COLORS_RESET, i);
			break;
		}
	}

	printf("\tAllocated %d tiny blocks.\n", i);
	for (int j = 0; j < i; j++)
		free(ptrs[j]);
	printf("\tFreed all successfully.\n");
}

static void	test_alignment_boundary(void)
{
	printf(CLI_COLORS_YELLOW "ALIGNMENT test:\n" CLI_COLORS_RESET);

	void *p = malloc(13);
	if (!p)
	{
		printf(CLI_COLORS_RED "\tmalloc(13) failed!\n" CLI_COLORS_RESET);
		return;
	}

	_size_t *header = GET_HEADER(GET_BLOCK(p));

	if ((uintptr_t)header % sysconf(_SC_PAGESIZE) == 0)
		printf(CLI_COLORS_GREEN "\tSUCCESS: mmap() returned page-aligned block (%p)\n" CLI_COLORS_RESET, p);
	else
		printf(CLI_COLORS_RED "\tFAILURE: base address not page aligned (%p)\n" CLI_COLORS_RESET, p);

	free(p);
}

static void	do_test(TestType test_type)
{
	printf(CLI_COLORS_CYAN "--------- Starting Test for %s ---------\n" CLI_COLORS_RESET,
		test_type_to_str(test_type));

	switch (test_type)
	{
		case TT_BASIC_ALLOC_FREE:
			test_basic_alloc_free();
			break;
		case TT_REALLOC_BEHAVIOR:
			test_realloc_behavior();
			break;
		case TT_ZONE_MANAGEMENT:
			test_zone_management();
			break;
		case TT_MEMORY_REUSE:
			test_memory_reuse();
			break;
		case TT_EDGE_CASES:
			test_edge_cases();
			break;
		case TT_STRESS_EXHAUSTION:
			test_stress_exhaustion();
			break;
		case TT_ALIGNMENT_BOUNDARY:
			test_alignment_boundary();
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
		do_test(i);

	return (0);
}
