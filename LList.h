#ifndef LLIST_H
#define LLIST_H

#include <iostream>
#include <cstdlib>
#include "utils.h"

//Singly linked list node
template <typename E> class Link {
    private:
        static Link<E>* freelist;         //Reference to freelist head
    public: 
        E element;                        //Value for this node
        Link *next;                       //Pointer to next node in list

        //Constructors
        Link(const E& elemval, Link* nextval = nullptr)
            { element = elemval; next = nextval; }
        Link(Link* nextval = nullptr) { next = nextval; }

        void* operator new(size_t) {                      //Overload new operator 
            if(freelist == nullptr) return ::new Link<E>; //Create space
            Link<E>* temp = freelist;                     //Can take from freelist
            freelist = freelist -> next;
            return temp;                                  //Return the link
        }

        void operator delete(void* ptr) {                 //Overloaded delete operator
            ((Link<E>*) ptr)->next = freelist;            //Put on freelist
            freelist = (Link<E>*) ptr;
        }             
};

//The freelist head pointer is actually created here
template <typename E> 
Link<E>* Link<E>::freelist = nullptr;

//Linked list implementation
template <typename E> class LList {
    private:
        Link<E>* head;                //Pointer to list header
        Link<E>* tail;                //Pointer to last element
        Link<E>* curr;                 //Pointer to current element
        int cnt;                      //Size of the list

        void init() {                //Initialization helper method
            curr = tail = head = new Link<E>;
            cnt = 0;
        }

        void removeall() {            //Return link nodes to free store
            while(head != nullptr) {
                curr = head;
                head = head->next;
                delete curr;
            }
        }

        public:
            LList(int size = defaultSize) { init(); }    //Constructor
            ~LList() { removeall(); }                    //Destructor
            void print() const;                          //Print list content
            void clear() { removeall(); init(); }        //Clear list

            //Insert "it" at current position
            void insert(const E& it) {
                curr->next = new Link<E> (it, curr->next);
                if(tail == curr) tail = curr->next;      //New tail
                cnt++;
            }

            void append(const E& it) {                   //Append "it" to list
                tail = tail->next = new Link<E> (it, nullptr);
                cnt++;
            }

            //Remove and return current element
            E remove() {
                Assert(curr->next != nullptr, "No element!");  
                E it = curr->next->element;          //Remember value 
                Link<E>* ltemp = curr->next;          //Remember link node
                if(tail == curr->next) tail = curr;    //Reset tail 
                curr->next = curr->next->next;           //Remove from list
                delete ltemp;                            //Reclaim space
                cnt--;                                   //Decrement the count
                return it;
            }

            void moveToStart()                           //Place curr at list start
                { curr = head; }

            void moveToEnd()                             //Place curr at list end
                { curr = tail; }
            
            //Move curr one step left; no change if aready at front
            void prev() {
                if(curr == head) return;
                Link<E>* temp = head;
                //March down list until we find the previous element
                while(temp->next != curr) temp = temp->next;
                curr = temp;
            }

            //Move curr one step right; no change if already at end
            void next() {
                if(curr != tail) curr = curr->next;
            }

            int length() const { return cnt; }            //Return list length

            //Return the position of the current element
            int currPos() const {
                Link<E>* temp = head;
                int i;
                for(i = 0; curr != temp; i++)
                    temp = temp->next;
                return i; 
            }

            //Move down list to "pos" position
            void moveToPos(int pos) {
                Assert((pos >= 0) && (pos <= cnt), "Position out of range");
                curr = head;
                for(int i = 0; i < pos; i++) curr = curr->next;
            }

            const E& getValue() const {
                Assert(curr->next != nullptr, "No value!");
                return curr->next->element;
            }
};

template <typename E> 
void LList<E>::print() const {
    Link<E>* temp = head->next;
    while (temp != nullptr) {
        std::cout << temp->element << "\n";
        temp = temp->next;
    }
};

#endif