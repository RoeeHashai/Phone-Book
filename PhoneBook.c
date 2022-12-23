/******************************************
*Student name: Roee Hashai
*Student ID: 209853282
*User Name: hashair
*Exercise name: ex_5
******************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARRAY_LENGTH 11
#define ABC_LENGTH 26

// define the Contact
typedef struct Contact {
    char *firstName;
    char *lastName;
    char *phoneNum;
    struct Contact *next;
} Contact;

// enum that helps to determine if contact exist in list before adding
enum contactAddStatus {
    NAME_ERROR = 1, PHONE_NUMBER_ERROR, VALID
};

void printWelcomeMessage();

void printMenu();

void printExitMessage();

void printErrorMessage();

int getOption();

void initPhoneBook(Contact *phonebook[ABC_LENGTH]);

Contact *createContact(char firstName[MAX_ARRAY_LENGTH],
                       char lastName[MAX_ARRAY_LENGTH],
                       char phoneNumber[MAX_ARRAY_LENGTH],
                       Contact *phonebook[ABC_LENGTH]);

void freeContactFieldMemory(Contact *contact);

int contactExist(Contact *phonebook[ABC_LENGTH], Contact *newContact);

void addNewContact(Contact *phonebook[ABC_LENGTH]);

void deleteContact(Contact *phonebook[ABC_LENGTH]);

Contact *searchContactByPhoneNum(Contact *phonebook[ABC_LENGTH],
                                 char phoneNumber[MAX_ARRAY_LENGTH]);

void searchContactByPhoneNumMng(Contact *phonebook[ABC_LENGTH]);

Contact *searchContactByName(Contact *phonebook,
                             char firstName[MAX_ARRAY_LENGTH],
                             char lastName[MAX_ARRAY_LENGTH]);

void searchContactByNameMng(Contact *phonebook[ABC_LENGTH]);

void updateContactPhoneNumber(Contact *phonebook[ABC_LENGTH]);

void printPhoneBook(Contact *phonebook[ABC_LENGTH]);

void freePhoneBook(Contact *phonebook[ABC_LENGTH]);

int main() {
    // phonebook and option declaration
    Contact *phonebook[ABC_LENGTH];
    int option;
    // init phonebook null
    initPhoneBook(phonebook);
    printWelcomeMessage();
    do {
        // print menu and get option from user and print menu
        printMenu();
        option = getOption();
        if (option > 7 || option <= 0) {
            // while the option is invalid continue to get option from user
            while (option > 7 || option <= 0) {
                printErrorMessage();
                option = getOption();
            }
        }
        switch (option) {
            case 1:
                // 1. Add a new contact to the phone book.
                addNewContact(phonebook);
                break;
            case 2:
                // 2. Delete a contact from the phone book.
                deleteContact(phonebook);
                break;
            case 3:
                // 3. Find a contact in the phone book by phone number.
                searchContactByPhoneNumMng(phonebook);
                break;
            case 4:
                // 4. Find a contact in the phone book by name.
                searchContactByNameMng(phonebook);
                break;
            case 5:
                // 5. Update phone number for a contact.
                updateContactPhoneNumber(phonebook);
                break;
            case 6:
                // 6. Print phone book.
                printPhoneBook(phonebook);
                break;
            case 7:
                // 7. Exit.
                freePhoneBook(phonebook);
                printExitMessage();
                break;
            default:
                break;
        }
    } while (option != 7);
    return 0;
}

/***********************************************************************
* function name: printWelcomeMessage
* The Input: no input
* The output: no output
* The Function operation: prints Welcome message to user
***********************************************************************/
void printWelcomeMessage() {
    printf("Welcome to the phone book manager!\n");
}

/***********************************************************************
* function name: printMenu
* The Input: no input
* The output: no output
* The Function operation: prints the menu to user
***********************************************************************/
void printMenu() {
    printf("Welcome to the phone book manager!\n"
           "Choose an option:\n"
           "1. Add a new contact to the phone book.\n"
           "2. Delete a contact from the phone book.\n"
           "3. Find a contact in the phone book by phone number.\n"
           "4. Find a contact in the phone book by name.\n"
           "5. Update phone number for a contact.\n"
           "6. Print phone book.\n"
           "7. Exit.\n");
}

/***********************************************************************
* function name: printExitMessage
* The Input: no input
* The output: no output
* The Function operation: prints the exit message to user
***********************************************************************/
void printExitMessage() {
    printf("Bye!");
}

/***********************************************************************
* function name: printErrorMessage
* The Input: no input
* The output: no output
* The Function operation: prints the error message to user
***********************************************************************/
void printErrorMessage() {
    printf("Wrong option, try again:\n");
}

/***********************************************************************
* function name: getOption
* The Input: no input
* The output: int option
* The Function operation: gets the option from user and return the option
***********************************************************************/
int getOption() {
    int option;
    scanf("%d", &option);
    return option;

}

/***********************************************************************
* function name: initPhoneBook
* The Input: Contact phonebook
* The output: no output
* The Function operation: initializes phonebook, makes all pointers to point
* to NULL
***********************************************************************/
void initPhoneBook(Contact *phonebook[ABC_LENGTH]) {
    for (int i = 0; i < ABC_LENGTH; ++i) {
        phonebook[i] = NULL;
    }
}

/***********************************************************************
* function name: createContact
* The Input: arrays of - firstname, last name, phoneNumber, phonebook
* The output: a pointer to the new contact
* The Function operation: allocates memory for the struct and for all struct
* filed and return a pointer to adress in the Heap memory of the struct
***********************************************************************/
Contact *createContact(char firstName[MAX_ARRAY_LENGTH],
                       char lastName[MAX_ARRAY_LENGTH],
                       char phoneNumber[MAX_ARRAY_LENGTH],
                       Contact *phonebook[ABC_LENGTH]) {
    // allocate memory for the struct
    Contact *ptrNewContact = (Contact *) malloc(sizeof(Contact));
    if (ptrNewContact == NULL) {
        freePhoneBook(phonebook);
        exit(1);
    }
    // allocate memory for the struct filed - firstName
    ptrNewContact->firstName = (char *) malloc((strlen(firstName) + 1) *
                                               sizeof(char));
    if (ptrNewContact->firstName == NULL) {
        // if allocation failed free all Heap memory allocated
        free(ptrNewContact);
        freePhoneBook(phonebook);
        exit(1);
    }
    // copy the string into the block of memory that has been allocated
    stpcpy(ptrNewContact->firstName, firstName);

    // allocate memory for the struct filed - lastName
    ptrNewContact->lastName = (char *) malloc((strlen(lastName) + 1) *
                                              sizeof(char));
    if (ptrNewContact->lastName == NULL) {
        // if allocation failed free all Heap memory allocated
        free(ptrNewContact);
        free(ptrNewContact->firstName);
        freePhoneBook(phonebook);
        exit(1);
    }
    // copy the string into the block of memory that has been allocated
    stpcpy(ptrNewContact->lastName, lastName);

    // allocate memory for the struct filed - lastName
    ptrNewContact->phoneNum = (char *) malloc(strlen(phoneNumber) *
                                              sizeof(char));
    if (ptrNewContact->phoneNum == NULL) {
        // if allocation failed free all Heap memory allocated
        free(ptrNewContact);
        free(ptrNewContact->firstName);
        free(ptrNewContact->lastName);
        freePhoneBook(phonebook);
        exit(1);
    }
    // copy the string into the block of memory that has been allocated
    stpcpy(ptrNewContact->phoneNum, phoneNumber);
    return ptrNewContact;
}

/***********************************************************************
* function name: freeContactFieldMemory
* The Input: a pointer to a contact struct
* The output: no output
* The Function operation: frees all Heap memory allocates for the struct fields
***********************************************************************/
void freeContactFieldMemory(Contact *contact) {
    free(contact->firstName);
    contact->firstName = NULL;
    free(contact->lastName);
    contact->lastName = NULL;
    free(contact->phoneNum);
    contact->phoneNum = NULL;
    contact->next = NULL;
}

/***********************************************************************
* function name: contactExist
* The Input: 2 pointers to contact struct
* The output: int
* The Function operation: determines if the name of contact exists already in
* list, or the numbers is already in list
***********************************************************************/
int contactExist(Contact *phonebook[ABC_LENGTH], Contact *newContact) {
    Contact *ptrScanner;
    for (int i = 0; i < ABC_LENGTH; ++i) {
        ptrScanner = phonebook[i];
        while (ptrScanner != NULL) {
            if (!strcmp(ptrScanner->firstName, newContact->firstName) &&
                !strcmp(ptrScanner->lastName, newContact->lastName)) {
                return NAME_ERROR;
            } else if (!strcmp(ptrScanner->phoneNum, newContact->phoneNum)) {
                return PHONE_NUMBER_ERROR;
            } else
                ptrScanner = ptrScanner->next;

        }
    }
    return VALID;
}

/***********************************************************************
* function name: addNewContact
* The Input: Contact *phonebook[]
* The output: no output
* The Function operation: creates a new contact and adds it to the phonebook
***********************************************************************/
void addNewContact(Contact *phonebook[ABC_LENGTH]) {
    // variable, arrays and pointers declaration and initialization
    Contact *ptrNewContact;
    int firstLetterIndex;
    int contactExistence;
    char firstName[MAX_ARRAY_LENGTH] = "";
    char lastName[MAX_ARRAY_LENGTH] = "";
    char phoneNumber[MAX_ARRAY_LENGTH] = "";

    // print the prompt to user and get input
    printf("Enter a contact details"
           " (<first name> <last name> <phone number>): ");
    scanf("%s%s%s", firstName, lastName, phoneNumber);

    // creates a new contact struct
    ptrNewContact = createContact(firstName, lastName, phoneNumber, phonebook);
    // check if the contact already exist in phonebook
    firstLetterIndex = ptrNewContact->lastName[0] - 'A';
    contactExistence = contactExist(phonebook, ptrNewContact);
    if (phonebook[firstLetterIndex] == NULL && contactExistence == VALID) {
        // in case of the first struct in list -> add it to list
        phonebook[firstLetterIndex] = ptrNewContact;
        printf("The contact has been added successfully!\n");
    } else {
        // in case of name error - the name already exist in phonebook
        if (contactExistence == NAME_ERROR) {
            printf("The addition of the contact has failed, "
                   "since the contact %s %s already exists!\n",
                   ptrNewContact->firstName, ptrNewContact->lastName);
            // free the memory of the struct that was created
            freeContactFieldMemory(ptrNewContact);
            free(ptrNewContact);
            ptrNewContact = NULL;

        } else if (contactExistence == PHONE_NUMBER_ERROR) {
            // in case of phoneNumber error - the phoneNumber already exist in
            // phonebook
            printf("The addition of the contact has failed, "
                   "since the phone number %s already exists!\n",
                   ptrNewContact->phoneNum);
            // free the memory of the struct that was created
            freeContactFieldMemory(ptrNewContact);
            free(ptrNewContact);
            ptrNewContact = NULL;
        } else {
            // add the new contact to the head of list(LIFO)
            ptrNewContact->next = phonebook[firstLetterIndex];
            phonebook[firstLetterIndex] = ptrNewContact;
            printf("The contact has been added successfully!\n");

        }
    }
}

/***********************************************************************
* function name: deleteContact
* The Input: Contact *phonebook[]
* The output: no output
* The Function operation: deletes a contact from the phonebook
***********************************************************************/
void deleteContact(Contact *phonebook[ABC_LENGTH]) {
    // variable, arrays and pointers declaration and initialization
    char firstName[MAX_ARRAY_LENGTH] = "";
    char lastName[MAX_ARRAY_LENGTH] = "";
    char confirmChar;
    Contact *ptrCurrentContact, *ptrToDelete;
    int firstLetterIndex;

    // print the prompt to user and get input
    printf("Enter a contact name (<first name> <last name>): ");
    scanf("%s%s", firstName, lastName);

    // point the pointer to the relevant list(by the first letter of last name)
    firstLetterIndex = lastName[0] - 'A';
    ptrCurrentContact = phonebook[firstLetterIndex];
    if (ptrCurrentContact == NULL) {
        // if the user wants to delete a contact that doesn't exist
        printf("The deletion of the contact has failed!\n");
        return;
    }
        // in case that need to delete the first struct in list
    else if (!strcmp(ptrCurrentContact->lastName, lastName) &&
             !strcmp(ptrCurrentContact->firstName, firstName)) {
        // confirmation that the user wants to delete the contact
        printf("\nAre you sure? (y/n) ");
        getchar();
        scanf("%c", &confirmChar);
        // if the user regretted the deletion - don't delete
        if (confirmChar != 'y' && confirmChar != 'Y') {
            printf("The deletion of the contact has been canceled.\n");
            return;
        }
        // delete the contact free its memory and fix the linked list
        phonebook[firstLetterIndex] = phonebook[firstLetterIndex]->next;
        freeContactFieldMemory(ptrCurrentContact);
        free(ptrCurrentContact);
        ptrCurrentContact = NULL;
        printf("The contact has been deleted successfully!\n");
        return;
    } else if (!strcmp(ptrCurrentContact->next->lastName, lastName) &&
               !strcmp(ptrCurrentContact->next->firstName, firstName)) {
        while (ptrCurrentContact->next != NULL) {
            if (!strcmp(ptrCurrentContact->next->lastName, lastName) &&
                !strcmp(ptrCurrentContact->next->firstName, firstName)) {
                // confirmation that the user wants to delete the contact
                printf("\nAre you sure? (y/n) ");
                getchar();
                scanf("%c", &confirmChar);
                // if the user regretted the deletion - don't delete
                if (confirmChar != 'y' && confirmChar != 'Y') {
                    printf("The deletion of the contact has been canceled"
                           ".\n");
                    return;
                }
                // delete the contact free its memory and fix the linked list
                ptrToDelete = ptrCurrentContact->next;
                ptrCurrentContact->next = ptrCurrentContact->next->next;
                freeContactFieldMemory(ptrToDelete);
                free(ptrToDelete);
                ptrToDelete = NULL;
                printf("The contact has been deleted successfully!\n");
                return;
            } else
                ptrCurrentContact = ptrCurrentContact->next;
        }
    } else
        // if the user wants to delete a contact that doesn't exist
        printf("The deletion of the contact has failed!\n");
}

/***********************************************************************
* function name: searchContactByPhoneNum
* The Input: Contact *phonebook[], phoneNumber
* The output: Contact *
* The Function operation: search for contact by its phoneNumber, if found
* return the address else return NULL
***********************************************************************/
Contact *searchContactByPhoneNum(Contact *phonebook[ABC_LENGTH],
                                 char phoneNumber[MAX_ARRAY_LENGTH]) {
    Contact *ptrScanner;
    for (int i = 0; i < ABC_LENGTH; ++i) {
        ptrScanner = phonebook[i];
        if (ptrScanner != NULL) {
            while (ptrScanner != NULL) {
                if (!strcmp(ptrScanner->phoneNum, phoneNumber))
                    // the contact has been found
                    return ptrScanner;
                ptrScanner = ptrScanner->next;
            }
        }
    }
    // the contact hasn't been found
    return NULL;
}

/***********************************************************************
* function name: searchContactByPhoneNumMng
* The Input: Contact *phonebook[]
* The output: no output
* The Function operation: manages the searching of a contact by its phone
* number and prints the contact info if found
***********************************************************************/
void searchContactByPhoneNumMng(Contact *phonebook[ABC_LENGTH]) {
    // array and pointers declaration and initialization
    char phoneNumber[MAX_ARRAY_LENGTH];
    Contact *ptrScanner;
    // get input from user into the phoneNumber string
    printf("Enter a phone number: ");
    scanf("%s", phoneNumber);

    // gets the address of the contact that has found(if exist)
    ptrScanner = searchContactByPhoneNum(phonebook, phoneNumber);
    if (ptrScanner != NULL) {
        // the contact has found
        printf("The following contact was found: %s %s %s\n",
               ptrScanner->firstName, ptrScanner->lastName,
               ptrScanner->phoneNum);
    } else
        // the contact has not found
        printf("No contact with a phone number %s was found in the phone "
               "book\n",
               phoneNumber);
}

/***********************************************************************
* function name: searchContactByName
* The Input: Contact *phonebook[], firstname[] and lastname[]
* The output: Contact *
* The Function operation: search for contact by its first and last name, if
* found return the address else return NULL
***********************************************************************/
Contact *searchContactByName(Contact *phonebook,
                             char firstName[MAX_ARRAY_LENGTH],
                             char lastName[MAX_ARRAY_LENGTH]) {
    Contact *ptrScanner;
    ptrScanner = phonebook;
    while (ptrScanner != NULL) {
        if (!strcmp(ptrScanner->lastName, lastName) &&
            !strcmp(ptrScanner->firstName, firstName)) {
            // the contact has been found
            return ptrScanner;
        }
        ptrScanner = ptrScanner->next;
    }
    // the contact hasn't been found
    return NULL;
}

/***********************************************************************
* function name: searchContactByNameMng
* The Input: Contact *phonebook[]
* The output: no output
* The Function operation: manages the searching of a contact by its full name
* and prints the contact info if found
***********************************************************************/
void searchContactByNameMng(Contact *phonebook[ABC_LENGTH]) {
    // variables array and pointers declaration and initialization
    char firstName[MAX_ARRAY_LENGTH] = "";
    char lastName[MAX_ARRAY_LENGTH] = "";
    int firstLetterIndex;
    Contact *ptrScanner;

    // get input from user into the names strings
    printf("Enter a contact name (<first name> <last name>): ");
    scanf("%s%s", firstName, lastName);
    firstLetterIndex = lastName[0] - 'A';

    // gets the address of the contact that has found(if exist)
    ptrScanner = searchContactByName(phonebook[firstLetterIndex],
                                     firstName, lastName);
    // if the contact has found - print it else - print the missing message
    if (ptrScanner != NULL)
        printf("The following contact was found: %s %s %s\n",
               ptrScanner->firstName, ptrScanner->lastName,
               ptrScanner->phoneNum);
    else
        printf("No contact with a name %s %s was found in the phone book\n",
               firstName, lastName);
}

/***********************************************************************
* function name: updateContactPhoneNumber
* The Input: Contact *phonebook[]
* The output: no output
* The Function operation: updates the phone number of the contact
***********************************************************************/
void updateContactPhoneNumber(Contact *phonebook[ABC_LENGTH]) {
    // variables array and pointers declaration and initialization
    char firstName[MAX_ARRAY_LENGTH] = "";
    char lastName[MAX_ARRAY_LENGTH] = "";
    char newPhoneNumber[MAX_ARRAY_LENGTH] = "";
    int firstLetterIndex;
    Contact *ptrContactUpdate, *ptrScanner;

    // get input from user into the names strings
    printf("Enter a contact name (<first name> <last name>): ");
    scanf("%s%s", firstName, lastName);
    firstLetterIndex = lastName[0] - 'A';

    // gets the address of the wanted contact
    ptrContactUpdate = searchContactByName(phonebook[firstLetterIndex],
                                           firstName, lastName);
    if (ptrContactUpdate != NULL)
        // print the contact info
        printf("The following contact was found: %s %s %s\n",
               ptrContactUpdate->firstName, ptrContactUpdate->lastName,
               ptrContactUpdate->phoneNum);
    else {
        // in case the contact wanted doesn't exist in phonebook
        printf("No contact with a name %s %s was found in the phone book\n",
               firstName, lastName);
        return;
    }

    // get the new phone number from user
    printf("Enter the new phone number: ");
    scanf("%s", newPhoneNumber);
    // check if the number exist in phonebook
    ptrScanner = searchContactByPhoneNum(phonebook, newPhoneNumber);
    if (ptrScanner != NULL) {
        printf("The update of the contact has failed, "
               "since the phone number %s already exists!\n",
               ptrScanner->phoneNum);
        ptrScanner = NULL;
        ptrContactUpdate = NULL;
        return;
    } else {
        // after all checks - update the phone number
        strcpy(ptrContactUpdate->phoneNum, newPhoneNumber);
        printf("The contact has been updated successfully!\n");
    }
}

/***********************************************************************
* function name: printPhoneBook
* The Input: Contact *phonebook[]
* The output: no output
* The Function operation: prints the phone book to user
***********************************************************************/
void printPhoneBook(Contact *phonebook[ABC_LENGTH]) {
    Contact *ptrScanner;
    for (int i = 0; i < ABC_LENGTH; ++i) {
        ptrScanner = phonebook[i];
        if (ptrScanner != NULL) {
            while (ptrScanner != NULL) {
                printf("%-10s%-10s%-10s\n", ptrScanner->firstName,
                       ptrScanner->lastName, ptrScanner->phoneNum);
                ptrScanner = ptrScanner->next;
            }
        }
    }
}

/***********************************************************************
* function name: freePhoneBook
* The Input: Contact *phonebook[]
* The output: no output
* The Function operation: frees all the Heap memory of the phonebook
***********************************************************************/
void freePhoneBook(Contact *phonebook[ABC_LENGTH]) {
    Contact *ptrScanner;
    for (int i = 0; i < ABC_LENGTH; ++i) {
        ptrScanner = phonebook[i];
        if (ptrScanner != NULL) {
            while (ptrScanner != NULL) {
                phonebook[i] = phonebook[i]->next;
                // free all the contact memory
                freeContactFieldMemory(ptrScanner);
                ptrScanner->next = NULL;
                free(ptrScanner);
                ptrScanner = phonebook[i];
            }
        }
    }
}