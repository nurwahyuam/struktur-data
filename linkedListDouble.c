#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

//========================================================
struct node {
  int data;
  struct node *prev;
  struct node *next;
};

typedef struct node node;

void addFirst(node **head);
void addInBetween(node **head);
void addLast(node **head);
void deleteFirst(node **head);
void deleteInBetween(node **head);
void deleteLast(node **head);
void searchData(node **head);
void viewAmountData(node **head);
void viewTotalData(node **head);
void traverse(node *head);

//========================================================
int main(){
  node *head;
  char pilih;
  head = NULL;
  do
  {
    system("cls");
    printf("========================================================\n");
    printf("Masukkan Pilihan\n");
    printf("========================================================\n");
    printf("1. Tambah data di awal\n");
    printf("2. Tambah data di tengah list\n");
    printf("3. Tambah data di akhir\n");
    printf("4. Hapus data di awal\n");
    printf("5. Hapus data di tengah list\n");
    printf("6. Hapus data di akhir\n");
    printf("7. Cari data list\n");
    printf("8. Cetak jumlah data\n");
    printf("9. Cetak total jumlah data\n");
    printf("0. Cetak isi list\n");
    printf("========================================================\n");
    printf("Masukan Pilihan (tekan q untuk keluar) : ");
    fflush(stdin);
    scanf("%c", &pilih);
    if (pilih == '1')
      addFirst(&head);
    else if (pilih == '2')
      addInBetween(&head);
    else if (pilih == '3')
      addLast(&head);
    else if (pilih == '4')
      deleteFirst(&head);
    else if (pilih == '5')
      deleteInBetween(&head);
    else if (pilih == '6')
      deleteLast(&head);
    else if (pilih == '7')
      searchData(&head);
    else if (pilih == '8')
      viewAmountData(&head);
    else if (pilih == '9')
      viewTotalData(&head);
    else if (pilih == '0')
    {
      traverse(head);
      getch();
    }
  } while (pilih != 'q');
  return 0;
}

//========================================================
void addFirst(node **head)
{
  int bil;
  node *pNew;
  system("cls");
  printf("masukkan bilangan : ");
  fflush(stdin);
  scanf("%d", &bil);
  pNew = (node *)malloc(sizeof(node));
  if (pNew != NULL)
  {
    pNew->data = bil;
    pNew->prev = NULL;
    pNew->next = *head;

    if (*head != NULL)
      (*head)->prev = pNew;

    *head = pNew;
  }
  else
  {
    printf("Alokasi memori gagal");
    getch();
  }
}

//========================================================
void addInBetween(node **head)
{
  int pos, bil;
  node *pNew, *pCur;
  system("cls");
  traverse(*head);
  printf("\nposisi penyisipan setelah data bernilai : ");
  fflush(stdin);
  scanf("%d", &pos);
  printf("\nbilangan : ");
  fflush(stdin);
  scanf("%d", &bil);
  pCur = *head;

  while (pCur != NULL && pCur->data != pos){
    pCur = pCur->next;
  }

  pNew = (node *)malloc(sizeof(node));
  if (pCur == NULL){
    printf("\nnode tidak ditemukan");
    getch();
  } else if (pNew == NULL){
    printf("\nalokasi memori gagal");
    getch();
  } else {
    pNew->data = bil;
    pNew->next = pCur->next;
    pNew->prev = pCur;

    if (pCur->next != NULL)
      pCur->next->prev = pNew;

    pCur->next = pNew;
  }
}

//========================================================
void addLast(node **head){
  int bil;
  node *pNew, *pCur;
  system("cls");
  printf("masukkan bilangan : ");
  scanf("%d", &bil);
  pNew = (node *)malloc(sizeof(node));

  if (pNew != NULL){
    pNew->data = bil;
    pNew->next = NULL;
    if (*head == NULL){
      pNew->prev = NULL;
      *head = pNew;
    } else {
      pCur = *head;
      while (pCur->next != NULL) {
        pCur = pCur->next;
      }
      pCur->next = pNew;
      pNew->prev = pCur;
    }
  } else {
    printf("Alokasi memori gagal");
    getch();
  }
}

//========================================================
void deleteFirst(node **head){
  node *pTemp;
  if (*head != NULL){
    pTemp = *head;
    *head = (*head)->next;

    if (*head != NULL)
      (*head)->prev = NULL;

    free(pTemp);
    system("cls");
    printf("Data Awal telah dihapus di dalam linked list.");
    getch();
  } else {
    system("cls");
    printf("Linked list kosong, tidak ada data yang bisa dihapus.");
    getch();
  }
}

//========================================================
void deleteInBetween(node **head){
  int target;
  node *pCur;
  if (*head == NULL){
    system("cls");
    printf("Linked list kosong, tidak ada data yang bisa dihapus.");
    getch();
    return;
  }

  system("cls");
  traverse(*head);
  printf("\n\nMasukan Data yang akan dihapus bernilai : ");
  scanf("%d", &target);
  pCur = *head;

  while (pCur != NULL && pCur->data != target){
    pCur = pCur->next;
  }

  if (pCur != NULL){
    if (pCur->prev != NULL)
      pCur->prev->next = pCur->next;
    else
      *head = pCur->next;

    if (pCur->next != NULL)
      pCur->next->prev = pCur->prev;

    free(pCur);
    system("cls");
    printf("Data %d telah dihapus di dalam linked list.", target);
    getch();
  } else {
    system("cls");
    printf("Data %d tidak ditemukan di dalam linked list.", target);
    getch();
  }
}

//========================================================
void deleteLast(node **head){
  node *pCur;
  if (*head == NULL){
    system("cls");
    printf("Linked list kosong, tidak ada data yang bisa dihapus.");
    getch();
    return;
  }
  pCur = *head;
  while (pCur->next != NULL){
    pCur = pCur->next;
  }
  if (pCur->prev != NULL)
    pCur->prev->next = NULL;
  else
    *head = NULL;

  free(pCur);
  system("cls");
  printf("Data Akhir telah dihapus di dalam linked list.");
  getch();
}

//========================================================
void searchData(node **head){
  int target, found = 0;
  node *pCur;
  system("cls");
  printf("Masukkan nilai data yang akan dicari: ");
  scanf("%d", &target);
  pCur = *head;
  while (pCur != NULL){
    if (pCur->data == target){
      system("cls");
      printf("Data %d ditemukan di dalam linked list.", target);
      found = 1;
      getch();
      break;
    }
    pCur = pCur->next;
  }
  if (!found){
    system("cls");
    printf("Data %d tidak ditemukan di dalam linked list.", target);
    getch();
  }
}

//========================================================
void viewAmountData(node **head){
  int bil = 0;
  node *pCur;
  pCur = *head;
  while (pCur != NULL){
    bil++;
    pCur = pCur->next;
  }
  system("cls");
  printf("Total data di dalam linked list adalah %d", bil);
  getch();
}

//========================================================
void viewTotalData(node **head){
  int bil = 0;
  node *pCur;
  pCur = *head;
  while (pCur != NULL){
    bil += pCur->data;
    pCur = pCur->next;
  }
  system("cls");
  printf("Total data di dalam linked list jika di jumlah adalah %d", bil);
  getch();
}

//========================================================
void traverse(node *head)
{
  node *pWalker;
  system("cls");
  pWalker = head;
  while (pWalker != NULL){
    printf("%d\t", pWalker->data);
    pWalker = pWalker->next;
    printf(" <-> ");
  }
  printf("NULL");
}
