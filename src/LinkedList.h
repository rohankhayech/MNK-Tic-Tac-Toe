#ifndef LL_H
#define LL_H


/* ListNode struct
|* Represents an item in the list and holds the next and prev nodes, and the items value.
|* Links items in a LinkedList together */
typedef struct ListNode 
{
    void* value;
    struct ListNode* next;
    struct ListNode* prev;
} ListNode;

/* LinkedList struct
|* Allows for unlimited storage of any datatype in a list
|* Stores the head and tail of the list as well as a count of items.
|* Managed by the below functions */
typedef struct 
{
    ListNode* head;
    ListNode* tail;
    int count;
} LinkedList;


/* Print/Free Value Function Pointers
|* Points to a function used to print/free the specific datatypes in the linked list.
|* Necessary as the generic linked list does not know what data it holds. */
typedef void (*PrintFunc)(void*);
typedef void (*FreeFunc)(void*);

/* Print To File Function Pointer
|* Similar purpose to the above however should print to file rather than the terminal.
|* Therefore passes in a FILE* as well*/
typedef void (*FilePrintFunc)(void*,FILE*);


/* Functions to manage the LinkedLists */
LinkedList* createLinkedList();
ListNode* createListNode(void* value);
void insertFirst(LinkedList* list, void* value);
void insertLast(LinkedList* list, void* value);
void* removeFirst(LinkedList* list);
void* removeLast(LinkedList* list);
void* peekFirst(LinkedList* list);
void* peekLast(LinkedList* list);
int isEmpty(LinkedList* list);
void printLinkedList(LinkedList* list, PrintFunc printFunc);
void printLinkedListToFile(LinkedList* list, FilePrintFunc printFunc, FILE* file);
void freeLinkedList(LinkedList* list, FreeFunc freeFunc);
void freeNode(ListNode* node, FreeFunc freeFunc);
#endif