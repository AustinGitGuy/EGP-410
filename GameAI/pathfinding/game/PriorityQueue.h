//https://stackoverflow.com/questions/16749723/how-i-can-find-value-in-priority-queue (This was going around in the group so people probably have similar things, not sure if they
//credited this or not but this is basically it. A bit of the formatting was changed to keep it nice tho
#pragma once

#include <queue>
#include "Node.h"

template<class T, class Container = std::vector<T>, class Compare = std::less<typename Container::value_type>>class PriorityQueue : public std::priority_queue<T, Container, Compare>{

public:
	typedef typename
	std::priority_queue<T, Container, Compare>::container_type::const_iterator const_iterator;

	//It is just a function that loops through to find the specified node from the function
	const_iterator find(const Node* val) const {
		auto first = this->c.cbegin();
		auto last = this->c.cend();
		while(first != last){
			if ((*first)->GetID() == val->GetID()) return first;
			++first;
		}
		return last;
	}

	//This is just a function to return the end of the queue
	const_iterator end() const{
		auto last = this->c.cend();
		return last;
	}

};