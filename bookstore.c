
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Structure for a book
typedef struct Book {
    char isbn[14]; // ISBN number (13 digits + null terminator)
    char title[100];
    char author[100];
    char genre[50];
    double price;
    struct Book *left;
    struct Book *right;
} Book;

// Forward declaration of displayBook function
void displayBook(Book* book);

// Queue node
typedef struct QueueNode {
    Book* book;
    struct QueueNode* next;
} QueueNode;

// Queue structure
typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
} Queue;

// Function to create a new book node
Book* createBook(const char isbn[], const char title[], const char author[], const char genre[], double price) {
    Book* newBook = (Book*)malloc(sizeof(Book));
    strcpy(newBook->isbn, isbn);
    strcpy(newBook->title, title);
    strcpy(newBook->author, author);
    strcpy(newBook->genre, genre);
    newBook->price = price;
    newBook->left = NULL;
    newBook->right = NULL;
    return newBook;
}

// Function to create a new Queue node
QueueNode* createQueueNode(Book* book) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->book = book;
    newNode->next = NULL;
    return newNode;
}

// Function to create an empty Queue
Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = queue->rear = NULL;
    return queue;
}

// Function to check if the Queue is empty
bool isEmpty(Queue* queue) {
    return (queue->front == NULL);
}

// Function to enqueue a book into the Queue
void enqueue(Queue* queue, Book* book) {
    QueueNode* newNode = createQueueNode(book);
    if (isEmpty(queue)) {
        queue->front = queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

// Function to dequeue a book from the Queue
Book* dequeue(Queue* queue) {
    if (isEmpty(queue)) {
        return NULL;
    } else {
        QueueNode* temp = queue->front;
        Book* book = temp->book;
        queue->front = queue->front->next;
        if (queue->front == NULL) {
            queue->rear = NULL;
        }
        free(temp);
        return book;
    }
}

// Function to search for a book by ISBN using BFS
Book* searchBookBFSByISBN(Book* root, const char isbn[]) {
    if (root == NULL) return NULL;

    Queue* queue = createQueue();
    enqueue(queue, root);

    while (!isEmpty(queue)) {
        Book* current = dequeue(queue);
        if (strcmp(current->isbn, isbn) == 0) {
            return current;
        }
        if (current->left != NULL) {
            enqueue(queue, current->left);
        }
        if (current->right != NULL) {
            enqueue(queue, current->right);
        }
    }

    return NULL;
}

// Function to search for books by genre using BFS
void searchBooksBFSByGenre(Book* root, const char genre[]) {
    if (root == NULL) return;

    Queue* queue = createQueue();
    enqueue(queue, root);

    while (!isEmpty(queue)) {
        Book* current = dequeue(queue);
        if (strcmp(current->genre, genre) == 0) {
            printf("Book found!\n");
            displayBook(current);
            printf("\n");
        }
        if (current->left != NULL) {
            enqueue(queue, current->left);
        }
        if (current->right != NULL) {
            enqueue(queue, current->right);
        }
    }
}

// Function to search for books by author using BFS
void searchBooksBFSByAuthor(Book* root, const char author[]) {
    if (root == NULL) return;

    Queue* queue = createQueue();
    enqueue(queue, root);

    while (!isEmpty(queue)) {
        Book* current = dequeue(queue);
        if (strstr(current->author, author) != NULL) {
            printf("Book found!\n");
            displayBook(current);
            printf("\n");
        }
        if (current->left != NULL) {
            enqueue(queue, current->left);
        }
        if (current->right != NULL) {
            enqueue(queue, current->right);
        }
    }
}

// Function to search for books by title using BFS
void searchBooksBFSByTitle(Book* root, const char title[]) {
    if (root == NULL) return;

    Queue* queue = createQueue();
    enqueue(queue, root);

    while (!isEmpty(queue)) {
        Book* current = dequeue(queue);
        if (strstr(current->title, title) != NULL) {
            printf("Book found!\n");
            displayBook(current);
            printf("\n");
        }
        if (current->left != NULL) {
            enqueue(queue, current->left);
        }
        if (current->right != NULL) {
            enqueue(queue, current->right);
        }
    }
}

// Function to display information about a book
void displayBook(Book* book) {
    printf("ISBN: %s\n", book->isbn);
    printf("Title: %s\n", book->title);
    printf("Author: %s\n", book->author);
    printf("Genre: %s\n", book->genre);
    printf("Price: %.2f\n", book->price);
    printf("\n");
}

// Function to insert a book into the BST
Book* insertBook(Book* root, Book* newBook) {
    if (root == NULL)
        return newBook;

    if (strcmp(newBook->isbn, root->isbn) < 0)
        root->left = insertBook(root->left, newBook);
    else if (strcmp(newBook->isbn, root->isbn) > 0)
        root->right = insertBook(root->right, newBook);

    return root;
}

// Function to delete a node from the BST
Book* deleteBook(Book* root, char isbn[]) {
    if (root == NULL) 
        return root;

    if (strcmp(isbn, root->isbn) < 0)
        root->left = deleteBook(root->left, isbn);
    else if (strcmp(isbn, root->isbn) > 0)
        root->right = deleteBook(root->right, isbn);
    else {
        if (root->left == NULL) {
            Book* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Book* temp = root->left;
            free(root);
            return temp;
        }
        Book* temp = root->right;
        while

 (temp->left != NULL)
            temp = temp->left;
        strcpy(root->isbn, temp->isbn);
        strcpy(root->title, temp->title);
        strcpy(root->author, temp->author);
        strcpy(root->genre, temp->genre);
        root->price = temp->price;
        root->right = deleteBook(root->right, temp->isbn);
    }
    return root;
}

// Function to swap two books
void swap(Book** a, Book** b) {
    Book* temp = *a;
    *a = *b;
    *b = temp;
}

// Function to partition the array for quicksort
int partition(Book* books[], int low, int high) {
    char* pivot = books[high]->title;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (strcmp(books[j]->title, pivot) < 0) {
            i++;
            swap(&books[i], &books[j]);
        }
    }
    swap(&books[i + 1], &books[high]);
    return i + 1;
}

// Function to perform quicksort on an array of books by title
void quickSortByTitle(Book* books[], int low, int high) {
    if (low < high) {
        int pi = partition(books, low, high);

        quickSortByTitle(books, low, pi - 1);
        quickSortByTitle(books, pi + 1, high);
    }
}

int main() {
    Book* root = NULL;

    // Adding some pre-added books to the bookstore
    root = insertBook(root, createBook("9780131103627", "The C Programming Language", "Brian Kernighan, Dennis Ritchie", "Technical", 45.99));
    root = insertBook(root, createBook("9780321856715", "C Programming: A Modern Approach", "K. N. King", "Technical", 59.99));
    root = insertBook(root, createBook("9780201633610", "Design Patterns: Elements of Reusable Object-Oriented Software", "Erich Gamma, Richard Helm, Ralph Johnson, John Vlissides", "Technical", 54.99));
    root = insertBook(root, createBook("9781451673319", "To Kill a Mockingbird", "Harper Lee", "Fiction", 10.99));
    root = insertBook(root, createBook("9780141182605", "1984", "George Orwell", "Fiction", 9.99));
    root = insertBook(root, createBook("9780061120084", "The Catcher in the Rye", "J.D. Salinger", "Fiction", 11.99));
    root = insertBook(root, createBook("9780439023481", "The Hunger Games", "Suzanne Collins", "Fiction", 12.99));
    root = insertBook(root, createBook("9780547928227", "Harry Potter and the Sorcerer's Stone", "J.K. Rowling", "Fantasy", 14.99));
    root = insertBook(root, createBook("9780545010221", "The Hobbit", "J.R.R. Tolkien", "Fantasy", 13.99));
    root = insertBook(root, createBook("9780060256654", "Where the Wild Things Are", "Maurice Sendak", "Children's", 8.99));
    root = insertBook(root, createBook("9780394800134", "Green Eggs and Ham", "Dr. Seuss", "Children's", 7.99));
    root = insertBook(root, createBook("9780689870402", "The Very Hungry Caterpillar", "Eric Carle", "Children's", 6.99));
    root = insertBook(root, createBook("9780439554930", "Diary of a Wimpy Kid", "Jeff Kinney", "Children's", 10.99));

    int choice;
    char isbn[14], title[100], author[100], genre[50];
    double price;

    do {
        printf("\nBookstore Management System\n");
        printf("1. Add a Book\n");
        printf("2. Delete a Book\n");
        printf("3. Search for a Book\n");
        printf("4. Sort Books by Title\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter ISBN of the new book: ");
                scanf("%s", isbn);
                printf("Enter title of the new book: ");
                scanf(" %[^\n]s", title);
                printf("Enter author of the new book: ");
                scanf(" %[^\n]s", author);
                printf("Enter genre of the new book: ");
                scanf(" %[^\n]s", genre);
                printf("Enter price of the new book: ");
                scanf("%lf", &price);
                root = insertBook(root, createBook(isbn, title, author, genre, price));
                printf("Book added successfully!\n");
                break;
            case 2:
                printf("Enter ISBN of the book to delete: ");
                scanf("%s", isbn);
                root = deleteBook(root, isbn);
                printf("Book deleted successfully!\n");
                break;
            case 3:
                printf("Search by:\n");
                printf("1. ISBN\n");
                printf("2. Genre\n");
                printf("3. Author\n");
                printf("4. Title\n"); // New option for searching by title
                printf("Enter your choice: ");
                int searchChoice;
                scanf("%d", &searchChoice);
                switch (searchChoice) {
                    case 1:
                        printf("Enter ISBN of the book to search: ");
                        scanf("%s", isbn);
                        Book* foundBook = searchBookBFSByISBN(root, isbn);
                        if (foundBook != NULL) {
                            printf("Book found!\n");
                            displayBook(foundBook);
                        } else {
                            printf("Book not found.\n");
                        }
                        break;
                    case 2:
                        printf("Enter genre of the book to search: ");
                        scanf(" %[^\n]s", genre);
                        printf("\nBooks in the %s genre:\n", genre);
                        searchBooksBFSByGenre(root, genre);
                        break;
                    case 3:
                        printf("Enter author of the book to search: ");
                        scanf(" %[^\n]s", author);
                        printf("\nBooks by %s:\n", author);
                        searchBooksBFSByAuthor(root, author);
                        break;
                    case 4:
                        printf("Enter title of the book to search: ");
                        scanf(" %[^\n]s", title);
                        printf("\nBooks with title %s:\n", title);
                        searchBooksBFSByTitle(root, title);
                        break; // Added case for searching by title
                    default:
                        printf("Invalid choice. Please try again.\n");
                        break;
                }
                break;
            case 4:
                // Sort books by title using quicksort
                printf("Sorting books by title...\n");
                int numBooks = 0;
                Book* books[100];
                void inorderTraversal(Book* node) {
                    if (node != NULL) {
                        inorderTraversal(node->left);
                        books[numBooks++] = node;
                        inorderTraversal(node->right);
                    }
                }
                inorderTraversal(root);
                quickSortByTitle(books, 0, numBooks - 1);
                printf("Books sorted by title:\n");
                for (int i = 0; i < numBooks; i++) {
                    displayBook(books[i]);
                }
                break;
            case 5:
                printf("Exiting program.");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 5);

    return 0;
}


