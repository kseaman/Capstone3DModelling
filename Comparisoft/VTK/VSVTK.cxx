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
#include <fstream>
#include "VTK.h"
#include "fileDialogue.h"
using namespace std;



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
	cout << "1: cname\n";
	cout << cname;
	cout << "\n";

	//argument 2: Patient_Name
	pname = argv[2];
	cout << "2: pname\n";
	cout << pname;
	cout << "\n";

	//argument 3: File_Description
	fdesc = argv[3];
	cout << "3: fdesc\n";
	cout << fdesc;
	cout << "\n";

	//argument 4: Save_Location
	sloc = argv[4];
	cout << "4: sloc\n";
	cout << sloc;
	cout << "\n";

	//argument 5: File_Name
	fname = argv[5];
	cout << "5: fname\n";
	cout << fname;
	cout << "\n";

	//argument 6: Technician_Name
	tname = argv[6];
	cout << "6: tname\n";
	cout << tname;
	cout << "\n";

	//argument 7: Product_Name
	prodname = argv[7];
	cout << "7: pname\n";
	cout << pname;
	cout << "\n";

	//argument 8: Production_Date
	pdate = argv[8];
	cout << "8: pdate\n";
	cout << pdate;
	cout << "\n";

	//argument 9: Product_Description
	pdesc = argv[9];
	cout << "9: pdesc\n";
	cout << pdesc;
	cout << "\n";

	//argument 10: Report_Type
	rtype = argv[10];
	cout << "10: rtype\n";
	cout << rtype;
	cout << "\n";

	//argument 11: Confidence_Level
	clevel = argv[11];
	cout << "11: clevel\n";
	cout << clevel;
	cout << "\n";

	//argument 12: Error_Bound
	ebound = argv[12];
	cout << "12: ebound\n";
	cout << ebound;
	cout << "\n";

	//argument 13: Error_Unit
	eunit = argv[13];
	cout << "13: eunit\n";
	cout << eunit;
	cout << "\n";

	//argument 14: Alignment_Type
	atype = argv[14];
	cout << "14: atype\n";
	cout << atype;
	cout << "\n";

	//argument 15: Ref_Attempt
	refattempt = argv[15];
	cout << "15: refattempt\n";
	cout << refattempt;
	cout << "\n";

	//argument 16: Prod_Attempt
	prodattempt = argv[16];
	cout << "16: prodattempt\n";
	cout << prodattempt;
	cout << "\n";

	//argument 17: reference file
	filePathReference = argv[17];
	cout << "17: ref file\n";
	cout << filePathReference;
	cout << "\n";

	//argument 18+:production file(s)
	filePathProduction = argv[18];
	cout << "18: production file\n";
	cout << filePathProduction;
	cout << "\n";

	//Hardcoded files for testing
	//filePathReference = "C:/Development/Capstone/Capstone3DModelling/Comparisoft/VTK/VTK-bin/Release/CaroleLowerProduction.stl";
	//filePathProduction = "C:/Development/Capstone/Capstone3DModelling/Comparisoft/VTK/VTK-bin/Release/CaroleLowerReference.stl";

	/* Create HTML file for Comparison report */
	char report_path[100];
	sprintf(report_path, "%s%s%s%s", sloc, "/", fname, ".html");
	char screenshot[100];
	sprintf(screenshot, "%s%s%s%s", sloc, "/", fname, ".png");
	ofstream report_output;
	report_output.open(report_path);

	/* Set-up HTML file */
	report_output << "<!DOCTYPE html>\n";
	report_output << "<html>\n";
	report_output << "\t<head>\n";
	report_output << "\t\t<meta charset=\"UTF-8\">\n";
	report_output << "\t\t<title>Comparisoft</title>\n";
	report_output << "\t</head>\n";
	report_output << "\t<body>\n";

	/* Add all report info here */
	report_output << "\t\t<h1>Comparison Report</h1>\n";
	report_output << "\t\t<p>Technician: " << tname << "</p>\n";
	report_output << "\t\t<p>Client: " << cname << "</p>\n";
	report_output << "\t\t<p>Patient: " << pname << "</p>\n";

	report_output << "\t\t<img src=\"";
	report_output << screenshot;
	report_output << "\" alt=\"Screenshot1\">";

	report_output << "\t</body>\n";
	report_output << "</html>\n";

	/* Close will occur following alignment once the algorithm is generating values */
	report_output.close();

	//Launch the VTK function
	VTKmain(filePathReference, filePathProduction, screenshot);

}
