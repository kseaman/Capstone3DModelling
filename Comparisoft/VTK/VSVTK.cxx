// compile with: /D_UNICODE /DUNICODE /DWIN32 /D_WINDOWS /c

//Not sure what this is for, but it doesn't seem to break anything
#ifdef _MSC_VER
#    pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <string>
#include "VTK.h"
#include "fileDialogue.h"



// Global variables

//declare the file path variables here so that they are global
char* cname = NULL;
char* pname = NULL;
char* fdesc = NULL;
char* sloc = NULL;
char* fname = NULL;
char* tname = NULL;
char* prodname = NULL;
char* pdate = NULL;
char* pdesc = NULL;
char* rtype = NULL;
char* clevel = NULL;
char* ebound = NULL;
char* eunit = NULL;
char* atype = NULL;
char* refattempt = NULL;
char* prodattempt = NULL;
char* filePathReference = NULL;
char* filePathProduction = NULL;

/*
argc is the count of arguments passed to the program. 1 is the program name, so this number will be n+1, where n is the number of commands
we pass. argv is the arguments passed. 1 is the program name, the others are the ones that we pass, in the order passed.
*/
int main(int argc, char *argv[])

{

	//Writing points to logfile instead
	freopen("output.txt", "w", stdout);

	//filePathReference = argv[1];
	//filePathProduction = argv[2];
	
	//Argument 0: program name

	//argument 1: Client_Name
	cname = argv[1];
	std::cout << "1: cname\n";
	std::cout << cname;
	std::cout << "\n";

	//argument 2: Patient_Name
	pname = argv[2];
	std::cout << "2: pname\n";
	std::cout << pname;
	std::cout << "\n";

	//argument 3: File_Description
	fdesc = argv[3];
	std::cout << "3: fdesc\n";
	std::cout << fdesc;
	std::cout << "\n";

	//argument 4: Save_Location
	sloc = argv[4];
	std::cout << "4: sloc\n";
	std::cout << sloc;
	std::cout << "\n";

	//argument 5: File_Name
	fname = argv[5];
	std::cout << "5: fname\n";
	std::cout << fname;
	std::cout << "\n";

	//argument 6: Technician_Name
	tname = argv[6];
	std::cout << "6: tname\n";
	std::cout << tname;
	std::cout << "\n";

	//argument 7: Product_Name
	prodname = argv[7];
	std::cout << "7: pname\n";
	std::cout << pname;
	std::cout << "\n";

	//argument 8: Production_Date
	pdate = argv[8];
	std::cout << "8: pdate\n";
	std::cout << pdate;
	std::cout << "\n";

	//argument 9: Product_Description
	pdesc = argv[9];
	std::cout << "9: pdesc\n";
	std::cout << pdesc;
	std::cout << "\n";

	//argument 10: Report_Type
	rtype = argv[10];
	std::cout << "10: rtype\n";
	std::cout << rtype;
	std::cout << "\n";

	//argument 11: Confidence_Level
	clevel = argv[11];
	std::cout << "11: clevel\n";
	std::cout << clevel;
	std::cout << "\n";

	//argument 12: Error_Bound
	ebound = argv[12];
	std::cout << "12: ebound\n";
	std::cout << ebound;
	std::cout << "\n";

	//argument 13: Error_Unit
	eunit = argv[13];
	std::cout << "13: eunit\n";
	std::cout << eunit;
	std::cout << "\n";

	//argument 14: Alignment_Type
	atype = argv[14];
	std::cout << "14: atype\n";
	std::cout << atype;
	std::cout << "\n";

	//argument 15: Ref_Attempt
	refattempt = argv[15];
	std::cout << "15: refattempt\n";
	std::cout << refattempt;
	std::cout << "\n";

	//argument 16: Prod_Attempt
	prodattempt = argv[16];
	std::cout << "16: prodattempt\n";
	std::cout << prodattempt;
	std::cout << "\n";

	//argument 17: referance file
	filePathReference = argv[17];
	std::cout << "17: ref file\n";
	std::cout << filePathReference;
	std::cout << "\n";

	//argument 18+:production file(s)
	filePathProduction = argv[18];
	std::cout << "18: production file\n";
	std::cout << filePathProduction;
	std::cout << "\n";
	

	

	//Hardcoded files for testing
	//filePathReference = "C:/Development/Capstone/Capstone3DModelling/Comparisoft/VTK/VTK-bin/Release/CaroleLowerProduction.stl";
	//filePathProduction = "C:/Development/Capstone/Capstone3DModelling/Comparisoft/VTK/VTK-bin/Release/CaroleLowerReference.stl";

	//Launch the VTK function
	VTKmain(filePathReference, filePathProduction);

}
