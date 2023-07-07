#include <stdio.h>
#include <stdlib.h>

// STRUCT
typedef struct Node {
  int val;
  struct Node *prev;
  struct Node *next;
} Node;

typedef struct DoublyLinkedList {
  Node *head;
  Node *tail;
} DoublyLinkedList;

// FUNCTION DECLARATIONS
int prompt();
DoublyLinkedList createList();
void displayList(DoublyLinkedList list);
void displayNormal(DoublyLinkedList list);
void displayReverse(DoublyLinkedList list);
void sortAscending(DoublyLinkedList list);
void sortDescending(DoublyLinkedList list);
void insertNode(DoublyLinkedList *list);
void deleteNode(DoublyLinkedList *list);
void searchNumber(DoublyLinkedList list);

void freeList(DoublyLinkedList* list);

// MENU FUNCTIONS
int showInitialMenu();
int showMainMenu();
void showOption2SubMenu();
void showOption3SubMenu();

// GLOBAL DECLARATION
DoublyLinkedList list;

// MAIN
int main() {
  system("cls");

  // Display Menu
  /* If the list is empty, the menu should only include the 'Create a Doubly Linked List' and 'Exit' options. Otherwise, all options are available.*/ 
  if (list.head == NULL) {
    showInitialMenu();
  } else {
    showMainMenu();
  }
  freeList(&list);

  return 0;
}

int showInitialMenu() {
  int selectedOption;
  printf(" \
              MAIN MENU\n\
  \n\
  1. Create a Doubly Linked List\n\
  2. Exit\n\
  ");
  selectedOption = prompt();

  switch (selectedOption) {
      case 1:
        system("cls");
        printf("Create a Doubly Linked List\n");
        list = createList();
        system("cls");
        if (list.head == NULL) {
          printf("The list is empty!\n"); 
          showInitialMenu();
        } else {
          printf("\nYou successfully created your doubly linked list!\n");
          showMainMenu();
        }
        break;
      case 2:
        system("cls");
        printf("Thank you for using the program. Have a great day!\n");
        return 0;
        break;
      default:
        system("cls");
        printf("Invalid choice!\n");
        main();
  }
  return 0;
}

int showMainMenu() {
  int selectedOption;
  printf("\
              MAIN MENU\n\
  \n\
  1. Create a New Doubly Linked List\n\
  2. Display a Doubly Linked List\n\
    21. Normal order\n\
    22. Reverse order\n\
  3. Sort a Doubly Linked List\n\
    31. Ascending\n\
    32. Descending\n\
  4. Insert a Node\n\
  5. Delete a Node\n\
  6. Search a Number in the List\n\
  7. Exit\n \
  ");
  selectedOption = prompt();

  switch (selectedOption) {
    case 1:
      system("cls");
      printf("Create a Doubly Linked List\n");
      list = createList();
      system("cls");
      if (list.head == NULL) {
        printf("The list is empty!\n"); 
      } else {
        printf("\nYou successfully created your doubly linked list!\n");
      }
      showMainMenu();
      break;
    case 2:
      system("cls");
      displayList(list);
      showMainMenu();
      break;
    case 3:
      system("cls");
      showOption3SubMenu();
      break;
    case 4:
      system("cls");
      insertNode(&list);
      showMainMenu();
      break;
    case 5:
      system("cls");
      deleteNode(&list);
      showMainMenu();
      break;
    case 6:
      system("cls");
      searchNumber(list);
      showMainMenu();
      break;
    case 7:
      system("cls");
      printf("Thank you for using the program. Have a great day!\n");
      return 0;
    default:
      system("cls");
      printf("Invalid choice!\n");
      showMainMenu();
  }
  return 0;
}

void showOption2SubMenu() {
  printf("\
  Display a Doubly Linked List\n\
    1. Normal Order\n\
    2. Reverse Order\n\
    3. Back\n\
  ");
}

void showOption3SubMenu() {
  int selectedOption; 
  printf("\
  Sort a Doubly Linked List\n\
    1. Ascending\n\
    2. Descending\n\
    3. Back\n\
  ");
  selectedOption = prompt();

  switch (selectedOption) {
    case 1:
      system("cls");
      printf("The list is successfully sorted in Ascending Order\n");
      sortAscending(list);
      printf("Press any key to exit...");
      scanf("\n");
      getchar();
      system("cls");
      showOption3SubMenu();
      break;
    case 2: 
      system("cls");
      printf("The list is successfully sorted in Descending Order\n");
      sortDescending(list);
      printf("Press any key to exit...");
      scanf("\n");
      system("cls");
      getchar();
      showOption3SubMenu();
      break;
    case 3:
      system("cls");
      showMainMenu();
      break;
    default:
      system("cls");
      printf("Invalid choice\n");
      showOption3SubMenu();
  }
}

int prompt() {
  int selectedOption;
  printf("\nEnter choice: ");
  scanf("%d", &selectedOption);

  return selectedOption;
}

DoublyLinkedList createList() {
  DoublyLinkedList list;
  Node *curr;
  int val;
  list.head = NULL;

  system("cls");
  printf("Insert values for your doubly linked list\n\n");
  do {
    printf("Enter value (0 to stop): ");
    scanf("%d", &val);

    if (val != 0) {
      curr = (Node*)malloc(sizeof(Node));
      curr->val = val;

      if (list.head == NULL) {
        list.head = curr;
        list.tail = curr;
        curr->prev = NULL;
        curr->next = NULL;
      } else {
        list.tail->next = curr;
        curr->prev = list.tail;
        list.tail = curr;
        curr->next = NULL;
      }
    }
  } while (val != 0);

  return list;
}

void displayList(DoublyLinkedList list) {
  int selectedOption;
  showOption2SubMenu();
  printf("\nEnter choice: ");
  scanf("%d", &selectedOption);

  switch (selectedOption) {
    case 1:
      system("cls");
      printf("You selected normal order\n");
      displayNormal(list);

      printf("\nPress any key to exit...");
      scanf("\n");
      getchar();
      system("cls");
      break;
    case 2:
      system("cls");
      printf("You selected reverse order\n");
      displayReverse(list);
      break;
    case 3:
      system("cls");
      printf("You selected back\n");
      break;
    default:
      system("cls");
      printf("Invalid choice!\n");
      displayList(list);
  }
}

void displayNormal(DoublyLinkedList list) {
  Node *curr = list.head;
  system("cls");
  printf("Here is your doubly linked list in normal order\n\n");

  while (curr != NULL) {
    printf("%d|", curr->val);
    curr = curr->next;
  }
  printf("\n");
 
}

void displayReverse(DoublyLinkedList list) {
  Node *curr = list.tail;
  system("cls");
  printf("Here is your doubly linked list in reverse order\n\n");
  while (curr != NULL) {
    printf("%d|", curr->val);
    curr = curr->prev;
  }
  printf("\n");
  printf("\nPress any key to exit...");
  scanf("\n");
  getchar();
  system("cls");
}

void sortAscending(DoublyLinkedList list) {
  Node *curr = list.head;
  int temp;
  int switched = 1;

  while (switched) {
    switched = 0;
    curr = list.head;
    while (curr->next != NULL) {
      if (curr->val > curr->next->val) {
        temp = curr->val;
        curr->val = curr->next->val;
        curr->next->val = temp;
        switched = 1;
      }
      curr = curr->next;
   }
  }
}

void sortDescending(DoublyLinkedList list) {
  Node *curr = list.tail;
  int temp;
  int switched = 1;

  while (switched) {
    switched = 0;
    curr = list.tail;
    while (curr->prev != NULL) {
      if (curr->val > curr->prev->val) {
        temp = curr->val;
        curr->val = curr->prev->val;
        curr->prev->val = temp;
        switched = 1;
      }
      curr = curr->prev;
   }
  }
}

void insertNode(DoublyLinkedList *list) {
  int val;
  printf("Enter the value to insert: ");
  scanf("%d", &val);

  Node *newNode = (Node*)malloc(sizeof(Node));
  newNode->val = val;
  newNode->prev = NULL;
  newNode->next = NULL;

  if (list->head == NULL) {
    list->head = newNode;
    list->tail = newNode;
  } else {
    int position;
    displayNormal(*list);
    printf("Enter the position to insert (1 for first, 2 for second, and so on): ");
    scanf("%d", &position);

    Node *curr = list->head;
    int count = 1;

    while (curr != NULL && count < position) {
      curr = curr->next;
      count++;
    }
    
    system("cls");
    if (curr == NULL) {
      printf("Invalid position!\n");
      free(newNode);
    } else {
      newNode->prev = curr->prev;
      newNode->next = curr;
      if (curr->prev != NULL) {
        curr->prev->next = newNode;
      } else {
        list->head = newNode;
      }
      curr->prev = newNode;
    }
  }
}

void deleteNode(DoublyLinkedList *list) {
  if (list->head == NULL) {
    printf("The list is empty!\n");
    return;
  }

  int position;
  displayNormal(*list);
  printf("Enter the position to delete (1 for first, 2 for second, and so on): ");
  scanf("%d", &position);
  system("cls");
  Node *curr = list->head;
  int count = 1;

  while (curr != NULL && count < position) {
    curr = curr->next;
    count++;
  }

  if (curr == NULL) {
    printf("Invalid position!\n");
  } else {
    if (curr->prev != NULL) {
      curr->prev->next = curr->next;
    } else {
      list->head = curr->next;
    }

    if (curr->next != NULL) {
      curr->next->prev = curr->prev;
    } else {
      list->tail = curr->prev;
    }

    free(curr);
    printf("Node at position %d has been deleted.\n", position);
  }
}

void searchNumber(DoublyLinkedList list) {
  if (list.head == NULL) {
    printf("The list is empty!\n");
    return;
  }

  int val;
  printf("Enter the value to search: ");
  scanf("%d", &val);
  system("cls");
  Node *curr = list.head;
  int count = 1;
  int found = 0;

  while (curr != NULL) {
    if (curr->val == val) {
      printf("Value %d found at position %d.\n", val, count);
      found = 1;
    }
    curr = curr->next;
    count++;
  }

  if (!found) {
    printf("Value %d not found in the list.\n", val);
  }
}

void freeList(DoublyLinkedList* list) {
  Node* curr = list->head;
  Node* next;

  while (curr != NULL) {
    next = curr->next;
    free(curr);
    curr = next;
  }
  list->head = NULL;
  list->tail = NULL;
}
