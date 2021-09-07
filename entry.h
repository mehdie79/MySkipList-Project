#ifndef ENTRY_H
#define ENTRY_H
#include <string>
#include <sstream>
class Entry
{
private:
	int key;
	std::string value;
public:
	Entry();
	Entry(const int&,const std::string&);
	Entry(const Entry& temp);  // Copy Constructor
	void random();
	int getKey()const;     // Getters
	std::string getValue()const;
	void setKey(const int&);  // Setters
	void setValue(const std::string&);
	std::string toString()const;
};
Entry::Entry()
{
	key=-1;
	value="";
}
Entry::Entry(const int& newKey,const std::string& newValue)
{
	key=newKey;
	value=newValue;
}
Entry::Entry(const Entry& temp)
{
	key=temp.key;
	value=temp.value;
}
void Entry::random()
{
	key=rand() % 100;
	value="";
	for(int i=0;i<3;i++)
	{
		value+='a'+ rand()%26;
	}
}
int Entry::getKey()const
{
	return key;
}
std::string Entry::getValue()const
{
	return value;
}
void Entry::setKey(const int& num)
{
	this->key=num;
}
void Entry::setValue(const std::string& elem)
{
	this->value=elem;
}
std::string Entry::toString()const
{
	std::string dataName="(";
	std::stringstream ss;
	ss << key;
	dataName+=ss.str();
	dataName+=",";
	dataName+=value;
	dataName+=")";
	return dataName;
}
#endif