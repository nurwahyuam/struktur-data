#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#define MAX_PESERTA 10

typedef struct Peserta
{
    char nama[50];
    char jenis_kelamin;
    struct Peserta *next;
} Peserta;

Peserta *headL = NULL;
Peserta *headP = NULL;
Peserta *headALL = NULL;
int countL = 0, countP = 0, countALL = 0;

Peserta *buatPeserta(char *nama, char jenis_kelamin)
{
    Peserta *baru = (Peserta *)malloc(sizeof(Peserta));
    strcpy(baru->nama, nama);
    baru->jenis_kelamin = jenis_kelamin;
    baru->next = baru;
    return baru;
}

void tambahPeserta(Peserta **head, char *nama, char jenis_kelamin, int *count)
{
    if (*count >= MAX_PESERTA)
    {
        printf("Lingkaran %s penuh!\n", jenis_kelamin == 'L' ? "mahasiswa" : "mahasiswi");
        return;
    }

    Peserta *baru = buatPeserta(nama, jenis_kelamin);
    if (*head == NULL)
    {
        *head = baru;
    }
    else
    {
        Peserta *temp = *head;
        while (temp->next != *head)
        {
            temp = temp->next;
        }
        temp->next = baru;
        baru->next = *head;
    }
    (*count)++;
    printf("%s berhasil ditambahkan ke lingkaran %s.\n", nama, jenis_kelamin == 'L' ? "mahasiswa" : "mahasiswi");
    getch();
}

void hapusPeserta(Peserta **head, char *nama, int *count)
{
    if (*head == NULL)
    {
        printf("Lingkaran kosong!\n");
        return;
    }

    Peserta *curr = *head;
    Peserta *prev = NULL;

    do
    {
        if (strcmp(curr->nama, nama) == 0)
        {
            if (curr == *head)
            {
                Peserta *temp = *head;
                while (temp->next != *head)
                {
                    temp = temp->next;
                }
                *head = curr->next;
                temp->next = *head;
                if (curr == curr->next)
                {
                    *head = NULL;
                }
            }
            else
            {
                prev->next = curr->next;
            }
            free(curr);
            (*count)--;
            printf("%s telah keluar dari lingkaran.\n", nama);
            return;
        }
        prev = curr;
        curr = curr->next;
    } while (curr != *head);

    printf("Peserta dengan nama %s tidak ditemukan.\n", nama);
}

void tampilkanLingkaran(Peserta *head)
{
    if (head == NULL)
    {
        printf("Lingkaran kosong!\n");
        return;
    }

    Peserta *temp = head;
    do
    {
        printf("%s (%c) -> ", temp->nama, temp->jenis_kelamin);
        temp = temp->next;
    } while (temp != head);
    printf("(kembali ke %s)\n", head->nama);
}

int main()
{
    int pilihan;
    char nama[50];
    char jenis_kelamin;

    do
    {
        system("cls");
        printf("Menu:\n");
        printf("1. Tambah Peserta\n");
        printf("2. Hapus Peserta\n");
        printf("3. Tampilkan Lingkaran Mahasiswa\n");
        printf("4. Tampilkan Lingkaran Mahasiswi\n");
        printf("5. Tampilkan Lingkaran Semua Mahasiswa dan Mahasiswi\n");
        printf("6. Keluar\n");
        printf("Pilihan Anda: ");
        scanf("%d", &pilihan);

        switch (pilihan)
        {
        case 1:
            system("cls");
            tambahPeserta(&headL, "Irsyad", 'L', &countL);
            tambahPeserta(&headL, "Budi", 'L', &countL);
            tambahPeserta(&headL, "Andi", 'L', &countL);
            tambahPeserta(&headL, "Dika", 'L', &countL);

            tambahPeserta(&headP, "Cindy", 'P', &countP);
            tambahPeserta(&headP, "Siti", 'P', &countP);
            tambahPeserta(&headP, "Ayu", 'P', &countP);
            tambahPeserta(&headP, "Maya", 'P', &countP);
            tambahPeserta(&headP, "Lia", 'P', &countP);

            tambahPeserta(&headALL, "Irsyad", 'L', &countALL);
            tambahPeserta(&headALL, "Arsyad", 'L', &countALL);
            tambahPeserta(&headALL, "Budi", 'L', &countALL);
            tambahPeserta(&headALL, "Andi", 'L', &countALL);
            tambahPeserta(&headALL, "Dika", 'L', &countALL);
            tambahPeserta(&headALL, "Cindy", 'P', &countALL);
            tambahPeserta(&headALL, "Siti", 'P', &countALL);
            tambahPeserta(&headALL, "Ayu", 'P', &countALL);
            tambahPeserta(&headALL, "Maya", 'P', &countALL);
            tambahPeserta(&headALL, "Lia", 'P', &countALL);
        case 2:
            system("cls");
            printf("Masukkan nama yang ingin dihapus: ");
            scanf("%s", nama);

            hapusPeserta(&headL, nama, &countL);
            hapusPeserta(&headP, nama, &countP);
            break;

        case 3:
            system("cls");
            printf("Lingkaran Mahasiswa:\n");
            tampilkanLingkaran(headL);
            break;

        case 4:
            system("cls");
            printf("Lingkaran Mahasiswi:\n");
            tampilkanLingkaran(headP);
            break;

        case 5:
            system("cls");
            printf("Lingkaran Semua Mahasiswa dan Mahasiswi:\n");
            tampilkanLingkaran(headALL);
            break;

        case 6:
            system("cls");
            printf("Keluar dari program.\n");
            getch();
            break;

        default:
            system("cls");
            printf("Pilihan tidak valid!\n");
            getch();
        }
    } while (pilihan != 6);

    return 0;
}
