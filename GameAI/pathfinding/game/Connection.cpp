#include "Node.h"
#include "Connection.h"

Connection::Connection( Node* pFrom, Node* pTo, float cost )
:mFrom(pFrom)
,mTo(pTo)
,cost(cost){}

Connection::~Connection(){}