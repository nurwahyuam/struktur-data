#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

//========================================================
struct node {
  int data;
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
int main() {
  node *head = NULL;
  char pilih;
  
  do {
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
    else if (pilih == '0') {
      traverse(head);
      getch();
    }
  } while (pilih != 'q');
  
  return 0;
}

//========================================================
void addFirst(node **head) {
  int bil;
  node *pNew = (node *)malloc(sizeof(node));
  system("cls");
  fflush(stdin);
  printf("masukkan bilangan : ");
  scanf("%d", &bil);
  
  if (pNew != NULL) {
    pNew->data = bil;
    if (*head == NULL) {
      // If list is empty, point the new node to itself
      pNew->next = pNew;
      *head = pNew;
    } else {
      // Insert before the first node and make it head
      node *pCur = *head;
      while (pCur->next != *head) {
        pCur = pCur->next;
      }
      pNew->next = *head;
      pCur->next = pNew;
      *head = pNew;
    }
  } else {
    printf("Alokasi memori gagal");
    getch();
  }
}

//========================================================
void addInBetween(node **head) {
  if (*head == NULL) {
    printf("List kosong. Tidak bisa menambahkan data di tengah.");
    getch();
    return;
  }
  
  int pos, bil;
  node *pNew, *pCur = *head;
  system("cls");
  traverse(*head);
  printf("\nposisi penyisipan setelah data bernilai : ");
  fflush(stdin);
  scanf("%d", &pos);
  printf("\nbilangan : ");
  scanf("%d", &bil);

  while (pCur->data != pos && pCur->next != *head) {
    pCur = pCur->next;
  }
  if (pCur->data != pos) {
    printf("Posisi tidak ditemukan.\n");
    getch();
    return;
  }

  pNew = (node *)malloc(sizeof(node));
  if (pNew == NULL) {
    printf("Alokasi memori gagal\n");
    getch();
    return;
  }

  pNew->data = bil;
  pNew->next = pCur->next;
  pCur->next = pNew;
}

//========================================================
void addLast(node **head) {
  int bil;
  node *pNew = (node *)malloc(sizeof(node));
  system("cls");
  printf("masukkan bilangan : ");
  scanf("%d", &bil);

  if (pNew != NULL) {
    pNew->data = bil;
    if (*head == NULL) {
      // Jika list kosong, node baru menjadi head dan menunjuk ke dirinya sendiri
      pNew->next = pNew;
      *head = pNew;
    } else {
      node *pCur = *head;
      while (pCur->next != *head) {
        pCur = pCur->next;
      }
      pCur->next = pNew;
      pNew->next = *head;
    }
  } else {
    printf("Alokasi memori gagal");
    getch();
  }
}

//========================================================
void deleteFirst(node **head) {
  if (*head == NULL) {
    system("cls");
    printf("List kosong, tidak ada data yang bisa dihapus.");
    getch();
    return;
  }
  
  node *pCur = *head;
  if (pCur->next == *head) {
    // Only one node in the list
    free(pCur);
    *head = NULL;
  } else {
    while (pCur->next != *head) {
      pCur = pCur->next;
    }
    node *pTemp = *head;
    *head = (*head)->next;
    pCur->next = *head;
    free(pTemp);
  }

  system("cls");
  printf("Data Awal telah dihapus.");
  getch();
}

//========================================================
void deleteInBetween(node **head) {
  if (*head == NULL) {
    system("cls");
    printf("List kosong, tidak ada data yang bisa dihapus.");
    getch();
    return;
  }

  int target;
  node *pCur = *head, *pPrev = NULL;
  system("cls");
  traverse(*head);
  printf("\n\nMasukan Data yang akan dihapus bernilai : ");
  scanf("%d", &target);

  do {
    if (pCur->data == target) {
      if (pPrev != NULL) {
        pPrev->next = pCur->next;
      } else {
        // Hapus head
        node *last = *head;
        while (last->next != *head) {
          last = last->next;
        }
        last->next = pCur->next;
        *head = pCur->next;
      }
      free(pCur);
      system("cls");
      printf("Data %d telah dihapus.", target);
      getch();
      return;
    }
    pPrev = pCur;
    pCur = pCur->next;
  } while (pCur != *head);

  printf("Data %d tidak ditemukan.", target);
  getch();
}

//========================================================
void deleteLast(node **head) {
  if (*head == NULL) {
    system("cls");
    printf("List kosong, tidak ada data yang bisa dihapus.");
    getch();
    return;
  }

  node *pCur = *head, *pPrev = NULL;
  if (pCur->next == *head) {
    // Only one node in the list
    free(pCur);
    *head = NULL;
  } else {
    while (pCur->next != *head) {
      pPrev = pCur;
      pCur = pCur->next;
    }
    pPrev->next = *head;
    free(pCur);
  }

  system("cls");
  printf("Data Akhir telah dihapus.");
  getch();
}

//========================================================
void searchData(node **head) {
  if (*head == NULL) {
    system("cls");
    printf("List kosong, tidak ada data.");
    getch();
    return;
  }

  int target;
  node *pCur = *head;
  system("cls");
  printf("Masukkan nilai data yang akan dicari: ");
  scanf("%d", &target);

  do {
    if (pCur->data == target) {
      system("cls");
      printf("Data %d ditemukan di dalam linked list.", target);
      getch();
      return;
    }
    pCur = pCur->next;
  } while (pCur != *head);

  system("cls");
  printf("Data %d tidak ditemukan.", target);
  getch();
}

//========================================================
void viewAmountData(node **head) {
  if (*head == NULL) {
    system("cls");
    printf("List kosong.");
    getch();
    return;
  }

  int bil = 0;
  node *pCur = *head;
  do {
    bil++;
    pCur = pCur->next;
  } while (pCur != *head);

  system("cls");
  printf("Total data di dalam linked list adalah %d", bil);
  getch();
}

//========================================================
void viewTotalData(node **head) {
  if (*head == NULL) {
    system("cls");
    printf("List kosong.");
    getch();
    return;
  }

  int total = 0;
  node *pCur = *head;
  do {
    total += pCur->data;
    pCur = pCur->next;
  } while (pCur != *head);

  system("cls");
  printf("Total jumlah data adalah %d", total);
  getch();
}

//========================================================
void traverse(node *head) {
  if (head == NULL) {
    printf("List kosong.");
    return;
  }

  node *pCur = head;
  system("cls");
  printf("Isi linked list:\n");
  do {
    printf("%d -> ", pCur->data);
    pCur = pCur->next;
  } while (pCur != head);
  printf("%d (kembali ke awal)", head->data);
}
//========================================================
