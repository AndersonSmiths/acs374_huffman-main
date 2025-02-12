#include "priority_queue.h"
#include "cu_unit.h"
#include <string.h>


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

static int _cmp_string(const void *a, const void *b)
{
  return strcmp((const char *)a, (const char *)b);
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

  // empty case
  cu_check(stack_pop(&stack) == NULL);

  cu_end();
}

static int _test_priority_queue() {
  cu_start();


    PQNode *head = NULL;
    int anderson = 5, conner = 7, smith = 6;
    pq_enqueue(&head, &anderson, _cmp_int);
    pq_enqueue(&head, &conner, _cmp_int);
    pq_enqueue(&head, &smith, _cmp_int);

    cu_check(head != NULL);
    cu_check(*((int *)pq_dequeue(&head)->a_value) == 5);
    cu_check(*((int *)pq_dequeue(&head)->a_value) == 6);
    cu_check(*((int *)pq_dequeue(&head)->a_value) == 7);
    cu_check(head == NULL);


  // repeating cases
  int fozzie = 29, lilly = 29, wally = 29;
  pq_enqueue(&head, &fozzie, _cmp_int);
  pq_enqueue(&head, &lilly, _cmp_int);
  pq_enqueue(&head, &wally, _cmp_int);

  // 29 bc its my fav number :D 
  cu_check(*((int *)pq_dequeue(&head)->a_value) == 29);
  cu_check(*((int *)pq_dequeue(&head)->a_value) == 29);
  cu_check(*((int *)pq_dequeue(&head)->a_value) == 29);
  cu_check(head == NULL);

  // tie case TODO: figure out whether or not the prompt 
  // says that it is supposed to be done a certain way
  int reggie = 29, myrtle = 29;
  pq_enqueue(&head, &reggie, _cmp_int);
  pq_enqueue(&head, &myrtle, _cmp_int);
  cu_check(*((int *)pq_dequeue(&head)->a_value) == 29);
  cu_check(*((int *)pq_dequeue(&head)->a_value) == 29);
  cu_check(head == NULL);

  /// empty case 
  PQNode *head2 = NULL;
  cu_check(pq_dequeue(&head) == NULL);


  pq_enqueue(&head2, NULL, _cmp_int);
  cu_check(pq_dequeue(&head) == NULL);

  cu_end();
}


// static int _test_string_case()
// {
//   cu_start();
//   // -------------------------------
//   PQNode *head = NULL;
//   char *anderson = "anderson";
//   char *conner = "conner";
//   char *smith = "smith";
//   pq_enqueue(&head, anderson, _cmp_string);
//   pq_enqueue(&head, conner, _cmp_string);
//   pq_enqueue(&head, smith, _cmp_string);
  
//   cu_check(strcmp((char *)pq_dequeue(&head)->a_value, "anderson") == 0);
//   cu_check(strcmp((char *)pq_dequeue(&head)->a_value, "conner") == 0);
//   cu_check(strcmp((char *)pq_dequeue(&head)->a_value, "smith") == 0);
//   cu_check(head == NULL);
//   // -------------------------------
//   cu_end();
// }


int main(int argc, char *argv[])
{
  cu_start_tests();
  cu_run(_test_simple_pq);
  cu_run(_test_simple_stack);
  cu_run(_test_priority_queue);
  cu_end_tests();
  return EXIT_SUCCESS; 
}