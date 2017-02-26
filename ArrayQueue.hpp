#ifndef ARRAYQUEUE_HPP
#define ARRAYQUEUE_HPP

#include<iostream>
using namespace std;
  //maximum size of the array that will store Queue.

// Creating a class named Queue.
class ArrayQueue{
  private:
	   int* A;
     int* Levels;
     int front, rear;
     int arraySize;
     int size;
  public:
	// Constructor - set front and rear as -1.
	// We are assuming that for an empty Queue, both front and rear will be -1.
    ArrayQueue(int);
    ~ArrayQueue();
    void Reset();
	// To check wheter Queue is empty or not
    bool IsEmpty();

	// To check whether Queue is full or not
    bool IsFull();

	// Inserts an element in queue at rear end
  void Enqueue(int);

	// Removes an element in Queue from front end.
	int Dequeue();
	// Returns element at front of queue.
	int Front();

	void Print();

  int getLevelFront();

  void setLevel(int, int);

  int getSize();

  int getFront();

  int getRear();

  int getLevel(int);

  int getNodeId(int);

  int getIdFront();

  int getFrontPointer();

  int getRearPointer();

  int get_nth_element(int );

  
};

#endif
