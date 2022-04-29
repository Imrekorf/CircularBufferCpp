// CircularBuffer.hpp
#pragma once

#include <list>

template<typename T>
struct CircularBufferNode{
	T val;
	size_t max_size;
	size_t ID = 0;
	CircularBufferNode* next = nullptr;
	CircularBufferNode* prev = nullptr;
	CircularBufferNode* end  = nullptr; // only start has a reference to the last value

	CircularBufferNode(size_t max_size) : max_size(max_size), end((CircularBufferNode*)-1){}

	T operator[](int i) const {
		CircularBufferNode* ref = this;
		for(int j = 0; j < i; j++){
			if(ref->next == nullptr)
				throw(std::out_of_range(std::to_string(i) + " out of range"));
			ref = ref->next;
		}
		return ref->val;
	}

	size_t size(){
		if(end != nullptr)
			return (this->ID - this->end->ID) + 1;
		else
			return 0;
	}

	size_t capacity(){return max_size;}

	static void add(CircularBufferNode<T>** start, T val){
		if((*start)->end == (CircularBufferNode*)-1){ // handle first node
			(*start)->val = val;
			(*start)->end = (*start);
			return;
		}
		CircularBufferNode<T>* node = new CircularBufferNode<T>((*start)->max_size); 	// new start;
		// do linkage
		(*start)->prev = node;				// add link from old start to new node
		node->next = *start;				// add link from new start to old start
		node->end = (*start)->end; 			// set the end link to the new start
		(*start)->end = nullptr;			// indicate that this is not the start node
		

		// keep track of values
		node->val = val;					// set value
		node->ID = (*start)->ID+1;			// get ID;

		// make sure the buffer is not too big
		while(node->size() > node->max_size){		// remove any old nodes
			CircularBufferNode<T>* old_end = node->end;
			node->end = old_end->prev;			// move end back by 1
			node->end->next = nullptr;			// destroy link
			delete old_end;						// free end node
		}

		*start = node;						// move start
	}

	static void freeCircularBuffer(CircularBufferNode<T>** start){
		if(!start){	return;	} // nullptr save guard
		if(*start && (*start)->end){ // nullptr & check if this node is actually the start
			CircularBufferNode<T>* current = *start;
			CircularBufferNode<T>* next = (*start)->next;
			while(next){
				delete current;	// delete current node
				current = next; // move to next
				next = current->next; // save link to next node
			}
			start = nullptr;
		}
		else{
			throw(std::runtime_error("Not the start of the circular buffer"));
		}
	}
};
