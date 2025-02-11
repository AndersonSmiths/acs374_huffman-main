#include "priority_queue.h"
#include "cu_unit.h"

static int _cmp_int(const void *a, const void *b)
{
  int x = *((int *)a);
  int y = *((int *)b);
  return x - y;
}

static void _print_int(void *a_n)
{
  int n = *((int *)a_n);
  printf("%d", n);
}

static int _test_simple_pq()
{
  cu_start();
  // -------------------------------
  PQNode *head = NULL;
  int n1 = 5, n2 = 7, n3 = 6;
  pq_enqueue(&head, &n1, _cmp_int);
  pq_enqueue(&head, &n2, _cmp_int);
  pq_enqueue(&head, &n3, _cmp_int);
  cu_check(head != NULL);
  PQNode *first_node = pq_dequeue(&head);
  cu_check(*((int *)first_node->a_value) == 5);
  PQNode *second_node = pq_dequeue(&head);
  cu_check(*((int *)second_node->a_value) == 6);
  PQNode *third_node = pq_dequeue(&head);
  cu_check(*((int *)third_node->a_value) == 7);
  cu_check(head == NULL);
  free(first_node);
  free(second_node);
  free(third_node);
  // -------------------------------
  cu_end();
}

static int _test_simple_stack()
{
  cu_start();
  // -------------------------------
  PQNode *stack = NULL;
  int n1 = 5, n2 = 7, n3 = 6;
  stack_push(&stack, &n1);
  stack_push(&stack, &n2);
  stack_push(&stack, &n3);
  cu_check(stack != NULL);
  PQNode *first_node = stack_pop(&stack);
  cu_check(*((int *)first_node->a_value) == 6);
  PQNode *second_node = stack_pop(&stack);
  cu_check(*((int *)second_node->a_value) == 7);
  PQNode *third_node = stack_pop(&stack);
  cu_check(*((int *)third_node->a_value) == 5);
  cu_check(stack == NULL);
  free(first_node);
  free(second_node);
  free(third_node);
  // -------------------------------
  cu_end();
}

int main(int argc, char *argv[])
{
  cu_start_tests();
  cu_run(_test_simple_pq);
  cu_run(_test_simple_stack);
  cu_end_tests();
  return EXIT_SUCCESS;
}