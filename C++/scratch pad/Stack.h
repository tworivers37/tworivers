#ifndef _STACK_H_
#define _STACK_H_

#include<iostream>


namespace ArrStack{
	template <typename TYPE>
	class ArrayStack{
		protected:
			TYPE * stack;
			int esp;
			int stackSize;
		public:
			ArrayStack(int nSize=100);
			~ArrayStack();
			int getCount() const;
			bool isEmpty() const;
			void RemoveAll();
			TYPE peek() const;
			void push(const TYPE& element);
			TYPE pop();
		public:
			enum Exception{
				STACK_OVERFLOW,
				STACK_UNDERFLOW,
				INVALID_STACK_SIZE,
				MEMALLOC_FAILED,
				STACK_EMPTY
			};
	};

	template <typename TYPE>
	ArrayStack<typename TYPE>::ArrayStack(int nSize=100){
		stack=new TYPE[nSize];
		esp=-1;
		stackSize=nSize;
	}

	template <typename TYPE>
	ArrayStack<typename TYPE>::~ArrayStack(){
		delete[] stack;
	}

	template <typename TYPE>
	int ArrayStack<typename TYPE>::getCount() const{
		return esp+1;
	}

	template <typename TYPE>
	bool ArrayStack<typename TYPE>::isEmpty() const{
		return stackSize==0 ? true:false;
	}

	template <typename TYPE>
	void ArrayStack<typename TYPE>::RemoveAll(){
		esp=-1;
	}

	template <typename TYPE>
	TYPE ArrayStack<typename TYPE>::peek() const{
		if(isEmpty()) throw STACK_EMPTY;
		return stack[esp];
	}

	template <typename TYPE>
	void ArrayStack<typename TYPE>::push(const TYPE& element){
		if(stackSize<=esp+1) throw STACK_OVERFLOW;
		esp++;
		stack[esp]=element;
	}

	template <typename TYPE>
	TYPE ArrayStack<typename TYPE>::pop(){
		if(isEmpty())	 throw STACK_UNDERFLOW;
		esp--;
		return stack[esp];
	}


}

namespace lStack{
	template <typename TYPE>
	struct Node{
		Node*next;
		TYPE data;
	};

	template <typename TYPE>
	class List{
		protected:
			Node<typename TYPE> *esp;
			int stackCount;
		public:
			List();
			~List();
			void RemoveAll();
			bool isEmpty()const{return getStackCount()==0 ? true:false;}
			void incStackCount(){stackCount++;}
			void decStackCount(){stackCount--;}
			int getStackCount()const{return stackCount;}			
			Node<typename TYPE>* getEsp() const{return esp;}
	};

	template <typename TYPE>
	class ListStack{
		protected :
			List<typename TYPE> *list;
		public:
			ListStack();
			~ListStack();
			int getCount()const{ return list->getStackCount(); }
			bool isEmpty()const{ return list->isEmpty(); }
			void RemoveAll(){ list->RemoveAll(); }
			TYPE peek() const;
			void push(const TYPE& element);
			TYPE pop();
		public:
			enum Exception{STACK_OVERFLOW,STACK_UNDERFLOW,STACK_EMPTY};
	};	

	//List-------------
	template <typename TYPE>
	List<typename TYPE>::List(){
		esp=new Node<TYPE>;
		esp->next=NULL;

		stackCount=0;
	}

	template <typename TYPE>
	List<typename TYPE>::~List(){
		delete[] esp;
	}

	template <typename TYPE>
	void List<typename TYPE>::RemoveAll(){
		delete[]esp;
		esp=NULL;
		stackCount=0;
	}
	//-----------------

	//ListStack--------------
	template <typename TYPE>
	ListStack<typename TYPE>::ListStack(){
		list=new List<TYPE>();
	}

	template <typename TYPE>
	ListStack<typename TYPE>::~ListStack(){
		delete list;
	}

	template <typename TYPE>
	void ListStack<typename TYPE>::push(const TYPE& element){
		Node<TYPE> *newNode=new Node<TYPE>;
		newNode->next=NULL;
		newNode->data=element;

		if(isEmpty()) list->getEsp()->next=newNode;
		else{
			newNode->next=list->getEsp()->next;
			list->getEsp()->next=newNode;
		}
		list->incStackCount();
	}

	template <typename TYPE>
	TYPE ListStack<typename TYPE>::pop(){
		if(isEmpty()) throw STACK_UNDERFLOW;

		TYPE tmpData=list->getEsp()->next->data;
		Node<TYPE>*tmpNode=list->getEsp()->next;

		list->getEsp()->next=list->getEsp()->next->next;
		list->decStackCount();

		delete tmpNode;

		return tmpData;
	}

	template <typename TYPE>
	TYPE ListStack<typename TYPE>::peek()const{
		return list->getEsp()->next->data;
	}
	//----------------------

}


#endif