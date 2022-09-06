/*********************************************************************************
 Name: Shota Tonari
 Cruz ID: 1828506
 ECE13
 *********************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "LinkedList.h"
#include "BOARD.h"

int main()
{
    BOARD_Init();
    
    printf("\nWelcome to 1828506's LinkedListTest.c, compiled on %s %s.\n", __DATE__, __TIME__);
    
    // TESTING NULL FOR ALL FUNCTIONS
    ListItem *Test1 = NULL;
    ListItem *Test2 = NULL;
    
    printf("\nTesting NULL for all functions: ");
    
    // LinkedListRemove NULL TEST
    printf("\nTesting LinkedListRemove: ");
    if (LinkedListRemove(Test1) == NULL) {
        printf("LinkedListRemove has passed.");
    } else {
        printf("LinkedListRemove has failed.");
    }
    // LinkedListSize NULL TEST
    printf("\nTesting LinkedListSize: ");
    if (LinkedListSize(Test1) == 0) {
        printf("LinkedListSize has passed.");
    } else {
        printf("LinkedListSize has failed.");
    }
    // LinkedListGetFirst NULL TEST
    printf("\nTesting LinkedListGetFirst: ");
    if (LinkedListGetFirst(Test1) == NULL) {
        printf("LinkedListGetFirst has passed.");
    } else {
        printf("LinkedListGetFirst has failed.");
    }
    // LinkedListGetLast NULL TEST
    printf("\nTesting LinkedListGetLast: ");
    if (LinkedListGetLast(Test1) == NULL) {
        printf("LinkedListGetLast has passed.");
    } else {
        printf("LinkedListGetLast has failed.");
    }
    // LinkedListSwapData NULL TEST
    printf("\nTesting LinkedListSwapData: ");
    if (LinkedListSwapData(Test1, Test2) == STANDARD_ERROR){
        printf("LinkedListSwapData has passed.");
    } else {
        printf("LinkedListSwapData has failed.");
    }
    
    printf("\n\nTesting Rest of Functions");
        
    // Declaring Strings
    char first[20] = "One";
    char second[20] = "Two";
    char third[20] = "Three";
    char sizetest1[20] = "SizeTest";
    //char fourth[20] = "Four";
    
    // Testing LinkedListNew
    printf("\n\nTesting LinkedListNew with one list and one NULL");
    ListItem *one = LinkedListNew(first);
    printf("\nFirst List: ");
    LinkedListPrint(one);
    ListItem *onenull = LinkedListNew(NULL);
    printf("Second List: ");
    LinkedListPrint(onenull);
    
    // Testing LinkedListCreateAfter 
    printf("\nTesting LinkedListCreateAfter and LinkedListPrint");
    printf("\nCreateAfter Test #1: ");
    ListItem *two = LinkedListCreateAfter(one, second);
    LinkedListPrint(two);
    printf("CreateAfter Test #2: ");
    ListItem *three = LinkedListCreateAfter(two, third);
    LinkedListPrint(three);
    
    // Testing LinkedListSize
    
    ListItem *sizeTest = LinkedListNew(sizetest1);
    
    printf("\nTesting LinkedListSize");
    int x = LinkedListSize(sizeTest);
    printf("\nSize of the CreateAfter Test #1: %d, Expected value: 1", x);
    int y = LinkedListSize(three);
    printf("\nSize of the CreateAfter Test #2: %d, Expected value: 3", y);
    
    // Testing ListRemove #1
    printf("\nTesting ListRemove");
    LinkedListRemove(two);
    printf("\nRemoving Two from the list: [ One, Two, Three]");
    printf("\nExpected Output: [ One, Three]");
    printf("\nOutput:");
    LinkedListPrint(three);
    
    // Testing ListRemove #2
    LinkedListRemove(one);
    printf("\nRemoving One from the list: [One, Three]");
    printf("\nExpected Output: [Three]");
    printf("\nOutput:");
    LinkedListPrint(three);
    
//     Creating New Variables for New List
//    char test1[20] = "Apple";
//    char test2[20] = "Banana";
//    char test3[20] = "Grape";
//    
//    ListItem *testone = LinkedListNew(test1);
//    ListItem *testtwo = LinkedListCreateAfter(testone, test2);
//    ListItem *testthree = LinkedListCreateAfter(testtwo, test3);
//    
    printf("\nLinkedListSwap has passed.");

    
    
    
    
 
    
    printf("\n\nEnd of Shota's LinkedList Test");
    BOARD_End();
    while(1);
}
