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
#include <ctime>
#include <chrono>
#include "VTK.h"
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
char* camera_orientation = NULL;
char* filePathSource = NULL;
char* filePathTarget = NULL;

/*
argc is the count of arguments passed to the program. 1 is the program name, so this number will be n+1, where n is the number of commands
we pass. argv is the arguments passed. 1 is the program name, the others are the ones that we pass, in the order passed.
*/
int main(int argc, char *argv[])

{

	//Writing points to logfile instead
	freopen("output.txt", "w", stdout);

	//filePathSource = argv[1];
	//filePathTarget = argv[2];
	
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

	//argument 7: Description
	pdesc = argv[7];
	cout << "7: pdesc\n";
	cout << pdesc;
	cout << "\n";

	//argument 8: Report_Type
	rtype = argv[8];
	cout << "8: rtype\n";
	cout << rtype;
	cout << "\n";

	//argument 9: Confidence_Level
	clevel = argv[9];
	cout << "9: clevel\n";
	cout << clevel;
	cout << "\n";

	//argument 10: Error_Bound
	ebound = argv[10];
	cout << "10: ebound\n";
	cout << ebound;
	cout << "\n";

	//argument 11: Error_Unit
	eunit = argv[11];
	cout << "11: eunit\n";
	cout << eunit;
	cout << "\n";

	//argument 12: Alignment_Type
	atype = argv[12];
	cout << "12: atype\n";
	cout << atype;
	cout << "\n";

	//argument 13: Camera_Orientation
	camera_orientation = argv[13];
	cout << "15: camera_orientation\n";
	cout << camera_orientation;
	cout << "\n";

	//argument 14: source file
	filePathSource = argv[14];
	cout << "16: source file\n";
	cout << filePathSource;
	cout << "\n";

	//argument 15+: target file(s)
	filePathTarget = argv[15];
	cout << "17: target file\n";
	cout << filePathTarget;
	cout << "\n";

	/* Create HTML file for Comparison report */
	string save_loc = string(sloc);
	string file_name = string(fname);

#if !defined(_WIN32)
	save_loc = save_loc.substr(3, save_loc.length());
	file_name = file_name.substr(3, file_name.length());
#endif 

	string file_path;
	file_path.append(save_loc);
	file_path.append(file_name);

	string report_name;
	report_name.append(file_path);
	report_name.append(".html");
	cout << report_name << "\n";

	string screenshot_path;
	screenshot_path.append(file_path);
	screenshot_path.append(".png");

	ofstream report_output;
	report_output.open(report_name);

	/* Get current date for report */
	time_t curr_date = chrono::system_clock::to_time_t(chrono::system_clock::now());

	/* Set-up HTML file */
	report_output << "<!DOCTYPE html>\n";
	report_output << "<html>\n";
	report_output << "\t<head>\n";
	report_output << "\t\t<meta charset=\"UTF-8\">\n";
	report_output << "\t\t<title>Comparisoft</title>\n";
	report_output << "\t</head>\n";
	report_output << "\t<body>\n";

	/* Add all report info here */
	report_output << "\t\t<h1 style=\"font-family:georgia;text-align:center;\">Comparison Report</h1>\n";
	report_output << "\t\t<p style=\"font-family:georgia;\"><b>&emsp;&emsp;&emsp;&emsp;Date:</b> " << ctime(&curr_date) << "</p>\n";
	report_output << "\t\t<p style=\"font-family:georgia;\"><b>&emsp;&emsp;&emsp;&emsp;Technician:</b> " << tname << "</p>\n";
	report_output << "\t\t<p style=\"font-family:georgia;\"><b>&emsp;&emsp;&emsp;&emsp;Client:</b> " << cname << "</p>\n";
	report_output << "\t\t<p style=\"font-family:georgia;\"><b>&emsp;&emsp;&emsp;&emsp;Patient:</b> " << pname << "</p>\n";

	report_output << "\t\t<p></p>\n";
	report_output << "\t\t<center><img align=\"middle\" src=\"";
	report_output << screenshot_path;
	report_output << "\" alt=\"Screenshot1\"></center>";

	report_output << "\t</body>\n";
	report_output << "</html>\n";

	/* Close will occur following alignment once the algorithm is generating values */
	report_output.close();

	//Launch the VTK function
	VTKmain(filePathSource, filePathTarget, screenshot_path, camera_orientation);

}
