#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100
#define MAX_TITLE 100

// Structure to store book details
typedef struct {
    int id;
    char title[MAX_TITLE];
    int isIssued; // 0 = available, 1 = issued
} Book;

Book library[MAX_BOOKS];
int bookCount = 0;

void loadBooksFromFile() {
    FILE *file = fopen("books.dat", "rb");
    if (file) {
        fread(&bookCount, sizeof(int), 1, file);
        fread(library, sizeof(Book), bookCount, file);
        fclose(file);
    }
}

void saveBooksToFile() {
    FILE *file = fopen("books.dat", "wb");
    if (file) {
        fwrite(&bookCount, sizeof(int), 1, file);
        fwrite(library, sizeof(Book), bookCount, file);
        fclose(file);
    }
}

void addBook() {
    if (bookCount >= MAX_BOOKS) {
        printf("Library is full. Cannot add more books.\n");
        return;
    }

    printf("Enter Book ID: ");
    scanf("%d", &library[bookCount].id);

    printf("Enter Book Title: ");
    getchar(); // To clear newline from input buffer
    fgets(library[bookCount].title, MAX_TITLE, stdin);
    library[bookCount].title[strcspn(library[bookCount].title, "\n")] = 0; // Remove newline

    library[bookCount].isIssued = 0; // Initially, the book is not issued

    bookCount++;
    saveBooksToFile();

    printf("Book added successfully.\n");
}

void deleteBook() {
    int id, i, found = 0;
    printf("Enter Book ID to delete: ");
    scanf("%d", &id);

    for (i = 0; i < bookCount; i++) {
        if (library[i].id == id) {
            found = 1;
            for (int j = i; j < bookCount - 1; j++) {
                library[j] = library[j + 1];
            }
            bookCount--;
            saveBooksToFile();
            printf("Book deleted successfully.\n");
            break;
        }
    }

    if (!found) {
        printf("Book not found.\n");
    }
}

void issueBook() {
    int id, i, found = 0;
    printf("Enter Book ID to issue: ");
    scanf("%d", &id);

    for (i = 0; i < bookCount; i++) {
        if (library[i].id == id) {
            found = 1;
            if (library[i].isIssued) {
                printf("Book is already issued.\n");
            } else {
                library[i].isIssued = 1;
                saveBooksToFile();
                printf("Book issued successfully.\n");
            }
            break;
        }
    }

    if (!found) {
        printf("Book not found.\n");
    }
}

void returnBook() {
    int id, i, found = 0;
    printf("Enter Book ID to return: ");
    scanf("%d", &id);

    for (i = 0; i < bookCount; i++) {
        if (library[i].id == id) {
            found = 1;
            if (!library[i].isIssued) {
                printf("Book is not issued.\n");
            } else {
                library[i].isIssued = 0;
                saveBooksToFile();
                printf("Book returned successfully.\n");
            }
            break;
        }
    }

    if (!found) {
        printf("Book not found.\n");
    }
}

void listBooks() {
    printf("\n%-10s %-30s %-10s\n", "Book ID", "Title", "Status");
    printf("----------------------------------------------------------\n");
    for (int i = 0; i < bookCount; i++) {
        printf("%-10d %-30s %-10s\n", library[i].id, library[i].title, library[i].isIssued ? "Issued" : "Available");
    }
    printf("\n");
}

int main() {
    int choice;

    loadBooksFromFile();

    do {
        printf("\nLibrary Management System\n");
        printf("1. Add Book\n");
        printf("2. Delete Book\n");
        printf("3. Issue Book\n");
        printf("4. Return Book\n");
        printf("5. List Books\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                deleteBook();
                break;
            case 3:
                issueBook();
                break;
            case 4:
                returnBook();
                break;
            case 5:
                listBooks();
                break;
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}
