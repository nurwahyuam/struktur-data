#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

struct stack
{
  int count;
  int maxKapasitas;
  struct node *top;
};
struct node
{
  int data;
  struct node *next;
};
typedef struct stack stack;
typedef struct node node;

stack *buatStack(int kapasitas)
{
  stack *stack = (struct stack *)malloc(sizeof(struct stack));
  stack->count = 0;
  stack->maxKapasitas = kapasitas;
  stack->top = NULL;
  return stack;
}
void pushStack(stack *stack, int value)
{
  if (stack->count >= stack->maxKapasitas)
  {
    printf("Stack Overflow! Stack is full");
    getch();
    return;
  }
  node *nodeBaru = (struct node *)malloc(sizeof(struct node));
  if (nodeBaru == NULL)
  {
    printf("Stack Overflow");
    getch();
    return;
  }
  nodeBaru->data = value;
  nodeBaru->next = stack->top;
  stack->top = nodeBaru;
  stack->count++;
  printf("Pushed %d onto the stack", value);
  getch();
}

void popStack(stack *stack)
{
  if (stack->top == NULL)
  {
    printf("Stack Underflow");
    getch();
    return;
  }
  node *temp = stack->top;
  stack->top = stack->top->next;
  int poppedValue = temp->data;
  free(temp);
  stack->count--;
  printf("Popped %d from the stack", poppedValue);
  getch();
}

void stackTop(stack *stack)
{
  if (stack->top == NULL)
  {
    printf("Stack is empty");
  }
  else
  {
    printf("Top element is %d", stack->top->data);
  }
  getch();
}

int isEmpty(stack *stack)
{
  return stack->top == NULL;
}

int isFull(stack *stack)
{
  return stack->count == stack->maxKapasitas;
}

void stackCount(stack *stack)
{
  printf("Stack count is %d", stack->count);
  getch();
}
void destroyStack(stack *stack)
{
  struct node *current = stack->top;
  while (current != NULL)
  {
    struct node *temp = current;
    current = current->next;
    free(temp);
  }
  stack->top = NULL;
  stack->count = 0;
  printf("Stack has been destroyed");
  getch();
}

void viewStack(stack *stack)
{
  if (isEmpty(stack))
  {
    printf("Stack is empty");
    getch();
    return;
  }
  node *current = stack->top;
  printf("Stack (Top to Bottom):\n");
  while (current != NULL)
  {
    printf("%d\n|\n", current->data);
    current = current->next;
  }
  printf("--");
  getch();
}

int main()
{
  int kapasitas, pilihan, value;

  system("cls");
  printf("Masukan Kapasitas Stack: ");
  scanf("%d", &kapasitas);

  stack *stack = buatStack(kapasitas);
  do
  {
    system("cls");
    printf("Menu (Dengan Kapasitas %d):\n1. Push Stack\n2. Pop Stack\n3. Stack Top\n4. Empty Stack\n5. Full Stack\n6. Stack Count\n7. Destroy Stack\n8. View Stack\n9. Keluar\nMasukan Pilihan: ", kapasitas);
    scanf("%d", &pilihan);
    printf("--------------------------------------------------------------------\n");
    switch (pilihan)
    {
    case 1:
      printf("Masukan Value data: ");
      scanf("%d", &value);
      pushStack(stack, value);
      break;
    case 2:
      popStack(stack);
      break;
    case 3:
      stackTop(stack);
      break;
    case 4:
      if (isEmpty(stack))
      {
        printf("Stack is empty");
      }
      else
      {
        printf("Stack is not empty");
      }
      getch();
      break;
    case 5:
      if (isFull(stack))
      {
        printf("Stack is full");
      }
      else
      {
        printf("Stack is not full");
      }
      getch();
      break;
    case 6:
      stackCount(stack);
      break;
    case 7:
      destroyStack(stack);
      break;
    case 8:
      viewStack(stack);
      break;
    case 9:
      break;
    default:
      printf("Pilihan yang anda masukkan salah!");
      getch();
      break;
    }
  } while (pilihan != 9);

  printf("End Program");
  printf("\n--------------------------------------------------------------------\n");
  return 0;
}