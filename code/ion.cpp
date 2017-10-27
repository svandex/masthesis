#include<ion.h>

void ddcChk::operator()(const int &ddcError) const {
	if(ddcError<0){
		os<<"ddcError"<<sep<<ddcError<<":"<<DDC_GetLibraryErrorDescription(ddcError)<<std::endl;
	}else{
	//	std::cout<<"Check Pass!"<<std::endl;
	}
}

ion::~ion(){
	ddcChk exChk;
	exChk(DDC_CloseFile(file));
}

ion::ion(const char* p, const char* t):pepath(p),tdmspath(t){
	ddcChk errorChk(std::cerr);
	//Open TDMS file
	errorChk(DDC_OpenFileEx(t,DDC_FILE_TYPE_TDM_STREAMING,1,&file));

	//Check which channel is ion	
#ifdef DEBUG
	errorChk(DDC_GetNumChannelGroups(file,&numOfChannelGroups));
	DDCChannelGroupHandle* cghtemp=(DDCChannelGroupHandle*)malloc(sizeof(DDCChannelGroupHandle)*(numOfChannelGroups+1));
	errorChk(DDC_GetChannelGroups(file,&cghtemp,numOfChannelGroups));	

	for(size_t i=1;i<=numOfChannelGroups;i++){
		std::cout<<"Channel Groups : "<<i<<std::endl;
		unsigned int numOfChannels;
		errorChk(DDC_GetNumChannels(cghtemp[i-1],&numOfChannels));
		DDCChannelHandle* chtemp = (DDCChannelHandle*)malloc(sizeof(DDCChannelHandle)*(numOfChannels+1)); 	
		errorChk(DDC_GetChannels(cghtemp[i-1],&chtemp,numOfChannels));

		for(size_t j=1;j<=numOfChannels;j++){
			unsigned int numOfProperties;
			errorChk(DDC_GetNumChannelProperties(chtemp,&numOfProperties));
			std::cout<<"		"<<j<<std::endl;
		}
	}
	free(cghtemp);
#endif //DEBUG

	//Determine number of cycles of TDMS file
	numOfCycle=0;//TODO LIST

	//std::cout<<"Ion Initialization Success."<<std::endl;
}


