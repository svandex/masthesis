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

//Initial Processing of ion TDMS file and PE TDMS file, PE for photoelectric encoder.
class ion{
public:
	ion(const char* pe, const char* ionT);
	ion(const ion& )=delete;
	~ion();
	friend std::ostream& operator<< (std::ostream& os, const ion& i);//Output all properties of one channel

//protected:
	DDCChannelGroupHandle getCGH(const unsigned int &cg) const;
	DDCChannelHandle getCH(const unsigned int &cgh, const unsigned int &ch) const;

	unsigned int split(std::pair<unsigned int, unsigned int> *p) const;
	//Use A-signal and Z-signal to determine, make sure the method has enough epsilong
	//use std::pair to hold each cycle's beginning number and ending number of ion-curve and cylinder-pressure-curve

private:
	const char* pepath;
	const char* ionTpath;

protected:
	DDCFileHandle file;
	unsigned int numOfChannelGroups;
	unsigned int numOfCycle;
};

std::ostream& operator<< (std::ostream& os, const ion& i);//Output all properties in format

//IO reading from TDMS file and writing cycle data to a file
class ioncyc:public ion{
public:
	ioncyc(const ion& ionT,unsigned int n);
	ioncyc(const ioncyc&)=delete;
	void writeTo(const char* w);//save data of single cycle for plotting
private:
	unsigned int numCycle;
};

