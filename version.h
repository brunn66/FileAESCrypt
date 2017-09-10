#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "10";
	static const char MONTH[] = "09";
	static const char YEAR[] = "2017";
	static const char UBUNTU_VERSION_STYLE[] = "";
	
	//Software Status
	static const char STATUS[] = "Experimental";
	static const char STATUS_SHORT[] = "x";
	
	//Standard Version Type
	static const long MAJOR = 0;
	static const long MINOR = 9;
	static const long BUILD = 15;
	static const long REVISION = 104;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT = 144;
	#define RC_FILEVERSION 0,9,15,104
	#define RC_FILEVERSION_STRING "0, 9, 15, 104\0"
	static const char FULLVERSION_STRING[] = "0.9.15.104";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY = 15;
	

}
#endif //VERSION_H
