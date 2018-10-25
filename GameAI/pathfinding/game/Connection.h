#pragma once

#include <Trackable.h>
class Node;

class Connection:public Trackable {
public:
	Connection( Node* pFrom, Node* pTo, float cost );
	~Connection();

	inline Node* GetFromNode() const {return mFrom;};
	inline Node* GetToNode() const {return mTo;};
	inline float GetWeight() const {return cost;};

private:
	Node* mFrom;
	Node* mTo;
	float cost;
};