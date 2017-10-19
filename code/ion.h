#include<iostream>
#include<nilibddc.h>

struct{
	unsigned int numberOfProperties;
	char **propertyNames;//Property Names in TDMS file 
}tdmsAttr;

class ion{//Initial Processing of TDMS file and PE file, PE for photoelectric encoder.
public:
	ion(const char* f, const char* t):pepath(f),tdmspath(t){ddcError=0;};
	ion(const ion&i)=delete;
protected:
	DDCFileHandle file;
private:
	const char* pepath;
	const char* tdmspath;
	int ddcError;
};

std::ostream& operator<< (std::ostream& os, const ion& i);//Output all properties in format

struct{
	
}ionAttr;

//IO reading from TDMS file and writing cycle data to a file
class ioncyc:public ion{
public:
	ioncyc(const ion& i,unsigned int n);
	ioncyc(const ioncyc& i)=delete;
	void writeTo(const char* w);//save data of single cycle for plotting
private:
	unsigned int numCycle;
};
