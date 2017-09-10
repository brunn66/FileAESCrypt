#include <iostream>
#include <fstream>
#include "BasicCryptoPPWrap.h"
#include <string>
#include <sstream>
#include <stdio.h>
#include <streambuf>
#include "version.h"
#include <sys/stat.h>



using namespace std;


// Functions
void ShowAbout () {
    // Print Version Info
    cout << "========================================================================\n";
    cout << "FileAESCrypt Linux x86_64 " << AutoVersion::FULLVERSION_STRING<< " " << AutoVersion::STATUS<< " Build " <<
    AutoVersion::BUILD<< " (" << AutoVersion::YEAR<< "-" << AutoVersion::MONTH<< "-" << AutoVersion::DATE<< ")" << "\n";
    cout << "Deleted." << endl;

    // Print License info
    cout <<"========================================================================\n" <<
    "This program utilizes the following libraries:\n\n   --- Crypto++ 5.65 - Copyright (c) 1995-2013 by Wei Dai\n"<<
    "   --- BasicCryptoPPWrap (Static) - By Michael R. Rich, 2009\n========================================================================"<<
    endl<<endl;
}


bool fileExists(const std::string& filename) {
    struct stat buf;
    if (stat(filename.c_str(), &buf) != -1)
    {
        return true;
    }
    return false;
}

// ================ MAIN ====================
int main (int argc, char * const argv[]) {


    string ThisProgramFilename = argv[0];
    string UsageNote = "\nUsage:\nEncode file: " + ThisProgramFilename + " -e [inputfile] [password] [IVstring] [outputfile]\nDecode file: " +
    ThisProgramFilename + " -d [inputfile] [password] [IVstring] [outputfile]\n\nShow Help:   " + ThisProgramFilename + " -h\n"+
    " Show Version Info:   " + ThisProgramFilename + " --version OR --about\n";
    string NoModeArg = "Syntax Error: No Mode Set\n" + UsageNote;
    string NoInputFile = "Syntax Error: No Input File Specified\n" + UsageNote;

    string NoPwd ="Syntax Error: No Password Specified\n" + UsageNote;
    string NoIvString = "Syntax Error: No iv-string specified" + UsageNote;
    string HelpText ="HELP:\n" + UsageNote + "\nEncode File: " + ThisProgramFilename +
    " -ef [inputfile] [password] [IVstring] (This mode also encrypt the filename)\nDecode File: " +
    ThisProgramFilename + " -df [inputfile] [password] [IVstring] (This mode is for using with -df)\nEncode-H-V File: " +
    ThisProgramFilename + " -ehv [inputfile] [password] [IVstring] [outputfile]\nEncode-H-V (F&F) File: " +
    ThisProgramFilename + " -ehvf [inputfile] [password] [IVstring]\n"+
    "Notes:  This function first encodes the supplied file as with the -e option and when finished, it also decodes the encrypted file"+
    "and compares the hashes (SHA-256) from the original file and the recovered (decoded) file."+
    "If they match, the decoded file will be deleted. If the DONT match, only the original file will be kept.";



    // Check for and if present load mode-flag
    if (argc == 1) { // No mode specified
        cout << NoModeArg;
        return -1;
    }
    string ArgMode = argv[1]; // Load mode-argument

        // Check if -h flag supplied
    if (ArgMode == "-h") {
    cout << HelpText;
    return -1;
    }else if (ArgMode == "-H") {
    cout << HelpText;
    return -1;
    }else if (ArgMode == "-?") {
    cout << HelpText;
    return -1;
    }

        // Check if --version or --about supplied
    if (ArgMode == "--version") {
    ShowAbout();
    return -1;
    }else if (ArgMode == "--about") {
    ShowAbout();
    return -1;
    }


    cout << "Loading Arguments...   ";


    // Exit if not all argument supplied
    if (argc == 2) { // No input file
        cout << NoInputFile;
        return -1;
    }else if (argc == 3) { // No password supplied
        cout << NoPwd;
        return -1;
    }else if (argc == 4) { // No IV supplied
        cout << NoIvString;
        return -1;
    }

    // Load arguments

    string InputFilename = argv[2];
    string VerifiedFilename;
    string UserPwd = argv[3];
    string Iv1 = argv[4];
    string OutputFilename;
    string EncOutputFilename;
    string DecOutputFilename;
    if (argc == 6) OutputFilename = argv[5];



    string Iv2 = BasicCryptoPPWrap::hashSHA256(Iv1); //Hash user IV and trim to 16byte
    Iv2.resize(16);

    // Variables for operation
    bool ArgDecoding = false;
    bool ArgEncoding = false;
    bool ArgHashVerify = false;
    bool ArgEncFilename = false;
    bool ArgDecFilename = false;



    cout << "DONE" << endl;

    // ModeSet
    cout << "Mode: ";

    if(ArgMode == ""){ // Nomode
        cout << NoModeArg;
        return -1;
    }else if(ArgMode == "-e"){ // Encoding mode
        ArgEncoding = true;
        cout << "Encoding Mode Set" << endl;

    }else if(ArgMode == "-ef"){ // Encoding file and filename mode
        ArgEncoding = true;
        ArgEncFilename = true;
        cout << "Encoding (File & Filename) Mode Set" << endl;

    }else if(ArgMode == "-ehv"){ // Encode-Hash-Verify mode

        ArgHashVerify = true;
        cout << "Encode-Hash-Verify Mode Set" << endl;
    }else if(ArgMode == "-ehvf"){ // Encode-Hash-Verify (F&F) mode

        ArgEncFilename = true;
        ArgDecFilename = true;
        ArgHashVerify = true;
        cout << "Encode-Hash-Verify (F&F) Mode Set" << endl;

    }else if(ArgMode == "-d"){ // Decoding mode
        ArgDecoding = true;
        cout << "Decoding Mode Set" << endl;

    }else if(ArgMode == "-df"){ // Decoding file and filename mode
        ArgDecoding = true;
        ArgDecFilename = true;
        cout << "Decoding (File & Filename) Mode Set" << endl;

    }else if(ArgMode != "-d"||"-df"||"-e"||"-ef"||"-ehv"||"-ehvf"){
        cout << "Syntax error: Invalid Mode: " << ArgMode << endl << UsageNote;
        return -1;
    }

    // FileCheck
    /* if (InputFilename == OutputFilename) {
    cout << "Fatal I/O Error: Input File and Output File cannot be the same!" << endl;
    return -1;

    } */





    // main program ================================================================================

    bool err;
	string errMsg;

	/** MR test below **/


	// string key2 = BasicCryptoPPWrap::BitGen(256); // For use with random pwd (256bit)
	// string key2 = BasicCryptoPPWrap::hashSHA256("This is my password"); // For Use With manual pwd, hashed to 256bit



    string key2 = BasicCryptoPPWrap::hashSHA256(UserPwd); //Hash userpwd to key2
    cout << "Using Password: " << UserPwd << endl;
    cout << "Using IV      : " << Iv1 << endl;

    // cout << "Password Hash: " << BasicCryptoPPWrap::HexEncode(BasicCryptoPPWrap::hashSHA256(UserPwd)) << endl;





    //ENCRYPTION START

    // Create encrypted filename


    if (ArgEncoding) {

        if (fileExists(InputFilename)) {
        cout << "Input file: " << InputFilename << " OK" << endl;
    }else if (!fileExists(InputFilename)){
        cout <<  "I/O Error: Can't open input file " << InputFilename << endl;
        return -1;
    }
        // Create encrypted filename
        if (ArgEncFilename) {
            EncOutputFilename = BasicCryptoPPWrap::HexEncode(BasicCryptoPPWrap::EncryptStringAES(InputFilename, key2, Iv2, err, errMsg));
            if (err) {
                cout << errMsg << "\n";
                return -1;
            }
             if (!fileExists(EncOutputFilename)) {
                cout << "Output file: " << EncOutputFilename << " will be created" << endl;
            }else if (fileExists(EncOutputFilename)){
                cout <<  "I/O Error: Output file already exist: " << EncOutputFilename << endl;
        return -1;
    }

        }else{
            if (argc != 6) {
                cout << "Syntax Error: Output filename must be specified when using the -e flag" << endl;
                return -1;
            }
            EncOutputFilename = OutputFilename;
             if (!fileExists(EncOutputFilename)) {
                cout << "Output file: " << EncOutputFilename << " will be created" << endl;
            }else if (fileExists(EncOutputFilename)){
                cout <<  "I/O Error: Output file already exist: " << EncOutputFilename << endl;
        return -1;
    }


        }



        cout << "Encrypting file: " << InputFilename << " to " << EncOutputFilename << endl;



	ifstream infile(InputFilename.c_str(), ios::binary);

	ofstream outfile(EncOutputFilename.c_str(), ios::binary);


	BasicCryptoPPWrap::EncryptFileAES(infile, outfile, key2, Iv2,  err, errMsg);
	if (err) {
		cout << errMsg << "\n";
		return -1;
	}

	infile.close();
	outfile.close();

	if (ArgEncFilename) {
	    remove(InputFilename.c_str());
        cout << InputFilename << " deleted"<<endl;
	}

	cout << "   Done!" << endl;
	// delete file
	// remove("xample.txt");

    }


	//DECRYPTION START
    if (ArgDecoding) {
            if (fileExists(InputFilename)) {
        cout << "Input file: " << InputFilename << " OK" << endl;
    }else if (!fileExists(InputFilename)){
        cout <<  "I/O Error: Can't open input file " << InputFilename << endl;
        return -1;
    }
        // Recover filename
        if (ArgDecFilename) {
            DecOutputFilename = BasicCryptoPPWrap::HexDecode(BasicCryptoPPWrap::DecryptStringAES(InputFilename, key2, Iv2, err, errMsg));
        }else{
             if (argc != 6) {
                cout << "Syntax Error: Output filename must be specified when using the -d flag" << endl;
                return -1;
            }
        DecOutputFilename = OutputFilename;
        }

        if (!fileExists(DecOutputFilename)) {
        cout << "Output file: " << DecOutputFilename << " will be created" << endl;
    }else if (fileExists(DecOutputFilename)){
        cout <<  "I/O Error: Output file already exist: " << DecOutputFilename << endl;
        return -1;
    }


	cout << "Decrypting file: " << InputFilename << " to " << DecOutputFilename << endl;

	stringstream outBuffer;
	ifstream encfile(InputFilename.c_str(), ios::binary);
	// infile.open(InputFilename.c_str(), ios::binary); //

	// Decrypt it!
	BasicCryptoPPWrap::DecryptFileAES(encfile, outBuffer, key2, Iv2,  err, errMsg);
	if (err) {
		cout << errMsg << "\n";
		return -1;
	}


	encfile.close();


	// buffer

	ofstream resultatet(DecOutputFilename.c_str(), ios::binary);

	// string aLine;
	// while (getline(outBuffer, aLine)) {
	//	resultatet << aLine; // <<  "\n";
	// }


    // const std::string& tmp = outBuffer.str();
    // const char* cstr = tmp.c_str();
	// resultatet.write(cstr, sizeof (cstr));
    // string aLine;
	// while (getline(outBuffer, aLine)) {
	// resultatet << aLine <<  "\n";
	// }

    resultatet.write( outBuffer.str().c_str(), outBuffer.str().length() );
    resultatet.close();


    if (ArgDecFilename) {
        remove(InputFilename.c_str());
        cout << InputFilename << " deleted" << endl;
    }

    cout << "   Done!" << endl;
	// And that's about it!
    }




	//HASHING-VERIFICATION

	    // Tempfix
    if (ArgHashVerify) cout << endl << "Encode-Hash-Verify Mode Disabled." << endl;

    /* if (ArgHashVerify) {

        // 1.- Encrypting
        string TempFile = OutputFilename + ".tmp";
    cout << "Encrypting file: " << InputFilename << " to " << OutputFilename;

	ifstream infile(InputFilename.c_str(), ios::binary);


	ofstream outfile(OutputFilename.c_str(), ios::binary);

	// encrypt it!
	BasicCryptoPPWrap::EncryptFileAES(infile, outfile, key2, Iv2,  err, errMsg);
	if (err) {
		cout << errMsg << "\n";
		return -1;
	}

	infile.close();
	outfile.close();
	cout << "   Done!" << endl;
	// delete file
	// remove("xample.txt");



        //2. DECRYPTION START

	//
	cout << "Decrypting file: " << OutputFilename << " to tempfile: " << TempFile;

	stringstream outBuffer;
	ifstream encfile(OutputFilename.c_str(), ios::binary);
	// infile.open(InputFilename.c_str(), ios::binary); //

	// Decrypt it!
	BasicCryptoPPWrap::DecryptFileAES(encfile, outBuffer, key2, Iv2,  err, errMsg);
	if (err) {
		cout << errMsg << "\n";
		return -1;
	}


	encfile.close();




	ofstream resultatet(TempFile.c_str(), ios::binary);

	// string aLine;
	// while (getline(outBuffer, aLine)) {
	//	resultatet << aLine; // <<  "\n";
	// }


    // const std::string& tmp = outBuffer.str();
    // const char* cstr = tmp.c_str();
	// resultatet.write(cstr, sizeof (cstr));
    // string aLine;
	// while (getline(outBuffer, aLine)) {
	// resultatet << aLine <<  "\n";
	// }

    resultatet.write( outBuffer.str().c_str(), outBuffer.str().length() );
    resultatet.close();


    cout << "   Done!" << endl;
	// And that's about it!




	ifstream oldfile1(InputFilename.c_str(), ios::binary);
	ifstream newfile1(TempFile.c_str(), ios::binary);

    stringstream oldbuffer;
    stringstream newbuffer;

    oldbuffer << oldfile1.rdbuf();
    newbuffer << newfile1.rdbuf();

	string oldhash1 = BasicCryptoPPWrap::hashSHA256(oldbuffer.str());
	string newhash1 = BasicCryptoPPWrap::hashSHA256(newbuffer.str());

	oldfile1.close();
	newfile1.close();


	cout << "Hash Input file    : " << BasicCryptoPPWrap::HexEncode(oldhash1) << endl;
	cout << "Hash Recovered file: " << BasicCryptoPPWrap::HexEncode(newhash1) << endl;

	if (oldhash1 == newhash1) {
    cout << "Hash Matches! - No Data Loss" << endl;
        remove(TempFile.c_str());
    cout << TempFile << " deleted"<<endl;
    cout << "All operations finished."<<endl;
	}
	else{
        cout << "ERROR: HASH MISMATCH! Deleting Files - Aborting" << endl;
        remove(OutputFilename.c_str());
        cout << OutputFilename << " deleted" << endl;
        remove(TempFile.c_str());
        cout << TempFile << " deleted" << endl;

	}



	return 0;


} */

}

