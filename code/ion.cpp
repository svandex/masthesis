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

//Show All channel properties
std::ostream& operator<< (std::ostream &os, const ion& ionT){
	ddcChk errorChk;
	DDCChannelGroupHandle* cghtemp=(DDCChannelGroupHandle*)std::calloc(ionT.numOfChannelGroups,sizeof(DDCChannelGroupHandle));
	if(cghtemp == nullptr){std::cerr<<"DDCChannelGroupHandle allocation failed! "<<std::endl;return os;}
	errorChk(DDC_GetChannelGroups(ionT.file,cghtemp,ionT.numOfChannelGroups));

	unsigned int numOfChannels;
	//in each channel group
	for(std::size_t i=1;i<=ionT.numOfChannelGroups;i++){
		os<<"Channel Groups : "<<i<<std::endl;
		errorChk(DDC_GetNumChannels(*(cghtemp+i-1),&numOfChannels));
		DDCChannelHandle* chtemp = (DDCChannelHandle* )std::calloc(numOfChannels,sizeof(DDCChannelHandle));
	if(chtemp == nullptr){std::cerr<<"DDCChannelHandle allocation failed! "<<std::endl;return os;}
		errorChk(DDC_GetChannels(*(cghtemp+i-1),chtemp,numOfChannels));

#ifdef DEBUG
		std::cout<<"cghtemp is "<<cghtemp<<", typeinfo of cghtemp is "<<typeid(cghtemp).name()<<std::endl;
		std::cout<<"typeinfo of *cghtemp is "<<typeid(*cghtemp).name()<<std::endl;
		std::cout<<"DDCChannelGroupHandle typeinfo is "<<typeid(DDCChannelGroupHandle).name()<<std::endl;
		std::cout<<"Line 40, numofCHannel is "<<numOfChannels<<std::endl;
#endif //DEBUG

		//each channel
		for(std::size_t j=1;j<=numOfChannels;j++){
			os<<"	Channel : "<<j<<std::endl;
			unsigned int numOfProperties;
			errorChk(DDC_GetNumChannelProperties(*(chtemp+j-1),&numOfProperties));
			char* property=0;
			unsigned int length;
			std::string property_s;

			errorChk(DDC_GetChannelStringPropertyLength(*(chtemp+j-1),DDC_CHANNEL_NAME,&length));

			property = (char*)malloc(length+1);
			errorChk(DDC_GetChannelProperty(chtemp[j-1],DDC_CHANNEL_NAME,property,length+1));
			errorChk(DDC_GetChannelProperty(chtemp[j-1],DDC_CHANNEL_NAME,&property_s,0));

			os<<"		Property: "<<property<<std::endl;
			free(property);
		}
		std::free(chtemp);
	}
	std::free(cghtemp);
	return os;
}

