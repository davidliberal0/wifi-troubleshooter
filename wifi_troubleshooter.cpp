// wifi.cpp : Defines the entry point for the application.
//

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <thread>


using namespace std;

string option; // holds the user option for the program 
string accConfirm; // Used to confirm if the user already has an existing account 


string username; // Username 
string password; // Password

void showMenu();
void wifiCheck(string option);
void recentConnection();
void toolLog();

void loginScreen();
void createNewUser();

void customerSetup(); 
void equipSelect();


void show_progress_bar(ostream& os, int time,
	string message, char symbol = '*') {

	static const auto bar_length = 45;

	if (message.length() >= bar_length) {

		os << message << '\n';
		message.clear();

	}
	else {

		message += " ";

	}

	const auto progress_level = 100.0 / (bar_length - message.length());

	cout << message;

	for (double percentage = 0; percentage <= 100; percentage += progress_level) {

		message += symbol;
		os << "\r [" << setw(3) << static_cast<int>(percentage) << "% ] " << message
			<< "> ]" << flush;
		this_thread::sleep_for(chrono::milliseconds(time));


	}


	os << "\n\n";

}




int main() {

	int nav; // for navigating through a menu 

	toolLog(); // Program Log

	
	cout << "WIFI TROUBLESHOOTER" << endl;
	cout << "-------------------" << endl;

	// Asks the user if he/she has an existing account - User input validation 
	while (accConfirm != "Yes" || accConfirm != "yes" || accConfirm != "No" || accConfirm != "no") {

		cout << "Are you an existing user?";
		cin >> accConfirm;

		if (accConfirm == "Yes" || accConfirm == "yes") {

			loginScreen();
			system("cls"); 
			break;
		}
		else if (accConfirm == "No" || accConfirm == "no") {

			createNewUser();
			Sleep(600);
			system("cls"); 
			break;
		}


	}


	cout << "Performing a system check\n";

	show_progress_bar(clog, 100, "Percentage [", '=');

	cout << "\n";

	cout << "Obtaining necessary information..\n";

	show_progress_bar(clog, 100, "Percentage [", '=');

	cout << "\n";

	cout << "Done!";

	Sleep(500);

	system("cls");





	do {


		showMenu();

		cin >> nav;

		system("cls");

		switch (nav) {

		case 1:

			cout << "Please wait...\n";

			show_progress_bar(clog, 100, "Percentage [", '=');

			system("cls");

			equipSelect(); // Takes the current user configuration 
			
			show_progress_bar(clog, 100, "Percentage [", '='); 

			wifiCheck(option);


		case 2:

			cout << "Please wait...\n";

			show_progress_bar(clog, 100, "Percentage [", '=');

			system("cls");

			recentConnection();
		}

	} while (nav != 3 || option == "yes" || option == "no" || option == "return");


	return 0;


}

// Function for Display Menu 
void showMenu() {

	cout << "Welcome to the WIFI Troubleshooter\n";
	cout << "1) Troubleshooter\n";
	cout << "2) Check Most Recent Connection\n";
	cout << "3) Exit\n";
	cout << "Choose an option (1..3) ";


}



// Fucntion for prompting the user to answer a series of wifi troubleshooting questions 
void wifiCheck(string option) {

	cout << "Reboot the computer and try to connect\n";

	do {

		cout << "Did that fix the problem? ";
		cin >> option;

	} while (!(option == "no" || option == "yes" || option == "return"));



	system("cls");

	if (option == "no") {

		cout << "Reboot the router and try to connect\n";

		do {

			cout << "Did that fix the problem? ";
			cin >> option;

		} while (!(option == "no" || option == "yes" || option == "return"));

		system("cls");

		if (option == "no") {

			cout << "Make sure the cables between the router and modem are plugged in firmly\n";

			do {

				cout << "Did that fix the problem? ";
				cin >> option;

			} while (!(option == "no" || option == "yes" || option == "return"));

			system("cls");

			if (option == "no") {

				cout << "Move the router to a new location and try to connect\n";

				do {

					cout << "Did that fix the problem? ";
					cin >> option;

				} while (!(option == "no" || option == "yes" || option == "return"));

				system("cls");

				if (option == "no") {

					cout << "Get a new router\n";
					cout << "----------------\n";
					equipSelect(); // Equipment Select Function Call - for further help 

				}

			}
			else if (option == "yes") {

				cout << "Your wifi is now Working!\n";
				cout << "-------------------------\n";

			}


		}
		else if (option == "yes") {

			cout << "Your wifi is now Working!\n";
			cout << "-------------------------\n";

		}


	}
	else if (option == "yes") {

		cout << "Your wifi is now Working!\n";
		cout << "-------------------------\n";

	}





}

void recentConnection() {

	// Function for checking wifi connection log file for last/most recent connection to internet

	string x; // string used to store the first column in the file (WILL NOT BE USED IN OUTPUT)
	string date;

	ifstream inFile;

	inFile.open("RecentConnection.txt");

	// Loops through all the dates in the file until last date in the file is stored
	while (inFile >> x >> date) {

	}

	// Print the most recent time wifi was connected according to connection log
	cout << "Last known time WIFI was Connected: " << " " << date << endl;
	cout << "-----------------------------------------------" << endl;

	inFile.close();
}

void toolLog() {

	// Function for checking last time tool was running

	// represents the current time on the system 
	time_t currentTime = time(0);

	// Convert current value/time in "currentTime" to a string
	char* dt = ctime(&currentTime);


	// Writing to file for latest run date
	ofstream outFile;

	outFile.open("WifiTroubleshooterLog.txt", std::ios::app);

	if (outFile.is_open()) {

		outFile << "Program Run Date: ";
		outFile << dt;
	}
	else {

		cout << "Log File could not be found" << endl; // Error message for missing log file

	}


	outFile.close();

}



void loginScreen() {

	// Booleans for indicating when password or username is found 
	bool foundusr = false;
	bool foundpass = false;

	string line;

	cout << "Login as Existing User..." << endl;
	cout << endl;

	cout << "Username: ";
	cin >> username;

	cout << "Password: ";
	cin >> password;


	ifstream inFile;


	inFile.open("UsernamesWTS.txt");

	// Search for username in .txt file -- searches line by line 
	while (getline(inFile, line) && !foundusr) {

		if (line.find(username) != string::npos) {

			cout << line << endl;
			foundusr = true; // if the username is found --> foundsur is set to true

			inFile.close(); // close the username text file 

			// If the username exists, check if the password is valid
			if (foundusr) {


				inFile.open("PasswordWTS.txt"); // Open the password .txt file 

				// Searching for the password in the .txt file 
				while (getline(inFile, line) && !foundpass) {

					if (line.find(password) != string::npos) {

						cout << line << endl;
						foundpass = true;

						inFile.close(); // closes password .txt file after the password is found 

						break;


					}

				}

			}
		}

	}
	
	// If the username is not found 
	if (!foundusr) {

		system("cls");

		cout << "ERROR USERNAME NOT FOUND" << endl;

		cout << "Do you want to create a new account (1) or try again (2) ? ";
		cin >> option;

		if (option == "1" || option == "one") {


			createNewUser(); // Allows the user to create new account, if "yes" is input 

		}
		else if (option == "2" || option == "two") {

			system("cls");

			loginScreen();

		}


	}

	// If the password is found incorrect, ask the user to input password again.
	if (!foundpass) {
		

		cout << "ERROR WRONG PASSWORD" << endl;
		cout << " 3 Attempts left" << endl;

		inFile.open("PasswordWTS.txt"); // Open the password file to seach for password 

		// Allow the user to enter the password for a maximum of three times 
		for (int i = 3; i > 0 && !foundpass; i--) {
	
			cout << "Enter the password again - " << "attempts left: " << i << endl;
			cin >> password;

			while (getline(inFile, line) && !foundpass) {

				if (line.find(password) != string::npos) {

					cout << line << endl;

					foundpass = true; // if password is found, set foundpass to true

					inFile.close(); // Close the password .txt file after the password is found 

					break;

				}																									

			}

			if (foundpass) {

				break; 
				foundpass = true; 


			}


		}


	}


					
	if (!foundpass) {

		cout << "MAXED Password attempts" << endl;

		cout << "Do you want to create a new account? ";
		cin >> option;


		if (option == "yes" || option == "Yes") {

			createNewUser(); // Allows the user to create new account, if "yes" is input 
		}
		else {

			exit(0); // Terminates the program 

		}

	}

	



}

// Function for creating new account 
void createNewUser() {

	system("cls"); // clear consosle before displaying the login screen 

	cout << "New User Creation \n";

	// Create a new user  
	cout << "Enter a username: ";
	cin >> username;

	cout << "Enter a password: ";
	cin >> password;

	ofstream outFile;

	// Storing the username in the text file
	outFile.open("UsernamesWTS.txt", std::ios::app);

	if (outFile.is_open()) {

		outFile << username << endl; // Saving the username to the username .txt file
		outFile.close(); // closes the username .txt file

	}
	else {

		cout << "The username file could not be located" << endl;

	}


	// Writing the password to the text file 
	outFile.open("PasswordWTS.txt", std::ios::app);

	if (outFile.is_open()) {

		outFile << password << endl;; // Saving the password to the password .txt file 
		outFile.close(); // Closing the password .txt file

	}
	else {

		cout << "The password file could not be located " << endl;

	}

	cout << "Account was created!" << endl; 



}

// Displays router and modem options that could be configured in customer's home
void customerSetup() {

	cout << "Select the Modem router combo currently in your home: \n" << endl; 

	cout << "Option #: " << setw(20) << "Router: " << setw(20) << "Modem: " << setw(35) <<"Maximum Speed: \n";
	cout << "---------------------------------------------------------------------------\n"; 

	cout << "1) "; 
    cout << setw(35) << "Netgear R6700AX " << setw(21) << "Motorola MB7621 " << setw(19) << "500 Mbps\n"; 
	cout << "2) ";
    cout << setw(34) << "Netgear AC1900 " << setw(22) << "Motorola SB6190 " << setw(29) << "1 Gbps ~ 1000 Mbps\n"; 
    cout << "3) "; 
    cout << setw(34) << "Netgear AX5400 " << setw(19) << "ARRIS SB S33 " << setw(20) << "3 Gbps\n";


}

// Function allows the user to select their current equipment setup 
void equipSelect() {

	int choice;
	int selection; 
	string appt; 

	cout << "Are you a Cable -(1)-  or Digital Subcscirber Line (DSL) -(2)-   Subscriber? \n";
	cout << "\n";
	cout << "Select a choice (1) for first option and (2) for the second option." << endl;
	cin >> choice;

	if (choice == 1) { 

		system("cls");

		customerSetup(); // Displays options for the customer's current confirguration 
		cout << "Which of the listed configurations do you currently have?" << endl; 
		cout << "Option: "; 
		cin >> selection; 

	}
	else if (choice == 2) {

		cout << "Furthur troubleshooting requires a technician. \n";

		do {

			cout << "Would you like to scedule an appointment?: ";
			cin >> appt;


		} while (appt != "yes" || appt != "Yes" || appt != "no" || appt != "No"); 

		if (appt == "Yes" || appt == "yes") {

			cout << "Call Comcast Xfinity @ 1-800-934-6489 or visit customer support @ https://www.xfinity.com/support/contact-us " << endl; 

		}
		else {



		}



	}


}