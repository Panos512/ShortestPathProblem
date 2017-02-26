#include "ArrayQueue.hpp"

ArrayQueue::ArrayQueue(int arraySize){
  front = -1;
  rear = -1;
  size = 0;
  this->arraySize = arraySize;
  this->A = new int[this->arraySize];
  for(int i = 0; i < this->arraySize; i++){
    A[i] = -1;
  }
  this->Levels = new int[this->arraySize];
}

ArrayQueue::~ArrayQueue(){
  delete[] A;
}

void ArrayQueue::Reset(){
  front = -1;
  rear = -1;
}

// To check wheter Queue is empty or not
bool ArrayQueue::IsEmpty(){
    return (front == -1 && rear == -1);
}

// To check whether Queue is full or not
bool ArrayQueue::IsFull(){
    return (rear+1)%this->arraySize == front ? true : false;
}

// Inserts an element in queue at rear end
void ArrayQueue::Enqueue(int x){
  //cout<<"Enqueuing "<<x<<" \n";
  if(IsFull()){
      cout<<"Error: Queue is Full\n";
      return;
  }
  if (IsEmpty()){
       front = rear = 0;
  }else{
      rear = (rear+1)%this->arraySize;
  }
    A[rear] = x;
    size++;
}

// Removes an element in Queue from front end.
int ArrayQueue::Dequeue(){
  if(IsEmpty())
  {
    //cout<<"Error: Queue is Empty\n";
    return -1;
  }
  else if(front == rear )
  {
    int ret = A[front];
    rear = front = -1;
    size--;
    //cout<<"Dequeuing " << ret << endl;

    return ret;
  }
  else
  {
    int ret = A[front];
    front = (front+1)%this->arraySize;
    size--;
    //cout<<"Dequeuing " << ret << endl;

    return ret;
  }
}
// Returns element at front of queue.
int ArrayQueue::Front()
{
if(front == -1)
{
  cout<<"Error: cannot return front from empty queue\n";
  return -1;
}
return A[front];
}
/*
 Printing the elements in queue from front to rear.
 This function is only to test the code.
 This is not a standard function for Queue implementation.
*/
void ArrayQueue::Print()
{
// Finding number of elements in queue
int count = (rear+this->arraySize-front)%this->arraySize + 1;
cout<<"Queue       : ";
for(int i = 0; i <count; i++)
{
  int index = (front+i) % this->arraySize; // Index of element while travesing circularly from front
  cout<<A[index]<<" ";
}
cout<<"\n\n";
}

int ArrayQueue::getLevel(int nodeId){
    return Levels[nodeId];
}

void ArrayQueue::setLevel(int level, int nodeId){
  Levels[nodeId] = level;
};

int ArrayQueue::getSize(){
  return size;
}

int ArrayQueue::getFront(){
  return A[front];
};

int ArrayQueue::getRear(){
  return A[rear];
};



int ArrayQueue::getNodeId(int i){
  return A[i];
};

int ArrayQueue::getIdFront(){
  return A[front];
}

int ArrayQueue::getFrontPointer(){
  return front;
}
int ArrayQueue::getRearPointer(){
  return rear;
}

int ArrayQueue::get_nth_element(int n){
  return A[n];
}
