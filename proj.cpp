#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
#include <iomanip>
#include <windows.h>
#include <stdexcept>
#include <conio.h>
#include <fstream>
using namespace std;

const int NUM_ROWS = 20;    // number of rows, seats, movies and ticket number in the cinema
const int NUM_SEATS = 10;
const int MAX_CINEMAS = 2;
const int MAX_MOVIES = 2;
const int MAX_SEATS = 200;
const int MAX_TIMESLOTS = 3;
const int MAX_TICKET_NUMBER = 9999;
int seats[NUM_ROWS][NUM_SEATS] = {0};

struct Cinema {					//struct for Cinema
    int number;
    int seats[MAX_SEATS];
    int movieIndex;
    string timeSlots[MAX_TIMESLOTS];
};

Cinema cinemas[MAX_CINEMAS];

struct Movie {				//struct for movie
    string title;
    string director;
    string duration;
    int price;
};

Movie movies[MAX_MOVIES];


struct Ticket {			//struct for ticket
    int ticketNumber;
    int cinemaNumber;
    string movieTitle;
    int row;
    int seat;
    int numSeats;
    string timeSlots;
    int price;
};

Ticket tickets[MAX_SEATS];


string login(string& username,string& password) {		//setting up a string for username and password
	system("cls");
	cout << setw(60) << "LOGIN\n";
	cout << setw(50) << "Username:";
	cin.ignore();
	getline(cin, username);
	cout << setw(50) << "Password:";
	getline(cin, password);
    cout << setw(57) << "Welcome! " << username << "."<< endl;
	getch();
    system("cls");
    return username + password;
}														//if username==admin && password==admin then addmovies

void initializeTimeSlots(){
	string slot1, slot2, slot3;
	ifstream file("CinemaTimeSlot1.txt");
	getline(file, slot1);
	cinemas[0].timeSlots[0] = slot1;
	getline(file, slot2);
	cinemas[0].timeSlots[1] = slot2;
	getline(file, slot3);
	cinemas[0].timeSlots[2] = slot3;
	file.close();
	ifstream ifile("CinemaTimeSlot2.txt");
	getline(ifile, slot1);
	cinemas[1].timeSlots[0] = slot1;
	getline(ifile, slot2);
	cinemas[1].timeSlots[1] = slot2;
	getline(ifile, slot3);
	cinemas[1].timeSlots[2] = slot3;
	ifile.close();
}

int addMovies() {										//function for adding a movie, title, director, duration, and price
string title, director;
	for (int i = 0; i < MAX_MOVIES; i++) {
		        cout << setw(60) << "Movie " << (i + 1) << endl;
		        cout << setw(60) << "Title: ";
		        cin.ignore();
		    	getline (cin, title);
		    	movies[i].title = title;
		        cout << setw(60) << "Director: ";
		    	getline (cin, director);
				movies[i].director = director;
		    	cout << setw(60) << "Duration (in minutes): ";
		    	cin >> movies[i].duration;
		    	cout << setw(60) << "Price: ";
		    	cin >> movies[i].price;
		    		if (!title.empty()){
    				cinemas[i].movieIndex++;
    				}
		}
	cout << setw(60) << "Movies added successfully!\n";
	getch();
	system("cls");
	return cinemas[MAX_CINEMAS].movieIndex;
}
	
void changeMovies() {						//function to change a movie
int choice;
do {
cout << setw(60) << "Change Movies\n";
for (int i = 0; i < MAX_MOVIES; i++) {
cout << setw(60) << (i + 1) << ". " << movies[i].title << endl;
}
cout << setw(60) << "0. Back\n";
cout << setw(60) << "Enter choice: ";
cin >> choice;
    if (choice >= 1 && choice <= MAX_MOVIES) {
        int index = choice - 1;
        cout << setw(60) << "Movie " << (index + 1) << endl;
        cout << setw(60) << "Title: " << movies[index].title << endl;
        cout << setw(60) << "Director: " << movies[index].director << endl;
        cout << setw(60) << "Duration (minutes): " << movies[index].duration << endl;
        cout << setw(60) << "Price: " << movies[index].price << endl;
        cout << setw(60) << "Enter new values (or leave blank to keep current values):\n";
        cout << setw(60) << "Title: ";
        string title;
        cin.ignore();
        getline(cin, title);
        if (!title.empty()) {
            movies[index].title = title;
        }
        cout << setw(60) << "Director: ";
        string director;
        getline(cin, director);
        if (!director.empty()) {
            movies[index].director = director;
        }
        cout << setw(60) << "Duration (minutes): ";
        string durationStr;
        getline(cin, durationStr);
        if (!durationStr.empty()) {
            int duration = stoi(durationStr);
            movies[index].duration = duration;
        }
        cout << setw(60) << "Price: ";
        string priceStr;
        getline(cin, priceStr);
        if (!priceStr.empty()) {
            int price = stoi(priceStr);
            movies[index].price = price;
        }
        cout << setw(60) << "Movie updated.\n";
    } else if (choice != 0) {
        cout << setw(60) << "Invalid choice.\n";
    }
    system("cls");
} while (choice != 0);
}
	

int cinema1TimeSlot1[NUM_ROWS][NUM_SEATS] = {0};
int cinema1TimeSlot2[NUM_ROWS][NUM_SEATS] = {0};
int cinema1TimeSlot3[NUM_ROWS][NUM_SEATS] = {0};
int cinema2TimeSlot1[NUM_ROWS][NUM_SEATS] = {0};
int cinema2TimeSlot2[NUM_ROWS][NUM_SEATS] = {0};
int cinema2TimeSlot3[NUM_ROWS][NUM_SEATS] = {0};

void showMovies(){
	for(int i=0; i<MAX_MOVIES; i++){
	cout << setw(60) << "Movie " << i+1 << endl;
	cout << setw(60) << "Title:" << movies[i].title << endl;
	cout << setw(60) << "Director:" << movies[i].director << endl;
	cout << setw(60) << "Duration:" << movies[i].duration << endl;
	cout << setw(60) << "Price:" << movies[i].price << endl;
}
getch();
system("cls");	
}

void printSeats(int cinemaNum, int timeslot) {					//function for printing seats 
    cout << setw(51);
	cout << "     ";
    for (int i = 1; i <= NUM_SEATS; i++) {
        cout << i << " ";
    }
    cout << endl;
    for (int i = 0; i < NUM_ROWS; i++) {
        cout << setw(50) << "Row " << i+1 << " ";
        for (int j = 0; j < NUM_SEATS; j++) {
            if (cinemaNum == 1) {
            	if(timeslot==1){
            cout << cinema1TimeSlot1[i][j] << " ";
        }
        	else if(timeslot==2){
            cout << cinema1TimeSlot2[i][j] << " ";
        }
        	else if(timeslot==3){
            cout << cinema1TimeSlot3[i][j] << " ";
        }
            } else if (cinemaNum == 2) {
            	if(timeslot==1){
            cout << cinema2TimeSlot1[i][j] << " ";
        }
        	else if(timeslot==2){
            cout << cinema2TimeSlot2[i][j] << " ";
        }
        	else if(timeslot==3){
            cout << cinema2TimeSlot3[i][j] << " ";
        } 
        else{
        cout << setw(51) << "INVALID CINEMA" << endl;
		}
    }
}
        cout << endl;
}
    cout << endl;
    cout << setw(74) << "===========SCREEN===========" << endl;
}


int buyTicket(){						//function for buying a ticket 
	int cinemaindex;
	int payment;
	int price=0;
	int change;
	int numSeats;
	int row, seat;
	int ticketNumber = rand()% MAX_TICKET_NUMBER + 1;
	do {
	cout << setw(65) << "Buy Ticket\n";
		for (int i = 0; i < MAX_CINEMAS; i++) {
	cout << setw(50) << (i + 1) << ". Cinema " << cinemas[i].number;
	if (cinemas[i].movieIndex != -1) {
	cout << " (" << movies[i].title << ")";
	}
	cout << endl;
	}
	cout << setw(65) << "0. Back\n";
	cout << setw(65) << "Enter choice: ";
	cin >> cinemaindex;
	system("cls");
	    if (cinemaindex >= 1 && cinemaindex <= MAX_CINEMAS) {
	        int index = cinemaindex - 1;
	        if (cinemas[index].movieIndex == -1) {
	        	cout << setw(65) << "No movie is currently showing in this cinema.\n";
	continue;
	}
	cout << setw(65) << "Cinema " << cinemas[index].number << endl;
	cout << setw(65) << "Movie: " << movies[index].title << endl;
	cout << setw(65) << "Director: " << movies[index].director << endl;
	cout << setw(65) << "Time: " << movies[index].duration << endl;
	cout << setw(65) << "Price: " << movies[index].price << endl;
	do {
	cout << setw(75) << "Number of tickets to buy (1-" << MAX_SEATS << "): ";
	cin >> numSeats;
	if (numSeats < 1 || numSeats > MAX_SEATS) {
	cout << setw(65) << "Invalid number of tickets.\n";
	system("cls");
	}
	} while (numSeats < 1 || numSeats > MAX_SEATS);
	int availableSeats = 0;
	  price = numSeats * movies[index].price;
	  cout << setw(65) << "Price:" << price << endl;
	  cout << setw(65) << "Payment:";
	  cin >> payment;
	  if(payment < price){
		cout << setw(68) << "Purchase failed.\n";
		getch();
		system("cls");
    	continue;
	  }
	  bool seatReserved = false;
	  	string filename;
	  	if(cinemaindex==1){
		filename = "CinemaTimeSlot1.txt";
	}
	else if(cinemaindex==2){
		filename = "CinemaTimeSlot2.txt";
	}
	else{
	    cout << "Invalid cinema choice" << endl;
        break;
	}
	ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file " << filename << endl;
        break;
    }
    cout << setw(70) << "Available time slots:" << endl;
    string line;
    int slot_number = 1;
    while (getline(file, line)) {
        cout << setw(50) << slot_number << ". " << line << endl;
        slot_number++;
    }
      int time_slot_choice;
    cout << setw(65) << "Choose a time slot: ";
    cin >> time_slot_choice;
    file.clear(); // reset the file's error state
    file.seekg(0, ios::beg); // move file pointer back to the beginning of the file
    int slot_index = 0;
    while (getline(file, line)) {
        if (slot_index == time_slot_choice - 1) {
            cout << setw(50) << "You Picked: " << line << endl;
            file.close();
			break;
        }
        slot_index++;
    }
        if(time_slot_choice > 3 || time_slot_choice < 1){
        cout << setw(50) << "INVALID";
        continue;
		}

	printSeats(cinemaindex, time_slot_choice);   
	for (int i = 0; i < numSeats; i++) {
	ticketNumber = rand()% MAX_TICKET_NUMBER + 1;
	if(payment >= price){
	  do{ 
if (cinemaindex == 1) {
	if(time_slot_choice == 1){
        cout << setw(65) << "Enter Row: ";
        cin >> row;
        cout << setw(66) << "Enter Seat: ";
        cin >> seat;
        if(row < 20 && seat < 10){
        if (cinema1TimeSlot1[row-1][seat-1] == 0) {
            cinema1TimeSlot1[row-1][seat-1] = 1;
            cout << setw(45) << "Seat " << row << "-" << seat << " in cinema 1 has been reserved." << endl;
            seatReserved = true;
            	tickets[index].ticketNumber = ticketNumber;
				tickets[index].cinemaNumber = cinemas[index].number;
				tickets[index].movieTitle = movies[index].title;
            	tickets[index].row = row;
				tickets[index].seat = seat;
				tickets[index].timeSlots = line;
				tickets[index].numSeats = numSeats;
		}	else {
            cout << setw(45) << "Seat " << row << "-" << seat << " in cinema 1 is already reserved. Please choose another seat." << endl;
            seatReserved = false;
            continue;
        }
	}
	else{
	cout << setw(60) << "INVALID ROW AND SEAT" << endl;
	continue;
	}
        }
       	else if(time_slot_choice == 2){
        cout << setw(65) << "Enter Row: ";
        cin >> row;
        cout << setw(66) << "Enter Seat: ";
        cin >> seat;
        if(row < 20 && seat < 10){
        if (cinema1TimeSlot2[row-1][seat-1] == 0) {
            cinema1TimeSlot2[row-1][seat-1] = 1;
            cout << setw(45) << "Seat " << row << "-" << seat << " in cinema 1 has been reserved." << endl;
            seatReserved = true;
        		tickets[index].ticketNumber = ticketNumber;
				tickets[index].cinemaNumber = cinemas[index].number;
				tickets[index].movieTitle = movies[index].title;
            	tickets[index].row = row;
				tickets[index].seat = seat;
				tickets[index].timeSlots = line;
				tickets[index].numSeats = numSeats;
		}	else {
            cout << setw(45) << "Seat " << row << "-" << seat << " in cinema 1 is already reserved. Please choose another seat." << endl;
            seatReserved = false;
            continue;
        }
		}
	else{
	cout << setw(50) << "INVALID ROW AND SEAT" << endl;
	continue;
	} 
        }
        else if(time_slot_choice == 3){
        cout << setw(65) << "Enter Row: ";
        cin >> row;
        cout << setw(66) << "Enter Seat: ";
        cin >> seat;
        if(row < 20 && seat < 10){
        if (cinema1TimeSlot3[row-1][seat-1] == 0) {
            cinema1TimeSlot3[row-1][seat-1] = 1;
            cout << setw(45) << "Seat " << row << "-" << seat << " in cinema 1 has been reserved." << endl;
            seatReserved = true;
        		tickets[index].ticketNumber = ticketNumber;
				tickets[index].cinemaNumber = cinemas[index].number;
				tickets[index].movieTitle = movies[index].title;
            	tickets[index].row = row;
				tickets[index].seat = seat;
				tickets[index].numSeats++;
				tickets[index].timeSlots = line;
				tickets[index].numSeats = numSeats;
	}	else {
            cout << setw(45) << "Seat " << row << "-" << seat << " in cinema 1 is already reserved. Please choose another seat." << endl;
            seatReserved = false;
            continue;
        }
    	}
	else{
	cout << setw(50) << "INVALID ROW AND SEAT" << endl;
	continue;
	} 
	}
} else if (cinemaindex == 2) {
	if(time_slot_choice == 1){
        cout << setw(65) << "Enter Row: ";
        cin >> row;
        cout << setw(66) << "Enter Seat: ";
        cin >> seat;
        if(row < 20 && seat < 10){
        if (cinema2TimeSlot1[row-1][seat-1] == 0) {
            cinema2TimeSlot1[row-1][seat-1] = 1;
            cout << setw(45) << "Seat " << row << "-" << seat << " in cinema 2 has been reserved." << endl;
            seatReserved = true;
        		tickets[index].ticketNumber = ticketNumber;
				tickets[index].cinemaNumber = cinemas[index].number;
				tickets[index].movieTitle = movies[index].title;
            	tickets[index].row = row;
				tickets[index].seat = seat;
				tickets[index].numSeats++;
				tickets[index].timeSlots = line;
				tickets[index].numSeats = numSeats;
		}	else {
            cout << setw(45) << "Seat " << row << "-" << seat << " in cinema 2 is already reserved. Please choose another seat." << endl;
            seatReserved = false;
            continue;
        }
		}
		else{
		cout << setw(50) << "INVALID ROW AND SEAT" << endl;
		continue;
		}  
        }
       	else if(time_slot_choice == 2){
        cout << setw(65) << "Enter Row: ";
        cin >> row;
        cout << setw(66) << "Enter Seat: ";
        cin >> seat;
        if(row < 20 && seat < 10){
        if (cinema2TimeSlot2[row-1][seat-1] == 0) {
            cinema2TimeSlot2[row-1][seat-1] = 1;
            cout << setw(45) << "Seat " << row << "-" << seat << " in cinema 2 has been reserved." << endl;
            seatReserved = true;
        		tickets[index].ticketNumber = ticketNumber;
				tickets[index].cinemaNumber = cinemas[index].number;
				tickets[index].movieTitle = movies[index].title;
            	tickets[index].row = row;
				tickets[index].seat = seat;
				tickets[index].numSeats++;
				tickets[index].timeSlots = line;
				tickets[index].numSeats = numSeats;
		}	else {
            cout << setw(45) << "Seat " << row << "-" << seat << " in cinema 2 is already reserved. Please choose another seat." << endl;
            seatReserved = false;
            continue;
        }
		}
		else{
		cout << setw(50) << "INVALID ROW AND SEAT" << endl;
		continue;
		}   
        }
        else if(time_slot_choice == 3){
        cout << setw(65) << "Enter Row: ";
        cin >> row;
        cout << setw(66) << "Enter Seat: ";
        cin >> seat;
        if(row < 20 && seat < 10){
        if (cinema2TimeSlot3[row-1][seat-1] == 0) {
            cinema2TimeSlot3[row-1][seat-1] = 1;
            cout << setw(45) << "Seat " << row << "-" << seat << " in cinema 2 has been reserved." << endl;
            seatReserved = true;
        		tickets[index].ticketNumber = ticketNumber;
				tickets[index].cinemaNumber = cinemas[index].number;
				tickets[index].movieTitle = movies[index].title;
            	tickets[index].row = row;
				tickets[index].seat = seat;
				tickets[index].numSeats++;
				tickets[index].timeSlots = line;
				tickets[index].numSeats = numSeats;
	}	else {
            cout << setw(45) << "Seat " << row << "-" << seat << " in cinema 2 is already reserved. Please choose another seat." << endl;
            seatReserved = false;
            continue;
        }
    	}
		else{
		cout << setw(50) << "INVALID ROW AND SEAT" << endl;
		continue;
		} 
	}
}
}while(!seatReserved);
} else {
    cout << setw(65) << "Purchase failed.\n";
    break;
}
availableSeats++;
}
	if (numSeats > availableSeats) {
	cout << setw(50) << "There are not enough available seats.\n";
	continue;
	}
	cout << setw(65)<< "Seats reserved" << endl;
    cout << setw(57) << "Change:" << payment - price << endl;
    cout << setw(65) << "Ticket Number: " << ticketNumber << endl;
    tickets[index].price = price;
    tickets[index].ticketNumber = ticketNumber;
    cout << setw(65) << "Purchase successful.\n";
    getch();
    system("cls");
	} else if (cinemaindex != 0) {
	cout << setw(65) << "Invalid choice.\n";
	}
	}while (cinemaindex != 0);
return numSeats;
}	
	
		
void lookupTicket() { //searches ticket 
    int ticketNumber;
    cout << setw(65) << "Lookup Ticket\n";
    do {
        cout << setw(65) << "Enter ticket number (1-" << MAX_TICKET_NUMBER << "): ";
        cin >> ticketNumber;
        if (ticketNumber < 1 || ticketNumber > MAX_TICKET_NUMBER) {
            cout << setw(65) << "Invalid ticket number.\n";
        }
    } while (ticketNumber < 1 || ticketNumber > MAX_TICKET_NUMBER);

    bool found = false;
    for (int i = 0; i < MAX_SEATS; i++) {
        if (tickets[i].ticketNumber == ticketNumber) {
            found = true;
            cout << setw(65) << "Ticket Found:\n";
            cout << setw(65) << "Ticket Number: " << tickets[i].ticketNumber << endl;
            cout << setw(65) << "Cinema Number: " << tickets[i].cinemaNumber << endl;
            cout << setw(65) << "Movie Title: " << tickets[i].movieTitle << endl;
            cout << setw(65) << "Time: " << tickets[i].timeSlots << endl;
            cout << setw(65) << "Seats Reserved: " << tickets[i].numSeats << endl;
            cout << setw(65) << "Price: " << tickets[i].price << endl;
}
}
    if (!found) {
        cout << setw(65) << "Ticket not found.\n";
    }
    getch();
    system("cls");
}


int main() {
system("Color 0A");
int choice;
int cinemaindex;
int numMovies = 0;
int row, seat;
int cinemaNum;
string username, password;
srand(time(NULL));//Initalizes RandomNumber Generator

for (int i = 0; i < MAX_CINEMAS; i++) {
        cinemas[i].number = i + 1;
        cinemas[i].movieIndex = -1;
        for (int j = 0; j < MAX_SEATS; j++) {
            cinemas[i].seats[j] = 0;
        }
    }//initializes cinema struct
    
string authUser, authPass;
ifstream inputfile("login.txt");
getline(inputfile, authUser);
getline(inputfile, authPass);
inputfile.close();
//initialize admin credentials

do{
	try{
 	    cout << setw(40) << "*" << setw(20) << "Main Menu" << setw(10) << "*" << endl; 
        cout << setw(40) << "*" << setw(15) << "1. Login" << setw(15) << "*" << endl;
        cout << setw(40) << "*" << "       2. Add Movies" << setw(10) << "*" << endl;
        cout << setw(40) << "*" << "       3. Change Movies" << setw(7) << "*" << endl;
        cout << setw(40) << "*" << setw(21) << "4. Show Movies" << setw(9) << "*" << endl;
        cout << setw(40) << "*" << setw(20) << "5. Buy Ticket" << setw(10) << "*" << endl;
        cout << setw(40) << "*" << setw(20) << "6. View Seats" << setw(10) << "*" << endl;
		cout << setw(40) << "*" << setw(24) << "7. Look Up Ticket" << setw(6) << "*" << endl;    
        cout << setw(40) << "*" << setw(14) << "0. Exit" << setw(16) <<  "*" << endl;
        cout << setw(60) << "Enter choice: ";
        cin >> choice;
        system("cls");
        switch (choice){
            case 1:
                login(username, password);//login 
       		    break;
            case 2:
            	if (username == authUser && password == authPass){
   				cinemaindex = addMovies();
   				}
        		else {
           		cout << setw(65) << "YOU ARE NOT AUTHORIZED TO ACCESS THIS! PRESS ANY KEY TO CONTINUE" << endl;
           		getch();
           		system("cls");
				}
			break;
			case 3:
            if(username == authUser && password == authPass){
            changeMovies();
       		}
            else{
            cout << setw(65) << "YOU ARE NOT AUTHORIZED TO ACCESS THIS" << endl;
            getch();
            system("cls");
			}
			break;
			case 4:
			showMovies();
			break;
			case 5:
			buyTicket();//buy ticket function
			system("cls");
			break;
			case 6:
			int timeslot;
			system("cls");
			for (int i = 0; i < MAX_CINEMAS; i++) {
			cout << setw(50) << (i + 1) << ". Cinema " << cinemas[i].number;
			if (cinemas[i].movieIndex != -1) {
			cout << " (" << movies[i].title << ")";
			}
			cout << endl;
			}
			cout << setw(60) << "Enter Cinema:";
			cin >> cinemaNum;
			if(cinemaNum == 1){
			ifstream infile("CinemaTimeSlot1.txt");
			string perLine;
			int slots = 1;
			while(getline(infile, perLine)){
			cout << setw(50) << slots << ". " << perLine << endl;
			slots++;
			}
			infile.close();
			}
			else if(cinemaNum == 2){
			ifstream infile("CinemaTimeSlot2.txt");
			string perLine;
			int slots = 1;
			while(getline(infile, perLine)){
			cout << setw(50) << slots << ". " << perLine << endl;
			slots++;
			}
			infile.close();
			}
			cout << setw(60) << "Enter Timeslot:";
			cin >> timeslot;
			if (cinemaNum == 1){
			system("cls");
			cout << setw(70) << "SEATS FOR TIMESLOT " << timeslot << endl;  
			printSeats(1, timeslot);
			getch();
			system("cls");
			break;
			system("cls");	
			}
			else if (cinemaNum == 2){
			system("cls");
			cout << setw(70) << "SEATS FOR TIMESLOT " << timeslot << endl;  
			printSeats(2, timeslot);
			getch();
			system("cls");
			break;
			system("cls");	
			}
			break;
			case 7:
   		 	lookupTicket();
    		break;
    		
    	case 0:
    		return 0;
    		break;
    		
            default:
                cout << setw(80) << "Invalid choice. Press any key to continue.";
                	getch();
   					system("cls");
    	}
    }
   		catch(const invalid_argument& e){
   			cout << setw(65) << "Invalid choice. Press any key to continue\n";
   			getch();
   			system("cls");
		}
        }while(true);
	
}
