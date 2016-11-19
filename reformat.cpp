//////////////////////////////////////////////////
////////////////////LIBRARIES/////////////////////
//////////////////////////////////////////////////


#include <iomanip>
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <stdlib.h>
#include <time.h>

using namespace std;

struct class_data {
	string course;
	string credits;
	string type;
	string days;
	string startdate;
	string enddate;
	string starttime;
	string endtime;
	string campus;
	string room;
};


//////////////////////////////////////////////////
////////////////////PROTOTYPES////////////////////
//////////////////////////////////////////////////


int parse_int (ifstream &, string); //parsing function to return an int
bool input_file_open (ifstream &, char const *); //opens and tests open of file
string convert_integer (int); //converts integer into string
int convert_string (string);
class_data * create_array (int); //create dynamic array
void parse_class (string [], int, ifstream &);
string convert_time (string);
string convert_date (string);
string convert_days (string);
void write_ics (class_data * , int );


//////////////////////////////////////////////////
///////////////////////MAIN///////////////////////
//////////////////////////////////////////////////

int main () {
	int class_entry;
	ifstream input_file;
	bool status;
	status = input_file_open(input_file, "courses.txt");
	if (!status)
	{
		cout << "input_file_open could not be opened for reading\n";
		cout << "Program terminating\n";
		return 0;
	}
	else
	{
		cout << "Counting number of entries...:\t";
		class_entry = parse_int (input_file, "entry:"); //counts how many classes to run through
		cout << class_entry<< endl;
	}
	class_data * class_array = create_array (class_entry);
	for (int i = 0; i < class_entry; i++) {
		string class_data_array[10];
		parse_class (class_data_array, i, input_file);
		class_array [i].course = class_data_array [0];
		class_array [i].credits = class_data_array [1];
		class_array [i].type = class_data_array [2];
		class_array [i].days = class_data_array [3];
		class_array [i].startdate = class_data_array [4];
		class_array [i].enddate = class_data_array [5];
		class_array [i].starttime = class_data_array [6];
		class_array [i].endtime = class_data_array [7];
		class_array [i].campus = class_data_array [8];
		class_array [i].room = class_data_array [9];
	}
	/*{
	int i = 1;
	cout << "Debug class_array ["<< i << "]: \n";
	cout << class_array[i].course << endl;
	cout << class_array[i].credits << endl;
	cout << class_array[i].type << endl;
	cout << class_array[i].startdate << endl;
	cout << class_array[i].enddate << endl;
	cout << class_array[i].starttime << endl;
	cout << class_array[i].endtime << endl;
	cout << class_array[i].campus << endl;
	cout << class_array[i].room << endl;
	}*/
	
	for (int i = 0; i < class_entry; i++) {
		class_array [i].starttime = convert_time (class_array [i].starttime);
		class_array [i].endtime = convert_time (class_array [i].endtime);
		//cout << "starttime: " << class_array [i].starttime << endl;
		class_array[i].startdate = convert_date(class_array[i].startdate);
		class_array[i].enddate = convert_date(class_array[i].enddate);
		//cout << "enddate: " << class_array [i].enddate << endl;
		class_array[i].days = convert_days(class_array[i].days);
		cout << "days: " << class_array [i].days << endl;
	}	
	input_file.close ();
	write_ics (class_array, class_entry);
	delete [] class_array;
	return 0;

}



//////////////////////////////////////////////////
//////////////FUNCTION DEFINITIONS////////////////
//////////////////////////////////////////////////


//input_file_open function opens the file and assigns it to input_file
//the function returns a bool character depending on if the open was successful or not

bool input_file_open (ifstream& input_file, char const *file_name) 
{
   input_file.open(file_name);
   if (input_file.fail())
         return false;
   else
         return true;
}

bool output_file_open (ofstream& output_file, string file_name) 
{
   output_file.open(file_name);
   if (output_file.fail())
         return false;
   else
         return true;
}
//parse_int function gets each line of f_input_file and looks for the delimiter in it
//if the delimiter is present, the count goes up by one
//once the function has gone through every line of text it will return count

int parse_int (ifstream & f_input_file, string delim) {
	f_input_file.clear();
	f_input_file.seekg(0L, ios::beg);
	int count = 0;
	string line;
	while (!f_input_file.fail()) {
		string data;
		getline (f_input_file, data);
		int pos;
		pos = data.find (delim);
		if (pos!=string::npos){
			count ++;
		}
		pos = 0;
	}
	return count;
}

//this function converts a given integer from parameter to a string

string convert_integer (int integer)
{
	string converted_integer;
	stringstream convert;   	// stream used for the conversion
	convert << integer;	// insert the textual representation of 'f_index' in the characters stream
	converted_integer = convert.str(); // set 'converted_f_index' to the contents of the stream
	// 'converted_f_index' now represents the string equivalent of the integer index" 
	return converted_integer;
}

int convert_string (string string_var)
{
	int converted_string;
	istringstream convert (string_var);
	convert >> converted_string;
	return converted_string;
}

//this function creates a dynamic array and returns the position of the first index

class_data * create_array (int size)
{
	class_data *pos = new class_data [size];
	return pos;
}

void parse_class (string f_class_data_array [], int class_index, ifstream& f_input_file) {
	f_input_file.clear();
	f_input_file.seekg(0L, ios::beg);
	int class_number = class_index + 1;
	string class_number_string = convert_integer (class_number);
	string class_entry = "entry:" + class_number_string;
	//cout << "class entry:   " << class_entry << endl;
	//int position[9] = {7,8,5,11,9,11,9,7,10};
	string line;
	string test;
	do {
		getline (f_input_file, test);
		//cout << "debug test:    " << test << endl;
	}
	while (test!=class_entry);
	for (int i = 0; i < 10; i++){
		getline (f_input_file, line);
		int pos = line.find(':');
		f_class_data_array [i] = line.substr (pos+1);	
	}
}

string convert_time (string time) {
	//cout << "time:  " << time << endl;
	string newtime, hours_str;
	hours_str = time.substr (0, 2); 
	//cout << "hours:  " << hours_str << endl;	
	int hours_int = convert_string(hours_str);
	string mins = time.substr (3,2);
	//cout << "mins: " << mins << endl;
	string AM_PM = time.substr (5,2);
	//cout << "AM_PM: " << AM_PM << endl;
	if (AM_PM == "PM") {
		if (hours_int < 12) {
			hours_int += 12;
		}
	}
	else if (AM_PM == "AM") {	
		if (hours_int == 12) {
			hours_int = 0;
		}
	}
	newtime = convert_integer(hours_int) + mins + "00";
	//cout << "time:  " << newtime << endl;
	if (newtime.length () == 5) {
		newtime = '0' + newtime;
	}
	return newtime;
}

string convert_date (string date) {
	string newdate, year, month, day;
	year = date.substr(6,4);
	month = date.substr (0,2);
	day = date.substr (3,2);
	newdate = year+month+day;
	return newdate;

}

string convert_days (string days) {
	string newdays;
	int count = 0, start_pos = 0, pos;
	do{
		pos = days.find ('|', start_pos);
		count += 1;
		start_pos = pos + 1;
	} while (pos!=string::npos);
	string * days_arr = new string [count];
	start_pos = 0;
	pos = days.find ('|', start_pos);
	start_pos = pos + 1;
	for (int i = 0; i < count; i++) {
		pos = days.find ('|', start_pos);
		if (pos != string::npos) {
			days_arr[i] = days.substr (start_pos, pos-start_pos);
		}
		else {
			days_arr[i] = days.substr (start_pos);
		}
		start_pos = pos + 1;
	}
	count --;
	for (int i = 0; i < count; i ++) {
		cout << days_arr[i] << endl;
		if (days_arr[i] == "Sunday")
			days_arr[i] = "SU";
		else if (days_arr[i] == "Monday")
			days_arr[i] = "MO";
		else if (days_arr[i] == "Tuesday")
			days_arr[i] = "TU";
		else if (days_arr[i] == "Wednesday")
			days_arr[i] = "WE";
		else if (days_arr[i] == "Thursday")
			days_arr[i] = "TH";
		else if (days_arr[i] == "Friday")
			days_arr[i] = "FR";
		else if (days_arr[i] == "Saturday")
			days_arr[i] = "SA";
	}
	newdays = days_arr[0];
	if (count > 1) {
		for (int i = 1; i < count; i ++ ){
			newdays = newdays + "," + days_arr[i];
		}
	}
	delete [] days_arr;
	return newdays;
}

void write_ics (class_data * array, int cnt) {
	ofstream output_file;
	bool status;
	srand (time(0));
	int randomint =  rand () % 999999999 + 100000000;
	string randomid = convert_integer(randomint);
	string filename = "OhloneSchedule" + randomid +".ics";
	status = output_file_open(output_file, filename);
	if (!status)
	{
		cout << "output_file could not be opened for reading\n";
		cout << "Program terminating\n";
		return;
	}
	else {
		output_file << "BEGIN:VCALENDAR\nVERSION:2.0\nPRODID:DOT-SLASH-CS\n";
		for (int i = 0; i < cnt; i++) {
			output_file << "BEGIN:VEVENT\nRRULE:FREQ=WEEKLY;UNTIL=";
			output_file << array[i].enddate <<"T115959Z;BYDAY=";
			output_file << array[i].days << endl;
			output_file << "DTEND;TZID=America/Los_Angeles:" << array[i].startdate << "T" << array[i].endtime << endl;
			output_file << "SUMMARY:" << array[i].course << "-" << array[i].type << endl;
			output_file << "DTSTART;TZID=America/Los_Angeles:" << array[i].startdate << "T" << array[i].starttime << endl;
			output_file << "DESCRIPTION:" << array[i].campus << array[i].room << " | " << array[i].credits << endl;
			output_file << "END:VEVENT" << endl;
		}
		output_file << "END:VCALENDAR";
	}
	output_file.close ();
}