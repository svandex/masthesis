#include<iostream>
#include<nilibddc.h>

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
	ion(const ion& )=delete;
	~ion();
	void showProperty() const;
	friend std::ostream& operator<< (std::ostream& os, const ion& i);//Output all properties of one channel

protected:
	DDCFileHandle file;
	unsigned int numOfChannelGroups;
	unsigned int numOfCycle;
	template <unsigned M, unsigned N>
		decltype(auto) getHandle();//channel group handle or channel handle, for data aquisition

	void split(unsigned int& numDataStart, unsigned int ) const;
	//Determine the start number of data, used as an parameter to the function of data aquisition
	//Use A-signal and Z-signal to determine, make sure the method has enough epsilong

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
	ioncyc(const ion& ionT,unsigned int n);
	ioncyc(const ioncyc&)=delete;
	void writeTo(const char* w);//save data of single cycle for plotting
private:
	unsigned int numCycle;
};

