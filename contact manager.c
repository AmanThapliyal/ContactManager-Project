#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Define the contact structure
typedef struct Contact
{
    char name[100];
    char phoneNumber[20];
    struct Contact *next;
} Contact;

// Define the binary search tree (BST) node for contacts
typedef struct ContactNode
{
    Contact *contact;
    struct ContactNode *left;
    struct ContactNode *right;
} ContactNode;

// Function prototypes
Contact *createContact(char *name, char *phoneNumber);
ContactNode *createContactNode(Contact *contact);
void addContact(ContactNode **root, Contact *contact);
void displayContacts(ContactNode *root);
void deleteContact(ContactNode **root, char *name);
Contact *searchContact(ContactNode *root, char *name);
void updateContact(ContactNode *root, char *name, char *newPhoneNumber);
Contact *searchContactByPhoneNumber(ContactNode *root, char *phoneNumber);

// Function implementations

// Function to create a new contact
Contact *createContact(char *name, char *phoneNumber)
{
    Contact *newContact = (Contact *)malloc(sizeof(Contact));
    strcpy(newContact->name, name);
    strcpy(newContact->phoneNumber, phoneNumber);
    newContact->next = NULL;
    return newContact;
}

// Function to create a new node for the contact BST
ContactNode *createContactNode(Contact *contact)
{
    ContactNode *newNode = (ContactNode *)malloc(sizeof(ContactNode));
    newNode->contact = contact;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to add a contact to the BST
void addContact(ContactNode **root, Contact *contact)
{
    if (*root == NULL)
    {
        *root = createContactNode(contact);
    }
    else
    {
        if (strcmp(contact->name, (*root)->contact->name) < 0)
        {
            addContact(&((*root)->left), contact);
        }
        else
        {
            addContact(&((*root)->right), contact);
        }
    }
}

// Function to display contacts in an in-order traversal
void displayContacts(ContactNode *root)
{
    if (root != NULL)
    {
        displayContacts(root->left);
        printf("Name: %s, Phone: %s\n", root->contact->name, root->contact->phoneNumber);
        displayContacts(root->right);
    }
}

// Function to delete a contact from the BST
void deleteContact(ContactNode **root, char *name)
{
    if (*root == NULL)
    {
        printf("Contact not found.\n");
        return;
    }

    // Search for the contact to delete
    if (strcmp(name, (*root)->contact->name) < 0)
    {
        deleteContact(&((*root)->left), name);
    }
    else if (strcmp(name, (*root)->contact->name) > 0)
    {
        deleteContact(&((*root)->right), name);
    }
    else
    {
        // Contact found, delete it
        ContactNode *temp = *root;

        // Node with only one child or no child
        if ((*root)->left == NULL)
        {
            *root = (*root)->right;
            free(temp);
        }
        else if ((*root)->right == NULL)
        {
            *root = (*root)->left;
            free(temp);
        }
        else
        {
            // Node with two children: Get the inorder successor (smallest
            // in the right subtree)
            ContactNode *successor = (*root)->right;
            while (successor->left != NULL)
            {
                successor = successor->left;
            }

            // Copy the inorder successor's data to this node
            strcpy((*root)->contact->name, successor->contact->name);
            strcpy((*root)->contact->phoneNumber, successor->contact->phoneNumber);

            // Delete the inorder successor
            deleteContact(&((*root)->right), successor->contact->name);
        }
    }
}

// Function to search for a contact by name in the BST
Contact *searchContact(ContactNode *root, char *name)
{
    if (root == NULL || strcmp(name, root->contact->name) == 0)
    {
        return (root != NULL) ? root->contact : NULL;
    }

    if (strcmp(name, root->contact->name) < 0)
    {
        return searchContact(root->left, name);
    }
    else
    {
        return searchContact(root->right, name);
    }
}

// Function to update contact information
void updateContact(ContactNode *root, char *name, char *newPhoneNumber)
{
    Contact *contactToUpdate = searchContact(root, name);
    if (contactToUpdate != NULL)
    {
        strcpy(contactToUpdate->phoneNumber, newPhoneNumber);
        printf("Contact information updated successfully!\n");
    }
    else
    {
        printf("Contact not found.\n");
    }
}

// Function to search for a contact by phone number in the BST
Contact *searchContactByPhoneNumber(ContactNode *root, char *phoneNumber)
{
    if (root == NULL || strcmp(phoneNumber, root->contact->phoneNumber) == 0)
    {
        return (root != NULL) ? root->contact : NULL;
    }

    if (strcmp(phoneNumber, root->contact->phoneNumber) < 0)
    {
        return searchContactByPhoneNumber(root->left, phoneNumber);
    }
    else
    {
        return searchContactByPhoneNumber(root->right, phoneNumber);
    }
}

// Main program
int main()
{
    ContactNode *contactTree = NULL; // Root of the binary search tree

    char name[100];
    char phoneNumber[20];
    char newPhoneNumber[20];

    int choice;
    do
    {
        // Display menu
        printf("\n1. Add Contact\n");
        printf("2. Display Contacts\n");
        printf("3. Delete Contact\n");
        printf("4. Update Contact Information\n");
        printf("5. Search Contact by Phone Number\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            // Add Contact
            printf("Enter contact name: ");
            scanf("%s", name);
            printf("Enter contact phone number: ");
            scanf("%s", phoneNumber);

            // Validate phone number length
            if (strlen(phoneNumber) != 10)
            {
                printf("Error: Phone number must have 10 digits.\n");
            }
            else
            {
                // Create a new contact and add it to the BST
                Contact *newContact = createContact(name, phoneNumber);
                addContact(&contactTree, newContact);
                printf("Contact added successfully!\n");
            }
            break;

        case 2:
            // Display Contacts
            printf("\nContacts:\n");
            displayContacts(contactTree);
            break;

        case 3:
            // Delete Contact
            printf("Enter contact name to delete: ");
            scanf("%s", name);
            deleteContact(&contactTree, name);
            break;

        case 4:
            // Update Contact Information
            printf("Enter contact name to update: ");
            scanf("%s", name);
            printf("Enter new phone number: ");
            scanf("%s", newPhoneNumber);
            updateContact(contactTree, name, newPhoneNumber);
            break;

        case 5:
            // Search Contact by Phone Number
            printf("Enter phone number to search: ");
            scanf("%s", phoneNumber);
            Contact *foundContactByPhoneNumber = searchContactByPhoneNumber(contactTree, phoneNumber);
            if (foundContactByPhoneNumber != NULL)
            {
                printf("Contact found:\n");
                printf("Name: %s, Phone: %s\n", foundContactByPhoneNumber->name, foundContactByPhoneNumber->phoneNumber);
            }
            else
            {
                printf("Contact not found.\n");
            }
            break;

        // ... (existing cases)

        } // end switch

    } while (choice != 0);

    // ... (existing code)

    return 0;
}