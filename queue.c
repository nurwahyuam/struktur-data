#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

struct node {
  int data;
  struct node *next;
};

struct queue {
  int count;
  int maxKapasitas;
  struct node *front;
  struct node *rear;
};

typedef struct node node;
typedef struct queue queue;

queue *buatQueue(int kapasitas){
  queue *q = (queue *)malloc(sizeof(queue));
  q->count = 0;
  q->maxKapasitas = kapasitas;
  q->front = NULL;
  q->rear = NULL;
  return q;
};

void enqueue(queue *q, int value){
  if (q->count == q->maxKapasitas){
    printf("Queue Penuh!");
    getch();
    return;
  }
  node *nodeBaru = (node *)malloc(sizeof(node));
  if (nodeBaru == NULL){
    printf("Queue Overflow");
    getch();
    return;
  }
  nodeBaru->data = value;
  nodeBaru->next = NULL;

  if (q->rear == NULL){
    q->front = nodeBaru;
    q->rear = nodeBaru;
  } else {
    q->rear->next = nodeBaru;
    q->rear = nodeBaru;
  }
  q->count++;
  printf("Data %d berhasil ditambahkan ke Queue", value);
  getch();
};

void dequeue(queue *q){
  if (q->front == NULL){
    printf("Queue Kosong!");
    getch();
    return;
  }
  node *temp = q->front;
  q->front = q->front->next;
  if (q->front == NULL){
    q->rear = NULL;
  }
  int dequeuedValue = temp->data;
  free(temp);
  q->count--;
  printf("Data %d berhasil dikeluarkan dari Queue", dequeuedValue);
  getch();
}

int isEmpty(queue *q){
  return q->front == NULL;
}

int isFull(queue *q){
  return q->count == q->maxKapasitas;
}

void clearQueue(queue *q){
  node *current = q->front;
  while (current != NULL){
    node *temp = current;
    current = current->next;
    free(temp);
  }
  q->front = NULL;
  q->rear = NULL;
  q->count = 0;
  printf("Queue berhasil dikosongkan!");
  getch();
}

void tampilQueue(queue *q){
  if (isEmpty(q)){
    printf("Queue Kosong!");
    getch();
    return;
  }
  node *current = q->front;
  printf("Queue (Front to Rear):\n");
  while (current != NULL){
    printf("%d <- ", current->data);
    current = current->next;
  }
  printf("NULL");
  getch();
}

int main(){
  int kapasitas, pilihan, value;

  system("cls");
  printf("Masukan Kapasitas Queue: ");
  scanf("%d", &kapasitas);

  queue *q = buatQueue(kapasitas);

  do {
    system("cls");
    printf("Menu (Dengan Kapasitas %d):\n1. Enqueue\n2. Dequeue\n3. isEmpty\n4. isFull\n5. Clear Queue\n6. Tampil Queue\n7. Keluar\nMasukan Pilihan: ", kapasitas);
    scanf("%d", &pilihan);
    printf("--------------------------------------------------------------------\n");
    switch (pilihan) {
      case 1:
        printf("Masukan Value Data: ");
        scanf("%d", &value);
        enqueue(q, value);
        break;
      case 2:
        dequeue(q);
        break;
      case 3:
        if (isEmpty(q)){
          printf("Queue Kosong!");
        } else {
          printf("Queue Tidak Kosong!");
        }
        getch();
        break;
      case 4:
        if (isFull(q)){
          printf("Queue Penuh!");
        } else {
          printf("Queue Tidak Penuh!");
        }
        getch();
        break;
      case 5:
        clearQueue(q);
        break;
      case 6:
        tampilQueue(q);
        break;
      case 7:
        break;
      default:
        printf("Pilihan yang ada masukkan salah!");
        getch();
        break;
    }
  } while (pilihan != 7);

  printf("End Program");
  printf("\n--------------------------------------------------------------------\n");
  return 0;
}
