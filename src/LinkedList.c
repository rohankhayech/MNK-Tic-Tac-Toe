/*
 * Copyright (c) 2019 Rohan Khayech
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "LinkedList.h"



LinkedList* createLinkedList() /* Initilises node references to NULL and count to 0 and returns the list*/
{
    LinkedList* list;
    
    list = (LinkedList*)malloc(sizeof(LinkedList));
    (*list).head = NULL;
    (*list).tail = NULL;
    (*list).count = 0;
    
    return list;
}



ListNode* createListNode(void* value) /* Creates a node with the specified value */
{
    ListNode* newNode;

    newNode = (ListNode*)malloc(sizeof(ListNode));
    
    newNode->value = value;
    newNode->next = NULL;
    newNode->prev = NULL;
    
    return newNode;
}


void insertFirst(LinkedList* list, void* value) /* Creates a node and places at the start of the list */
{
    ListNode* newNode = createListNode(value);
    if (isEmpty(list)==1) /*empty list*/
    {
        list->head = newNode;
        list->tail = newNode;
    }
    else /*one-item/multi-item list*/
    {
        newNode->next = list->head;
        list->head->prev = newNode; 
        list->head = newNode;
    }
    list->count++;
}

void insertLast(LinkedList* list, void* value) /* Creates a node and places at the end of the list */
{
    ListNode* newNode = createListNode(value);
    if (isEmpty(list)==1) /*empty list*/
    {
        list->tail = newNode;
        list->head = newNode;
    }
    else /*one-item/multi-item list*/
    {
        newNode->prev = list->tail;
        list->tail->next = newNode; 
        list->tail = newNode;
    }
    list->count++;
}

void* removeFirst(LinkedList* list) /* Removes the first item in the list and returns it's value */
/* calling function MUST free value when done */
{
    void* value = NULL;
    if (!isEmpty(list))
    {
        ListNode* temp = list->head;
        value = temp->value;
        
        if (list->head == list->tail) /*one-item list*/
        {
            list->head = NULL;
            list->tail = NULL;
        }
        else /*multi-item list*/
        {
            list->head = temp->next;
            list->head->prev = NULL;
        }
        list->count--;
        free(temp); 
        temp = NULL;
    }
    return value;
}

void* removeLast(LinkedList* list) /* Removes the last item in the list and returns it's value */
/*calling function must free value*/
{
    void* value = NULL;
    if (!isEmpty(list))
    {
        ListNode* temp = list->tail;
        value = temp->value;
        
        if (list->head == list->tail) /*one-item list*/
        {
            list->head = NULL;
            list->tail = NULL;
        }
        else /*multi-item list*/
        {
            list->tail = temp->prev;
            list->tail->next = NULL;
        }
        list->count--;
        free(temp); 
        temp = NULL;
    }
    return value;
}

void* peekFirst(LinkedList* list) /* Returns the value of the first item in the list */
{
    void* value = NULL;
    if (!isEmpty(list))
    {
        value = list->head->value;
    }
    return value;
}

void* peekLast(LinkedList* list) /* Returns the value of the last item in the list */
{
    void* value = NULL;
    if (!isEmpty(list))
    {
        value = list->tail->value;
    }
    return value;
}

int isEmpty(LinkedList* list) /* Returns whether the list is empty */
{
    int empty = 0;
    if ((*list).head==NULL)
    {
        empty = 1;
    }
    return empty;
}

void printLinkedList(LinkedList* list, PrintFunc printFunc) /* Prints the contents of the list to the terminal */
/* Calling function provides the function that prints each value */
{
    ListNode* cur;
    
    cur = list->head; 
    while (cur!=NULL)
    {
        (*printFunc)(cur->value);
        cur = cur->next;
    }
}

void printLinkedListToFile(LinkedList* list, FilePrintFunc printFunc, FILE* file) /* Prints the contents of the list to the specified file */
/* Calling function provides the function that prints each value */
{
    ListNode* cur;
    
    cur = list->head; 
    while (cur!=NULL)
    {
        (*printFunc)(cur->value,file);
        cur = cur->next;
    }
}

void freeLinkedList(LinkedList* list, FreeFunc freeFunc) /* Frees the list, listnodes and their contents */
/* Calling function provides the function that frees each value */
{
    ListNode* node, *nextNode;
    
    node = list->head;
    
    while (list->count > 0)
    {
        nextNode = node->next;
        freeFunc(node->value);
        free(node);
        list->count--;
        node = nextNode;
    }
    
    free(list);
    list = NULL;
}


