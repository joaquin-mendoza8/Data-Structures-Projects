#include <iostream>

using namespace std;

// class for making nodes
class Node {
public:

    // default node elements
    int data;
    Node* next;
    Node* prev;

    // node constructor
    Node(int val){

        next = nullptr;
        prev = nullptr;
        data = val;

    }
};

// staque implementation
// top is the first node, bottom is last node
class Staque {
private:

    // Staque size/pointers
    Node* top;
    Node* bottom;
    int size;
    Node* nextPop;

public:

    // default staque constructor
    Staque (){

        // set default field values
        top = nullptr;
        bottom = nullptr;
        size = 0;
        nextPop = nullptr;

    }

    // copy constructor
    Staque (const Staque& other){

        // set default field values
        top = nullptr;
        bottom = nullptr;
        size = 0;
        nextPop = nullptr;

        // populate this staque w/ other staque
        Node* tempNode = other.top;
        while (tempNode != nullptr){

            push(tempNode->data);

            // move temp.next forward
            tempNode = tempNode->next;

        }

        // update this's field values 
        top = other.top;
        bottom = other.bottom;
        size = other.size;
        nextPop = other.nextPop;

    }

    // staque destructor
    ~Staque() {

        // while not empty, remove nodes
        while(!isEmpty()){
            pop();
        }

    }

    // get size of staque
    int getSize() {

        return size;

    }

    // check if staque empty
    bool isEmpty() {

        // return true/false if empty 
        return ((top==nullptr) && (bottom==nullptr));

    }

    // print all nodes in staque
    void display() {

        // Node to store current node
        Node* tempNode = top;

        // prompt user if staque empty
        if(isEmpty())
            cout << "Staque is empty" << endl;
        
        // iterate through linked-list
        while(tempNode != nullptr){

            // print values
            cout << tempNode->data << ' ';

            // update tempNode
            tempNode = tempNode->next;

        }

        cout << endl;

    }

    // add nodes to staque
    // even nodes pushed on top/odd on bottom
    void push(int value) {

        // type checking
        if(typeid(value) != typeid(int))
            throw invalid_argument("Type must be integer for push()");

        // temporary nodes
        Node* tempNode = new Node(value);
        Node* tempPop = new Node(value);
        
        if (isEmpty()) { // first node to push

            top = tempNode;
            bottom = tempNode;

        } else if (value % 2 == 0) { // push even node

            tempNode->next = top;
            top->prev = tempNode;
            top = tempNode;

        } else if (value % 2 != 0){ // push odd node

            tempNode->prev = bottom;
            bottom->next = tempNode;
            bottom = tempNode;
            
        }

        if(top == bottom){ // if first node, update nextPop

            nextPop = tempPop;

        } else { // update nextPop and its pointers

            nextPop->next = tempPop;
            tempPop->prev = nextPop;
            nextPop = tempPop;
            nextPop->next = nullptr;

        }

        size++;
        

    }

    void pushBack(int value){

        // check parameter type
        if(typeid(value) != typeid(int))
            throw invalid_argument("Type must be integer for push()");

        Node* tempNode = new Node(value);
        
        if (isEmpty()) { // first node to push

            top = tempNode;
            bottom = top;
            
        } else { // push to bottom

            bottom->next = tempNode;
            tempNode->prev = bottom;
            bottom = tempNode;
            bottom->next = nullptr;

        }

        size++;
    }

    // remove nodes from staque
    int pop() {

        // error of popping empty staque
        if (isEmpty())
            throw runtime_error("Staque is empty");

        // temp values
        Node* tempNode;
        int returnVal;

        if (bottom == top) { // one node

            tempNode = bottom;
            bottom = nullptr;
            top = nullptr;
            nextPop = nullptr;

        } else if ((nextPop != nullptr) && (nextPop->data%2 == 0)) { // pop from top

            tempNode = top;
            top = top->next;
            top->prev = nullptr;

        } else { // pop from bottom

            tempNode = bottom;
            bottom = bottom->prev;
            bottom->next = nullptr;

        }

        if(top == nullptr){ // if last pop, null nextPop

            nextPop = nullptr;

        } else if(nextPop != nullptr){ // update nextPop val

            nextPop = nextPop->prev;

        }

        if(tempNode == nullptr){ // extract popped val/deallocate

            returnVal = tempNode->data;
            delete tempNode;

        }

        size--;
        return returnVal;
    }

    // pops by value
    int pop(int value) {

        // throws error if value isn't type int
        if(typeid(value) != typeid(int))
            throw invalid_argument("Value must be an integer");

        // prompt user that staque is empty
        if(isEmpty())
            throw out_of_range("pop(value) ERROR: Staque is empty");

        // temp values
        Node* tempNode;
        int returnVal;
        
        // begin search at top
        tempNode = top;

        // search thru staque
        while(tempNode->data != value){
            
            // move to next node
            tempNode = tempNode->next;

            // check if end of staque
            if(tempNode == nullptr){
                cout << "Value not in staque" << endl;
                return -1;
            }
        }

        if (size == 1) { // one node left

            bottom = nullptr;
            top = nullptr;

        } else if(tempNode == top){ // pop from top

            top = top->next;
            top->prev = nullptr;
           
        } else if(tempNode == bottom){ // pop from bottom
            
            bottom = bottom->prev;
            bottom->next = nullptr;

        } else { // pop between nodes

            tempNode->prev->next = tempNode->next;
            tempNode->next->prev = tempNode->prev;

        }

        if(top == nullptr){ // if last pop, update

            nextPop = nullptr;

        } else if(nextPop != nullptr){ // update nextPop

            nextPop = nextPop->prev;

        }

        // update/deallocate
        value = tempNode->data;
        delete tempNode;
        size--;

        // return popped node's value
        return value;
    }

    // pops from both ends and returns sum
    // of the popped nodes
    int popEnds(){

        // prompt user that staque is empty
        if(isEmpty())
            throw out_of_range("pop(value) ERROR: Staque is empty");

        // temp values
        Node* tempTop;
        Node* tempBottom;
        int returnVal;

        if (size == 1) { // one node left
            tempBottom = bottom;

            bottom = nullptr;
            top = nullptr;

            size--;
        } else if(size == 2) { // two nodes
            tempTop = top;
            tempBottom = bottom;

            top = nullptr;
            bottom = nullptr;

            size-=2;
        } else { // many nodes
            tempTop = top;
            tempBottom = bottom;

            top = top->next;
            bottom = bottom->prev;

            top->prev = nullptr;
            bottom->next = nullptr;

            size-=2;
        }

        // update/deallocate
        returnVal = tempTop->data + tempBottom->data;
        delete tempTop;
        delete tempBottom;

        // return popped node's value
        return returnVal;

    }

    // overloading assignment operator 
    void operator=(const Staque& other) {

        // break if other == this
        if(&other == this){

            // prompt user that staque's equal each other
            cout << "Can't assign staque to itself" << endl;
            return;

        }
            
        // delete current staque data
        this->~Staque();
        
        // update staque pointers/size
        top = nullptr;
        bottom = nullptr;
        size = 0;

        // other linked-list's top
        Node* tempNode = other.top;

        // populates this(nodes) with other(nodes)
        while(tempNode != nullptr){

            // push data from other to this
            pushBack(tempNode->data);

            // update temp node
            tempNode = tempNode->next;

        }

        // update values
        swap(top, this->top);
        swap(bottom, this->bottom);
        swap(size, this->size);

    }
};

int main(){
    
    // checks pop() and pop(int value)
    Staque s1;

    s1.push(1);
    s1.push(2);
    s1.push(3);
    s1.push(4);
    s1.push(5);

    cout << "\nPushing elements: 1 2 3 4 5 to s1\ns1: ";
    s1.display();

    s1.pop();
    s1.pop(2);
    cout << "\nAfter popping two values (one by value=2):\ns1: ";
    s1.display();

    // checks popping all nodes
    Staque s2;

    s2.push(2);
    s2.push(3);
    s2.push(1);
    s2.push(5);

    cout << "\nPushing elements: 2 3 1 5 to s2\ns2: ";
    s2.display();
    s2.pop();
    s2.pop();
    s2.pop();
    s2.pop();
    cout << "\nAfter popping all nodes:\ns2: ";
    s2.display();

    // checks popEnds()
    Staque s3;

    s3.push(3);
    s3.push(6);
    s3.push(5);
    s3.push(2);

    cout << "\nPushing elements: 3 6 5 2 to s3\ns3: ";
    s3.display();

    int returnVal = s3.popEnds();
    cout << "\nAfter popping end values:\ns3: ";
    s3.display();
    cout << "s3.popEnds() returns = " << returnVal << endl;

    // checks operator overloading
    Staque s4;

    s4 = s3;

    cout << "\nAfter calling 's4=s3:\ns4: ";
    s4.display();

    // checks copy constructor
    Staque s5(s4);

    cout << "\nAfter calling 'Staque s5(s4):\ns5: ";
    s5.display();

    // checks destructor
    cout << "\nAfter calling 's5.~Staque()':\ns5: ";
    s5.~Staque();
    s5.display();


    return 0;
};