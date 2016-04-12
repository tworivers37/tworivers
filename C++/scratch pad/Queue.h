#ifndef _QUEUE_H_
#define _QUEUE_H_

namespace CircularQueue{
	template <typename TYPE>
	class CirQueue{
		protected:
			TYPE* queue;
			int front;
			int rear;
			int nCount;
			int nSize;
		public:
			CirQueue(int nSize=100);
			~CirQueue();
			int getCount()const{return nCount;}
			void RemoveAll();
			TYPE getFront()const{return front;}
			TYPE getRear()const{return rear;}
			void enqueue(const TYPE& newElement);
			TYPE dequeue();
		public:
			enum Exception{
				QUEUE_OVERFLOW,
				QUEUE_UNDERFLOW,
				INVALID_QUEUE_SIZE,
				MEMALLOC_FAILED,
				QUEUE_EMPTY
			};
	};

	template <typename TYPE>
	CirQueue<typename TYPE>::CirQueue(int _nSize=100):nSize(_nSize){
		queue=new TYPE[nSize];
		nCount=front=rear=0;
	}

	template <typename TYPE>
	CirQueue<typename TYPE>::~CirQueue(){
		delete queue;
	}

	template <typename TYPE>
	void CirQueue<typename TYPE>::RemoveAll(){
		front=rear=0;
	}

	template <typename TYPE>
	void CirQueue<typename TYPE>::enqueue(const TYPE& newElement){
		if(front==(rear+1)%nSize) throw QUEUE_OVERFLOW;
		rear=(rear+1)%nSize;
		nCount++;
		queue[rear]=newElement;
	}

	template <typename TYPE>
	TYPE CirQueue<typename TYPE>::dequeue(){
		if(front==rear) throw QUEUE_UNDERFLOW;
		front=(front+1)%nSize;
		TYPE tmp(queue[front]);
		nCount--;
		return tmp;
	}

}

namespace ListQueue{
	template <typename TYPE>
	struct Node{
		TYPE data;
		Node*pNext;
	};

	template <typename TYPE>
	class LQueue{
		protected:
			Node<TYPE>* front;
			Node<TYPE>* rear;
			int nCount;
		public:
			LQueue();
			~LQueue();
			int getCount()const;
			bool isEmpty()const;
			void RemoveAll();

			TYPE getFront()const;
			TYPE getRear()const;

			void enqueue(const TYPE& newElement);
			TYPE dequeue();
		public:
			enum Exception{ QUEUE_OVERFLOW,
							QUEUE_UNDERFLOW,
							QUEUE_EMPTY};
	};

	template <typename TYPE>
	LQueue<typename TYPE>::LQueue(){
		front=new Node<TYPE>;
		rear=new Node<TYPE>;

		front->data=0;
		front->pNext=NULL;

		rear->data=0;
		rear->pNext=NULL;

		nCount=0;
	}

	template <typename TYPE>
	LQueue<typename TYPE>::~LQueue(){
		delete front;
		delete rear;
	}

	template <typename TYPE>
	int LQueue<typename TYPE>::getCount()const{
		return nCount;
	}

	template <typename TYPE>
	bool LQueue<typename TYPE>::isEmpty()const{
		return getCount()==0;
	}

	template <typename TYPE>
	void LQueue<typename TYPE>::RemoveAll(){
		delete front->pNext;
		delete rear->pNext;
		
		front->pNext=NULL;
		rear->pNext=NULL;
	
		nCount=0;
	}

	template <typename TYPE>
	void LQueue<typename TYPE>::enqueue(const TYPE& element){
		Node<TYPE> *newNode=new Node<TYPE>;
		newNode->data=element;
		newNode->pNext=NULL;

		if(front->pNext==NULL)front->pNext=newNode;
		else rear->pNext->pNext=newNode;
		rear->pNext=newNode;
		nCount++;
	}

	template <typename TYPE>
	TYPE LQueue<typename TYPE>::dequeue(){
		if(isEmpty()) throw QUEUE_UNDERFLOW;
		
		Node<TYPE> *tmp=front->pNext;
		TYPE tmpData=front->pNext->data;
		
		front->pNext=front->pNext->pNext;

		delete tmp;
		nCount--;
		return tmpData;
	}
}


#endif