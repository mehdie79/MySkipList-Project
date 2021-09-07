#ifndef QUAD_NODE_H
#define QUAD_NODE_H
#include "entry.h"
#include "skip_list.h"
class QuadNode
{
private:
	Entry* entry;
	QuadNode* prev;
	QuadNode* next;
	QuadNode* below;
	QuadNode* above;
	friend class SkipList;
};
#endif