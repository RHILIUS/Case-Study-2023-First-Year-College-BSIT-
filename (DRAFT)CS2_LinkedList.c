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

// GLOBAL DECLARATION
DoublyLinkedList list;

// FUNCTION PROTOTYPE
void showMainMenu();
DoublyLinkedList createList();
void displayList();
void displayNormalOrder();
void displayReverseOrder();
void freeList(DoublyLinkedList* list);
void sortAscending(DoublyLinkedList list);
void sortDescending(DoublyLinkedList list);

// FORMS
void displayEmptyListMenu() {
  printf(" \
              MAIN MENU\n\
  \n\
  1. Create a Doubly Linked List\n\
  2. Exit\n\
");
}
 void displayMainMenu() {
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
 }
void displayOption2SubMenu() {
  printf("\
  Display a Doubly Linked List\n\
    1. Normal Order\n\
    2. Reverse Order\n\
    3. Back\n\
  ");
}
void displayOption3SubMenu() {
  int selectedOption;
  printf("\
  Sort a Doubly Linked List\n\
    1. Ascending\n\
    2. Descending\n\
    3. Back\n\
  ");
  printf("Enter choice: ");
  scanf("%d", &selectedOption);

  switch (selectedOption) {
    case 1:
      system("cls");
      printf("The list is successfully sorted to Ascending Order\n");
      sortAscending(list);
      printf("Press any key to exit...");
      scanf("\n");
      getchar();
      system("cls");
      displayOption3SubMenu();
      break;
    case 2: 
      system("cls");
      printf("The list is successfully sorted to Descending Order\n");
      sortDescending(list);
      printf("Press any key to exit...");
      scanf("\n");
      system("cls");
      getchar();
      displayOption3SubMenu();
      break;
    case 3:
      system("cls");
      showMainMenu();
    default:
      system("cls");
      printf("Invalid choice\n");
      displayOption3SubMenu();
  }
}

// MAIN
int main() {
 
  system("cls");
  showMainMenu();
  freeList(&list);

}

// FUNCTIONS
void showMainMenu() {
  int selectedOption;
  int listIsEmpty; // boolean

  // Determine whether list is empty or not
  if (list.head == NULL) {
    listIsEmpty = 1;
  } else {
    listIsEmpty = 0;
  }

  // Display Menu 
  /* If the list is empty, the menu should only include the 'Create a Doubly Linked List' and 'Exit' options. Otherwise, all options are available.*/ 
  if (listIsEmpty) {
    displayEmptyListMenu();    
  } else {
    displayMainMenu();
  }
  printf("\nEnter choice: ");
  scanf("%d", &selectedOption);
  
  if (listIsEmpty) {
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
      printf("Thank you for using the program. Have a great day!\n");
      exit(0);
      break;
    default:
      system("cls");
      printf("Invalid choice!\n");
      showMainMenu();
  }
  } else {
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
      break;
    case 3:
      system("cls");
      displayOption3SubMenu();
      break;
    case 4:
      system("cls");
      printf("You clicked four\n");
      break;
    case 5:
      system("cls");
      printf("You clicked five\n");
      break;
    case 6:
      system("cls");
      printf("You clicked six\n");
      break;
    case 7:
      system("cls");
      printf("Thank you for using the program. Have a great day!\n");
      exit(0);
      break;
    default:
      system("cls");
      printf("Invalid choice!\n");
      showMainMenu();
  }
  }
} 
DoublyLinkedList createList() {
  DoublyLinkedList list;
  list.head = NULL;
  Node *curr;
  int val;

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
  displayOption2SubMenu();
  printf("\nEnter choice: ");
  scanf("%d", &selectedOption);

  switch (selectedOption) {
    case 1:
      system("cls");
      printf("You selected normal order\n");
      displayNormalOrder(list);
      break;
    case 2:
      system("cls");
      printf("You selected reverse order\n");
      displayReverseOrder(list);
      break;
    case 3:
      system("cls");
      printf("You selected back\n");
      showMainMenu();
      break;
    default:
      system("cls");
      printf("Invalid choice!\n");
      displayList(list);
  }
}
void displayNormalOrder(DoublyLinkedList list) {
  Node *curr = list.head;
  system("cls");
  printf("Here is your doubly linked list in normal order\n\n");

  do {
    printf("%d|", curr->val);
    curr = curr->next;
  } while (curr != NULL);
  printf("\n");
  printf("\nPress any key to exit...");
  scanf("\n");
  getchar();
  system("cls");
  displayList(list);
}
void displayReverseOrder(DoublyLinkedList list) {
  Node *curr = list.tail;
  system("cls");
  printf("Here is your doubly linked list in reverse order\n\n");
  do {
    printf("%d|", curr->val);
    curr = curr->prev;
  } while (curr != NULL);
  printf("\n");
  printf("\nPress any key to exit...");
  scanf("\n");
  getchar();
  system("cls");
  displayList(list);
}
void sortAscending(DoublyLinkedList list) {
  Node *curr = list.head;
  int temp;
  int switched = 1;

  while (switched) {
    switched = 0;
    curr = list.head;
    while(curr->next != NULL) {
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
    while(curr->prev != NULL) {
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
