/*********************************************************************************
 Name: Shota Tonari
 Cruz ID: 1828506
 ECE13
 *********************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "LinkedList.h"
#include "BOARD.h"



/**
 * This function starts a new linked list. Given an allocated pointer to data it will return a
 * pointer for a malloc()ed ListItem struct. If malloc() fails for any reason, then this function
 * returns NULL otherwise it should return a pointer to this new list item. data can be NULL.
 *
 * @param data The data to be stored in the first ListItem in this new list. Can be any valid 
 *             pointer value.
 * @return A pointer to the malloc()'d ListItem. May be NULL if an error occured.
 */

// FINISHED

ListItem *LinkedListNew(char *data){
    ListItem *link = malloc(sizeof(ListItem));
    // Checks for NULL and returns NULL
    if (link == NULL) {
        return NULL;
    } else {
        link->nextItem = link->previousItem = NULL;
        link->data = data;
    }
    return link;
}



/**
 * This function allocates a new ListItem containing data and inserts it into the list directly
 * after item. It rearranges the pointers of other elements in the list to make this happen. If
 * passed a NULL item, CreateAfter() should still create a new ListItem, just with no previousItem.
 * It returns NULL if it can't malloc() a new ListItem, otherwise it returns a pointer to the new
 * item. The data parameter is also allowed to be NULL.
 *
 * @param item The ListItem that will be before the newly-created ListItem.
 * @param data The data the new ListItem will point to.
 * @return A pointer to the newly-malloc()'d ListItem.
 */

// FINISHED

ListItem *LinkedListCreateAfter(ListItem *item, char *data){
    
    // Declare Temp Storage
    ListItem *newCreate = LinkedListNew(data);
    ListItem *next = item->nextItem;
    
    // Check if item is NULL
    if (next == NULL) {
        newCreate->previousItem = item;
        item->nextItem = newCreate;
        newCreate->data = data;
    } else {
        newCreate->nextItem = next;
        item->nextItem->previousItem = newCreate;
        item->nextItem = newCreate;
        newCreate->data = data;
        newCreate->previousItem = item;
    }
    return newCreate;
}


/**
 * This function will remove a list item from the linked list and free() the memory that the
 * ListItem struct was using. It doesn't, however, free() the data pointer and instead returns it
 * so that the calling code can manage it.  If passed a pointer to NULL, LinkedListRemove() should
 * return NULL to signal an error.
 *
 * @param item The ListItem to remove from the list.
 * @return The data pointer from the removed item. May be NULL.
 */
char *LinkedListRemove(ListItem *item){
    // Return NULL if item is NULL
    if (item == NULL) {
        return NULL;
    }
    // Declare list remove pointer to data 
    char *listremove = item->data;
    
    // Declare pointers for if statements
    ListItem *next = item->nextItem;
    ListItem *previous = item ->previousItem;
       
    if (next == NULL && previous == NULL){
        
    } else if (next == NULL){
        previous->nextItem = NULL;
    } else if (previous == NULL){
        next->previousItem = NULL;
    } else {
        item->previousItem->nextItem = next;
        item->nextItem->previousItem = previous;
                
    }
    free(&(*item));
    return listremove;
}

/**
 * This function returns the total size of the linked list. This means that even if it is passed a
 * ListItem that is not at the head of the list, it should still return the total number of
 * ListItems in the list. A NULL argument will result in 0 being returned.
 *
 * @param list An item in the list to be sized.
 * @return The number of ListItems in the list (0 if `list` was NULL).
 */

// FINISHED

int LinkedListSize(ListItem *list){
    int zero = 0;
    // Return 0 if list is NULL
    if (list == NULL) {
        return zero;
    }
    // Declare size as 0, increment in the while loop
    int size = 0;
    
    ListItem *ListSize = LinkedListGetFirst(list);
    
    while (ListSize) {
        size = size + 1;
        ListSize = ListSize->nextItem;
    }
    return size;

}


/**
 * This function returns the head of a list given some element in the list. If it is passed NULL,
 * it will just return NULL. If given the head of the list it will just return the pointer to the
 * head anyways for consistency.
 *
 * @param list An element in a list.
 * @return A pointer to the first element in the list. Or NULL if provided an invalid list.
 */

// FINISHED

ListItem *LinkedListGetFirst(ListItem *list){
    // if list is NULL return NULL
    if (list == NULL) {
        return NULL;
    }
    while (list->previousItem) {
        list = list->previousItem;
    }
    return list;
}

/**
 * This function operates identically to LinkedListGetFirst(), but returns
 * the tail of a linked list.
 * 
 * @param list An element in a list.
 * @return A pointer to the last element in the list. Or NULL if provided an invalid list.
 */

// FINISHED

ListItem *LinkedListGetLast(ListItem *list) {
    if (list == NULL) {
        return NULL;
    }
        
    ListItem *templast = list;
    
    for (; templast->nextItem != NULL;) {
        templast = templast->nextItem;
    }
    return templast;
}


/**
 * LinkedListSwapData() switches the data pointers of the two provided ListItems. This is most
 * useful when trying to reorder ListItems but when you want to preserve their location. This
 * function should return STANDARD_ERROR if either arguments are NULL, otherwise it should return
 * SUCCESS. If one or both of the data pointers are NULL in the given ListItems, it still does
 * perform the swap and returns SUCCESS.
 *
 * @param firstItem One of the items whose data will be swapped.
 * @param secondItem Another item whose data will be swapped.
 * @return SUCCESS if the swap worked or STANDARD_ERROR if it failed.
 */

// FINISHED

int LinkedListSwapData(ListItem *firstItem, ListItem *secondItem){
    // If first or second item is null, return standard error
    if (firstItem == NULL || secondItem == NULL){
       return STANDARD_ERROR;
    }
    char *tempSwap = firstItem->data;
    firstItem->data = secondItem->data;
    secondItem->data = tempSwap;
    
    return SUCCESS;
}
   

/**
 * LinkedListPrint() prints out the complete list to stdout. This function prints out the given
 * list, starting at the head if the provided pointer is not the head of the list, like "[STRING1,
 * STRING2, ... ]" If LinkedListPrint() is called with a NULL list it does nothing, returning
 * STANDARD_ERROR. If passed a valid pointer, prints the list and returns SUCCESS.
 *
 * @param list Any element in the list to print.
 * @return SUCCESS or STANDARD_ERROR if passed NULL pointers.
 */
int LinkedListPrint(ListItem *list){
    // If list is null, return standard error
    if (list == NULL){
        return STANDARD_ERROR;
    }
    // Declare LinkedListGetFirst as list
    list = LinkedListGetFirst(list);
    
    // Starts printing list from the head until all the tail
    printf("[ ");
    while ((list->nextItem) != NULL){
        printf("%s, ", list->data);
        list = list->nextItem;
    } 
    // Prints last Item
    printf("%s]\n", list->data);
    return SUCCESS;
}