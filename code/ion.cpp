#include<ion.h>
#include<cstdlib>
#include<typeinfo>
#include<string>

void ddcChk::operator()(const int &ddcError) const {
	if(ddcError<0){
		os<<"ddcError"<<sep<<ddcError<<":"<<DDC_GetLibraryErrorDescription(ddcError)<<std::endl;
	//	throw;
	}else{
	//	std::cout<<"Check Pass!"<<std::endl;
	}
}

ion::~ion(){
	ddcChk exChk;
	exChk(DDC_CloseFile(file));
}

ion::ion(const char* pe, const char* ionT):pepath(pe),ionTpath(ionT){
	ddcChk errorChk(std::cerr);
	//Open TDMS file
	errorChk(DDC_OpenFileEx(ionTpath,DDC_FILE_TYPE_TDM_STREAMING,1,&file));
	errorChk(DDC_GetNumChannelGroups(file,&numOfChannelGroups));

	//Determine number of cycles of TDMS file
	numOfCycle=0;//TO DO LIST
}

DDCChannelGroupHandle ion::getCGH(const unsigned int &cg) const{
	if(cg==0||cg>numOfChannelGroups){std::cerr<<"getChannelGroupHandle error: cg is not in the correct range. numOfChannelGroups is "<<numOfChannelGroups<<std::endl;return nullptr;}
	ddcChk errorChk;
	DDCChannelGroupHandle* cghtemp=(DDCChannelGroupHandle*)std::calloc(numOfChannelGroups,sizeof(DDCChannelGroupHandle));
	errorChk(DDC_GetChannelGroups(file,cghtemp,numOfChannelGroups));	
	DDCChannelGroupHandle temp=cghtemp[cg-1];
	free(cghtemp);
	return temp;
}

DDCChannelHandle ion::getCH(const unsigned int &cgh, const unsigned int &ch) const{
	ddcChk errorChk;
	DDCChannelGroupHandle cghtemp=getCGH(cgh);	
	unsigned int numOfChannels;
	errorChk(DDC_GetNumChannels(cghtemp,&numOfChannels));	

	if(ch==0||ch>numOfChannels){std::cerr<<"getChannelHandle error: ch is not in the correct range. numOfChannel is "<<numOfChannels<<std::endl;return nullptr;}
	DDCChannelHandle* chtemp = (DDCChannelHandle* )std::calloc(numOfChannels,sizeof(DDCChannelHandle));
	errorChk(DDC_GetChannels(cghtemp,chtemp,numOfChannels));
	DDCChannelHandle temp = chtemp[ch-1];
	free(chtemp);
	return temp;
}
