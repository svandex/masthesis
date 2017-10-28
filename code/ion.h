#include<iostream>
#include<nilibddc.h>
#include<vector>

//functor to display ddcError text
class  ddcChk{
public:
	ddcChk(std::ostream &o = std::cout, char c =' '):os(o),sep(c){}
	void operator()(const int& ddcError) const;
private:
	std::ostream &os;
	char sep;
};

//Initial Processing of TDMS file and PE file, PE for photoelectric encoder.
class ion{
public:
	ion(const char* p, const char* t);
	ion(const ion&i)=delete;
	~ion();

protected:
	DDCFileHandle file;
	unsigned int numOfChannelGroups;
	unsigned int numOfCycle;
	template <unsigned M, unsigned N>
		decltype(auto) getHandle(const unsigned int& M, const unsigned int& N);

private:
	const char* pepath;
	const char* tdmspath;
};

std::ostream& operator<< (std::ostream& os, const ion& i);//Output all properties in format

struct ionAttr{
	
};

//IO reading from TDMS file and writing cycle data to a file
class ioncyc:public ion{
public:
	ioncyc(const ion& i,unsigned int n);
	ioncyc(const ioncyc& i)=delete;
	void writeTo(const char* w);//save data of single cycle for plotting
private:
	unsigned int numCycle;
};

