#include <stdio.h>

void addMenu() {
  printf("You added menu!\n");
}
void subMenu() {
  int choice;
  printf("1. Exit\n");
  printf("Enter number: ");
  scanf("%d", &choice);

  switch (choice) {
    case 1: 
      mainMenu();
      break;
    default:
      printf("Invalid Input\n");
      subMenu();
  }

}
void mainMenu() {
  int choice;
  printf("Main Menu\n\n");
  printf("1. Add Record\n");
  printf("2. View Record\n");
  printf("3. Delete Record\n");
  printf("4. Update Record\n");
  printf("5. Exit\n");

  printf("Enter number: ");
  scanf("%d", &choice);

  switch (choice) {
    case 1:
      system("cls");
      printf("Add your record!\n");
      addMenu();
      subMenu();
      break;
    case 2: 
      system("cls");
      printf("You view the record\n");
      subMenu();
      break;
    case 3:
      system("cls");
      printf("Delete your record!\n");
      subMenu();
      break;
    case 4:
    system("cls");
      printf("Update your record!\n");
      subMenu();
      break;
    case 5: 
      system("cls");
      printf("Thank you for using our program!\n");
      break;
    default:
      printf("Invalid Input!\n");
      mainMenu();
  }



}
int main() {

  mainMenu();

}
