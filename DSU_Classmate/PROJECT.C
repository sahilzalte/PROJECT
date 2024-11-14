#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Node structure for Queue (Shopping Cart)
typedef struct CartNode {
    char item[50];
    struct CartNode* next;
} CartNode;

// Node structure for Stack (Undo Actions)
typedef struct ActionNode {
    char action[10];
    char item[50];
    struct ActionNode* next;
} ActionNode;

// Queue for cart management
CartNode* cartFront = NULL;
CartNode* cartRear = NULL;

// Stack for action history (Undo functionality)
ActionNode* actionTop = NULL;

// Function to add an item to the cart (enqueue operation)
void addItemToCart(const char* item) {
    CartNode* newNode = (CartNode*)malloc(sizeof(CartNode));
    strcpy(newNode->item, item);
    newNode->next = NULL;

    if (cartRear == NULL) {
        cartFront = cartRear = newNode;
    } else {
        cartRear->next = newNode;
        cartRear = newNode;
    }

    // Log action to stack for potential undo
    ActionNode* actionNode = (ActionNode*)malloc(sizeof(ActionNode));
    strcpy(actionNode->action, "add");
    strcpy(actionNode->item, item);
    actionNode->next = actionTop;
    actionTop = actionNode;

    printf("Item '%s' added to cart.\n", item);
}

// Function to remove the last added item from the cart (dequeue operation)
void removeLastItem() {
    if (cartFront == NULL) {
        printf("Cart is empty. No item to remove.\n");
        return;
    }

    CartNode* temp = cartFront;
    cartFront = cartFront->next;

    // Log action to stack for potential undo
    ActionNode* actionNode = (ActionNode*)malloc(sizeof(ActionNode));
    strcpy(actionNode->action, "remove");
    strcpy(actionNode->item, temp->item);
    actionNode->next = actionTop;
    actionTop = actionNode;

    printf("Item '%s' removed from cart.\n", temp->item);
    free(temp);

    // Reset rear pointer if the cart is empty
    if (cartFront == NULL) {
        cartRear = NULL;
    }
}

// Function to view all items in the cart
void displayCart() {
    if (cartFront == NULL) {
        printf("Your cart is empty.\n");
        return;
    }

    printf("Items in cart:\n");
    CartNode* current = cartFront;
    while (current != NULL) {
        printf("- %s\n", current->item);
        current = current->next;
    }
}

// Function to undo the last action
void undoLastAction() {
    if (actionTop == NULL) {
        printf("No actions to undo.\n");
        return;
    }

    ActionNode* lastAction = actionTop;
    actionTop = actionTop->next;

    if (strcmp(lastAction->action, "add") == 0) {
        // Undo the addition
        if (cartFront != NULL) {
            removeLastItem();  // Remove the item that was last added
        }
    } else if (strcmp(lastAction->action, "remove") == 0) {
        // Undo the removal by re-adding the item
        addItemToCart(lastAction->item);
    }

    free(lastAction);
}

// Main menu function
void displayMenu() {
    int choice;
    char item[50];

    while (1) {
        printf("\n--- Shopping Cart Menu ---\n");
        printf("1. Add Item\n");
        printf("2. Remove Last Item\n");
        printf("3. View Cart\n");
        printf("4. Undo Last Action\n");
        printf("5. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter item to add: ");
                scanf("%s", item);
                addItemToCart(item);
                break;
            case 2:
                removeLastItem();
                break;
            case 3:
                displayCart();
                break;
            case 4:
                undoLastAction();
                break;
            case 5:
                printf("Exiting program. Thank you!\n");
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

int main() {
    displayMenu();
    return 0;
}
