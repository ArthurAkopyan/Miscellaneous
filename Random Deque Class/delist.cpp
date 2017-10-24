//Written by Arthur Akopyan

#include "delist.h"
#include <iostream>
using namespace std;

DEList::DEList()
{
  head = NULL;
  tail = NULL;
}
  // Destructor to clean-up memory of current list
DEList::~DEList()
{
  //grab head
  //while loop through till we at tail or next = NULL
  DEItem* carry;
  DEItem* temp = head;
  while(temp != NULL)
  {
    carry = temp->next;
    temp->next = NULL;
    temp->prev = NULL;
    
    delete temp;
    temp = carry;
  }
}
  // returns a Boolean 'true' if the list is empty
bool DEList::empty()
{
  return (head == NULL);
}
  // returns number of items in the list
int DEList::size()
{
  int counter = 0;
  DEItem* temp = head;
  //Loops through till the head is null
  while(temp != NULL)
  {
    temp = temp->next;
    counter++; //the number of times we loop
  }
  return counter;
}
  // returns front item or -1 if empty list
int DEList::front()
{
  if(head != NULL) //returns head value
  {
    return head->val;
  }
  else
  {
    return -1;
  }
}
  // returns back item or -1 if empty list
int DEList::back()
{
  if(tail != NULL) //returns tail value
  {
    return tail->val;
  }
  else
  {
    return -1;
  }
}
  // Adds a new integer to the front of the list
void DEList::push_front(int new_val)
{
  if(head == NULL || tail == NULL)
  {
    //Creates head node
    head = new DEItem;
    head->val = new_val;
    head->next = NULL;
    head->prev = NULL;
    //Set tail node
    tail = head;
  }
  else
  {
    //Creates new node and points head to it
    DEItem* temp = new DEItem;
    temp->val = new_val;
    temp->next = head;
    temp->prev = NULL;
    head->prev = temp;
    head = temp;
  }
}
  // Adds a new integer to the back of the list
void DEList::push_back(int new_val)
{
  if(tail == NULL || head == NULL)
  {
    //Same as pushing front on empty list
    head = new DEItem;
    head->val = new_val;
    head->next = NULL;
    head->prev = NULL;
    tail = head;
  }
  else
  {
    //creates new node and sets tail to it
    DEItem* temp = new DEItem;
    temp->val = new_val;
    temp->next = NULL;
    temp->prev = tail;
    tail->next = temp;
    tail = temp;
  }
}
  // Removes the front item of the list (if it exists)
void DEList::pop_front()
{
  //if there is an item to pop back
  if(head != NULL)
  {
    DEItem* temp = NULL; //By default previous node is null
    if(head->next != NULL)
    {
      temp = head->next; //grabs next node
      temp->prev = NULL;
    }
    else
    {
      tail = NULL; //Makes sure that we delete tail when
                   //we pop last node
    }
    head->next = NULL; 
    head->prev = NULL;
    delete head; //delete stuff
    head = temp;
    if(temp == NULL)  
    {
      delete temp;
    }
  }

}
  // Removes the back item of the list (if it exists)
  // just look at pop_front from comments
void DEList::pop_back()
{
  if(tail != NULL)
  {
    DEItem* temp = NULL;
    if(tail->prev != NULL)
    {
      temp = tail->prev;
      temp->next = NULL;
    }
    else
    {
      head = NULL;//Makes sure that we delete head when
                   //we pop last node
    }
    //tail->prev = NULL;
    tail->prev = NULL;
    tail->next = NULL;
    delete tail;
    tail = temp;
  }
}