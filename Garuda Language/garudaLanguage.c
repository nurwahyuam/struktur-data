#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX 200

struct node {
  char data;
  struct node *next;
};

struct stack {
  int count;
  int maxKapasitas;
  struct node *top;
};

typedef struct stack Stack;
typedef struct node Node;

void initStack(Stack *s, int kapasitas){
  s->count = 0;
  s->maxKapasitas = kapasitas;
  s->top = NULL;
}

bool isEmpty(Stack *s){
  return s->count == 0;
}

bool push(Stack *s, char value){
  if (s->count >= s->maxKapasitas){
    printf("Stack Penuh!\n");
    return false;
  }

  Node *nodeBaru = (Node*) malloc(sizeof(Node));
  if (nodeBaru == NULL){
    printf("Alokasi memori gagal!\n");
    return false;
  }

  nodeBaru->data = value;
  nodeBaru->next = s->top;
  s->top = nodeBaru;
  s->count++;
  return true;
}

char pop(Stack *s){
  if (isEmpty(s)){
    printf("Stack Kosong!\n");
    return '\0';
  }

  Node *temp = s->top;
  char data = temp->data;
  s->top = temp->next;
  free(temp);
  s->count--;
  return data;
}

bool isMatchingPair(char open, char close) {
  return (open == '(' && close == ')') ||
         (open == '{' && close == '}') ||
         (open == '[' && close == ']') ||
         (open == '<' && close == '>');
}

bool isBalanced(char *exp){
  Stack s;
  initStack(&s, MAX);

  for (int i = 0; i < strlen(exp); i++){
    char current = exp[i];
    
    if (current == '(' || current == '{' || current == '[' || current == '<') {
      push(&s, current);
    } else if (current == ')' || current == '}' || current == ']' || current == '>') {
      if (isEmpty(&s) || !isMatchingPair(pop(&s), current)){
        return false;
      }
    }
  }
  return isEmpty(&s);
}

int main(){
  char expression[MAX];

  system("cls");
  printf("Masukan Ekspresi: ");
  fgets(expression, sizeof(expression), stdin);
  expression[strcspn(expression, "\n")] = '\0';

  

  if (isBalanced(expression)){
    printf("Kode Valid\n");
  } else {
    printf("Kode Tidak Valid\n");
  }
  system("pause");

  return 0;
}
