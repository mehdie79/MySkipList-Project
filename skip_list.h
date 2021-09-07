#ifndef SKIP_LIST_H
#define SKIP_LIST_H
#include "entry.h"
#include <string>
#include <iostream>
#include <climits>
#include "quad_node.h"
class RunTimeException
{
private:
	std::string message;
public:
	RunTimeException(const std::string& error): message(error){}
	std::string getMessage()
	{
		return message;
	}
};
class NonExistentEntry: public RunTimeException
{
public:
	NonExistentEntry(const std::string& error): RunTimeException(error) {}
};
class SkipList
{
private:
	QuadNode* header;
	QuadNode* trailer;
	int level;
	int sizeSkipList;
private:
	QuadNode* insertAfterAbove(QuadNode* start,QuadNode*belowNode,const int& key,const std::string& value); // It inserts a new QuadNode in SkipList with indicated key and value after the QuadNode* start and above the belowNode pointer     
	QuadNode* findPosition(const int& key)const;  // It finds the position of the QuadNode with indicated key
	int tossCoin()const; // zero for "head" and one for "tail"
public:
	static const Entry END;    // end entry
	SkipList();
	~SkipList();
	const Entry& find(const int& key)const; // if the map M has an entry with key k, return it. Else, return a reference to a special Entry end.
	const Entry& greaterEntry(const int& key)const; // finds the entry with the lowest key that is greater than k.
	const Entry& lessEntry(const int& key)const; // finds the entry with the greatest key that is less than k.
	void put(const int& key,const std::string& value); // if there is no entry with key k, insert entry (k, v),and otherwise set the entry’s value to v.
	void erase(const int& key)throw(NonExistentEntry); // if the map M has an entry with key k, remove it from M. Otherwise give an error.
	int size()const; // number of elements in the skip list
	bool empty()const; // is size == 0
	void print()const;
};
const Entry SkipList::END=Entry(-1,"END");
SkipList::SkipList()
{
	sizeSkipList=0;
	level=0;
	header= new QuadNode;
	trailer= new QuadNode;
	header->next=trailer;
	trailer->prev=header;
	header->prev=nullptr;
	trailer->next=nullptr;
	header->above=nullptr;
	header->below=nullptr;
	trailer->above=nullptr;
	trailer->below=nullptr;
	header->entry=new Entry;
	header->entry->setValue("-INF");
	header->entry->setKey(INT_MIN);
	trailer->entry=new Entry;
	trailer->entry->setValue("+INF");
	trailer->entry->setKey(INT_MAX);
}
SkipList::~SkipList()
{
	QuadNode* old=header;
	header=header->below;
	while(level > 0)
	{
		QuadNode* traverse=old;
		while(traverse!=nullptr)
		{
			QuadNode* oldTemp=traverse;
			Entry* old_entry= oldTemp->entry;
			traverse=traverse->next;
			delete oldTemp;
			delete old_entry;
		}
		level--;
		old=header;
		header=header->below;
	}
	while(header!=nullptr)
	{
		QuadNode* temp=header;
		Entry* old_entry= header->entry;
		header=header->next;
		delete temp;
		delete old_entry;
	}
	header=nullptr;
	trailer=nullptr;
	level=-1;
	this->sizeSkipList=0;
}
QuadNode* SkipList::insertAfterAbove(QuadNode* start,QuadNode*belowNode,const int& key,const std::string& value)
{
	QuadNode* temp=new QuadNode;
	temp->entry= new Entry;
	temp->entry->setKey(key);
	temp->entry->setValue(value);
	if(start==nullptr)
	{
		temp->next=nullptr;
		temp->prev=nullptr;
	}
	else
	{
		if(start->next==nullptr)
		{
			start->next=temp;
			temp->prev=start;
			temp->next=nullptr;
		}
		else
		{
			temp->next=start->next;
			start->next->prev=temp;
			start->next=temp;
			temp->prev=start;
		}
	}
	if(belowNode==nullptr)
	{
		temp->below=nullptr;
		temp->above=nullptr;
	}
	else
	{
		temp->above=nullptr;
		temp->below=belowNode;
		belowNode->above=temp;
	}
	return temp;
}
const Entry& SkipList::find(const int& key)  const
{
	QuadNode* temp=header;
	while(temp->below!=nullptr)
	{
		temp=temp->below;
		while(temp->next->entry->getKey() <= key)
		{
			temp=temp->next;
		}
	}
	if(temp->entry->getKey()==key)
	{
		Entry* founded_entry= temp->entry; 
		return *founded_entry;
	}
	else
	{
		return END;
	}
}	
const Entry& SkipList::greaterEntry(const int& key) const
{
	QuadNode* temp=header;
	while(temp->below!=nullptr)
	{
		temp=temp->below;
		while(temp->next->entry->getKey() <= key)
		{
			temp=temp->next;
		}
	}
	temp=temp->next;
	Entry* founded_entry= temp->entry; 
	return *founded_entry;
}
const Entry& SkipList::lessEntry(const int& key) const
{
	QuadNode* temp=header;
	while(temp->below!=nullptr)
	{
		temp=temp->below;
		while(temp->next->entry->getKey() < key)
		{
			temp=temp->next;
		}
	}
	Entry* founded_entry= temp->entry; 
	return *founded_entry;
}
int SkipList::tossCoin()const
{
	int random=rand()%2;
	return random;
}
QuadNode* SkipList::findPosition(const int& key) const
{
	QuadNode* temp=header;
	while(temp->below!=nullptr)
	{
		temp=temp->below;
		while(temp->next->entry->getKey() <= key)
		{
			temp=temp->next;
		}
	}
	return temp;
}
void SkipList::put(const int& key, const std::string& value) 
{
	QuadNode* position;
	QuadNode* positionInsertion;
	if(empty())
	{
		position=header;
		QuadNode* nextPtr=header->next;
		positionInsertion=this->insertAfterAbove(header,nullptr,key,value);
		header=this->insertAfterAbove(nullptr,header,INT_MIN,"-INF");
		this->insertAfterAbove(header,nextPtr,INT_MAX,"+INF");
		level++;
		this->sizeSkipList++;
	}
	else 
	{
		QuadNode* temp=this->findPosition(key);
		position=temp;
		if(key==temp->entry->getKey())
		{
			temp->entry->setValue(value);
			positionInsertion=temp;
		}
		else 
		{
			positionInsertion=this->insertAfterAbove(temp,nullptr,key,value);
			this->sizeSkipList++;
		}
	}
	int i=0;
	while(this->tossCoin()==0)     // while coin the out come of the tossed coin was "head"
	{
		i=i+1;
		if(i>=level)
		{
			level=level+1;
			QuadNode* temp=header->next;
			header=this->insertAfterAbove(nullptr,header,INT_MIN,"-INF");
			this->insertAfterAbove(header,temp,INT_MAX,"+INF");
		}
		while(position->above==nullptr)
		{
			position=position->prev;
		}
		position=position->above;
		if(position->entry->getKey()==key)
		{
			position->entry->setValue(value);
			positionInsertion=position;
		}
		else 
		{
			positionInsertion=this->insertAfterAbove(position,positionInsertion,key,value);
		}
	}
}
void SkipList::erase(const int& key) throw(NonExistentEntry)
{
	Entry e=this->find(key);
	if(e.getKey()==END.getKey())
	{
		throw(NonExistentEntry("Error! the entry with the mentioned key does not exist"));
	}
	else
	{
		QuadNode* temp=header;
		while(temp->below!=nullptr)
		{
			temp=temp->below;
			while(temp->next->entry->getKey() <=key)
			{
				temp=temp->next;
			}
			if(temp->entry->getKey()==key)
			{
				break;
			}
		}
		while(temp!=nullptr)
		{
			QuadNode* cur=temp;
			QuadNode* nextPtr=cur->next;
			QuadNode* prevPtr=cur->prev;
			prevPtr->next=nextPtr;
			nextPtr->prev=prevPtr;
			temp=temp->below;
			Entry* old_entry= cur->entry;
			delete cur;
			delete old_entry;
		}
		QuadNode* check=header;
		while(check->below!=nullptr)
		{
			QuadNode* temp=check->below;
			if(temp->next->entry->getKey()==INT_MAX)
			{
				header=header->below;
				level--;
				QuadNode* temp_old=check;
				check=check->below;
				while(temp_old!=nullptr)
				{
					QuadNode* cur=temp_old;
					Entry* old_entry= cur->entry;
					temp_old=temp_old->next;
					delete cur;
					delete old_entry;
				}
			}
			else
			{
				break;
			}
		}
		this->sizeSkipList--;
	}
}
int SkipList::size()const
{
	return sizeSkipList;
}
bool SkipList::empty()const
{
	return sizeSkipList==0;
}
void SkipList::print()const
{
	QuadNode* temp=header;
	QuadNode* firstLevel=header;
	int i=level;
	while(i>0)
	{
		firstLevel=firstLevel->below;
		i--;
	}
	while(temp!=nullptr)
	{
		int spaces=this->sizeSkipList;
		std::cout << "-inf";
		QuadNode* tempFirstLevel=firstLevel->next;
		QuadNode* cur=temp;
		temp=temp->below;
		cur=cur->next;
		while(spaces>0)
		{
			std::cout << "--";
			if(cur->entry->getKey()!=tempFirstLevel->entry->getKey())
			{
				if(tempFirstLevel->entry->getKey()%10==tempFirstLevel->entry->getKey())
				{
					std::cout << "-";
				}
				else
				{
					std::cout << "--";
				}
				spaces--;
				tempFirstLevel=tempFirstLevel->next;
			}
			else
			{
				std:: cout << cur->entry->getKey();
				if(cur->next!=nullptr)
				{
					cur=cur->next;
				}
				tempFirstLevel=tempFirstLevel->next;
				spaces--;
			}
		}
		std::cout << "--inf" << std::endl; 
	}
}
#endif