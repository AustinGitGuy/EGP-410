#include "Path.h"

Path::Path(){}

Path::~Path(){}

Node* Path::PeekNode(int index) const {
	if((unsigned int)index < nodes.size()){
		return nodes[index];
	}
	else {
		return NULL;
	}
}

Node* Path::PeekNextNode() const {
	if(nodes.size() > 0){
		return nodes.back();
	}
	else {
		return NULL;
	}
}

Node* Path::GetAndRemoveNextNode(){
	if(nodes.size() > 0){
		Node* pNode = nodes.back();
		nodes.pop_back();
		return pNode;
	}
	else {
		return NULL;
	}
}

void Path::AddNode(Node* pNode){
	nodes.push_back(pNode);
}

bool Path::ContainsNode(Node* pNode){
	bool retVal = false;

	for(unsigned int i=0; i<nodes.size(); i++){
		if(nodes[i] == pNode){
			retVal = true;
			break;
		}
	}
	return retVal;
}
