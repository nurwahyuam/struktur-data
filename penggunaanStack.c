#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 100

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

void initStack(Stack *s, int kapasitas) {
    s->count = 0;
    s->maxKapasitas = kapasitas;
    s->top = NULL;
}

bool isEmpty(Stack *s) {
    return s->count == 0;
}

bool push(Stack *s, char value) {
    if (s->count >= s->maxKapasitas) {
        printf("Stack Penuh!\n");
        return false;
    }

    Node *nodeBaru = (Node*) malloc(sizeof(Node));
    if (nodeBaru == NULL) {
        printf("Alokasi memori gagal!\n");
        return false;
    }

    nodeBaru->data = value;
    nodeBaru->next = s->top;
    s->top = nodeBaru;
    s->count++;
    return true;
}

char pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack Kosong!\n");
        return '\0';
    }

    Node *temp = s->top;
    char data = temp->data;
    s->top = s->top->next;
    free(temp);
    s->count--;
    return data;
}

bool isMatchingPair(char open, char close) {
    return (open == '(' && close == ')');
}

bool isBalanced(char *expression) {
    Stack s;
    initStack(&s, MAX);

    for (int i = 0; i < strlen(expression); i++) {
        char current = expression[i];

        if (current == '(') {
            push(&s, current);
        } else if (current == ')') {
            if (isEmpty(&s) || !isMatchingPair(pop(&s), current)) {
                return false;
            }
        }
    }

    return isEmpty(&s);
}

char peek(Stack *s){
  if (isEmpty(s)) {
    printf("Stack Kosong!\n");
    return '\0';
  }
  return s->top->data;
}

int precedence(char operand){
  if (operand == '+'|| operand == '-') return 1;
  if ( operand == '*' || operand == '/') return 2;
  return 0;
}

void infixToPostfix(char *infix, char *postfix){
  Stack s;
  initStack(&s, MAX);
  int j = 0;

  for (int i = 0; i < strlen(infix); i++){
    char token = infix[i];

    if (isalnum(token)){
      postfix[j++] = token;
    } else {
      while (!isEmpty(&s) && precedence(peek(&s)) >= precedence(token)) {
        postfix[j++] = pop(&s);
      }
      push(&s, token);
    }
  }

  while (!isEmpty(&s)){
    postfix[j++] = pop(&s);
  }
  postfix[j] = '\0';
}

void infixToPostfixExpression(char *infix, char *postfix){
  Stack s;
  initStack(&s, MAX);
  int j = 0;

  for (int i = 0; i < strlen(infix); i++){
    char token = infix[i];

    if (isalnum(token)){
      postfix[j++] = token;
    } else if (token == '(') {
      push(&s, token);
    } else if (token == ')') {
      while (!isEmpty(&s) && peek(&s) != '(') {
        postfix[j++] = pop(&s);
      }
      pop(&s);
    } else {
      while (!isEmpty(&s) && precedence(peek(&s)) >= precedence(token)) {
        postfix[j++] = pop(&s);
      }
      push(&s, token);
    }
  }

  while (!isEmpty(&s)){
    postfix[j++] = pop(&s);
  }
  postfix[j] = '\0';
}

int evaluasiPostfix(char *postfix){
  Stack s;
  initStack(&s, MAX);

  for (int i = 0; i < strlen(postfix); i++){
    char token = postfix[i];

    if (isdigit(token)){
      push(&s, token - '0');
    } else {
      int operand2 = pop(&s);
      int operand1 = pop(&s);
      
      switch (token){
        case '+': push(&s, operand1 + operand2); break;
        case '-': push(&s, operand1 - operand2); break;
        case '*': push(&s, operand1 * operand2); break;
        case '/': push(&s, operand1 / operand2); break;
      }
    }
  }
  return pop(&s);
}

int main() {
    int pilihan;
    char expression[MAX];
    char postfix[MAX];

    do {
        system("cls");
        printf("Pilih menu:\n1. Matching Balancing Parenthesis\n2. Infix ke Postfix dan Evaluasi\n3. Infix ke Postfix Expressions dan Evaluasi\n4. Keluar\nMasukan Pilihan: ");
        
        scanf("%d", &pilihan);
        getchar();

        switch (pilihan) {
        case 1:
            system("cls");
            printf("Masukkan ekspresi: ");
            fgets(expression, sizeof(expression), stdin);
            expression[strcspn(expression, "\n")] = '\0';

            if (isBalanced(expression)) {
                printf("Tanda Kurung Seimbang\n");
            } else {
                printf("Tanda Kurung Tidak Seimbang\n");
            }
            system("pause");
            break;
        case 2:
          system("cls");
          printf("Masukkan infix: ");
          fgets(expression, sizeof(expression), stdin);
          expression[strcspn(expression, "\n")] = '\0';

          infixToPostfix(expression, postfix);
          printf("Hasil postfix: %s\n", postfix);

          int hasil = evaluasiPostfix(postfix);
          printf("Hasil Evaluasi: %d\n", hasil);
          system("pause");
          break;
        case 3:
          system("cls");
          printf("Masukkan ekspresi infix: ");
          fgets(expression, sizeof(expression), stdin);
          expression[strcspn(expression, "\n")] = '\0';

          infixToPostfixExpression(expression, postfix);
          printf("Hasil Ekspresi postfix: %s\n", postfix);

          int hasilExpression = evaluasiPostfix(postfix);
          printf("Hasil Evaluasi: %d\n", hasilExpression);
          system("pause");
          break;
        case 4:
            system("cls");
            printf("Keluar Program\n");
            break;
        default:
            system("cls");
            printf("Pilihan anda kurang tepat\n");
            system("pause");
            break;
        }
    } while (pilihan != 4);

    return 0;
}
