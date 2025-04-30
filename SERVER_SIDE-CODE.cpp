#include <WS2tcpip.h>
#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
#include <string>
#include <tchar.h>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <cstring>
#include <fstream>
#include <sstream>
std::mutex mut;
std::timed_mutex tmut;
std::mutex sender;
std::mutex receiver;
std::condition_variable cv;
std::condition_variable connection_break;
#pragma comment(lib, "ws2_32.lib")
using namespace std;
sockaddr_in sockinfo;
// condition_variable checking;
static SOCKET connected_socket = SOCKET_ERROR;
static int connection_flag = 1;
//
//
stringstream ticket;
string req = "";
string res = "";
int func_no = 0;
int line_no = 0;
int tourist_flag;

class tourist
{
    const int id;
    string name;
    int age;
    unsigned long long phone;
    char gender;
    string nationality;
    static int count;
    string plann;
    string destinationn;
    string hotel;
    float cost;
    double plan_cost;
    double hotel_cost;
    double total_cost;
    string path;
    static string* tourist_msg;

public:
    void set_ticket()
    {
        ticket << "\n\n \t\t\t Service ===> OOP TRAVELS \n";
        ticket << "ID: " << id << endl
            << "Name: " << name << endl
            << "Age: " << age << endl;
        ticket << "Phone: " << phone << endl
            << "Gender: " << gender << endl;
        ticket << "Nationality: " << nationality << endl
            << "Plan: " << plann << endl;
        ticket << "Destination: " << destinationn << endl
            << "Hotel: " << hotel << endl;
        ticket << "Plan Cost: " << plan_cost << endl
            << "Hotel Cost: " << hotel_cost << endl;
        ticket << "Total Cost: " << total_cost << endl;
        res = ticket.str();
    }
    void set_messages()
    {

        tourist_msg[0] = "Enter name: \n";
        tourist_msg[1] = "\n Note: Age must be greater than 18 to travel for tourist \n Enter age: \n";
        tourist_msg[2] = "Enter phone number: \n";
        tourist_msg[3] = "Enter gender (M/F): \n";
        tourist_msg[4] = "Enter nationality: \n";
        tourist_msg[5] = "Invalid destination!\n";
        tourist_msg[6] = "Invalid input. Please enter a valid age (0-120): \n";
        tourist_msg[7] = "Invalid input. Please enter a 10-digit phone number: \n";
        tourist_msg[8] = "Invalid input. Please enter either 'M' or 'F' for gender: \n";
        tourist_msg[9] = "Here are the available travel destinations:\n1. Paris\n2. Rome\n3. Tokyo\n4. Bali\n5. New York\nEnter the destination number for more details: \n";
        tourist_msg[10] = "Tour to Paris\nChoose your plan:\n1. Standard Plan\n2. Premium Plan\nEnter your choice: \n";
        tourist_msg[11] = "Here are the available travel destinations:\n1. Paris\n2. Rome\n3. Tokyo\n4. Bali\n5. New York\nEnter the destination number for more details: \n";
        tourist_msg[12] = "---> Details for Standard Plan in Paris:\n---> Duration: 5 days\n---> Cost: $1000\n---> Details: Explore the beautiful city of Paris, including visits to the Eiffel Tower, Louvre Museum, and more.\n\n\n Press Enter To Proceed To Hotels\n";
        tourist_msg[13] = "---> Details for Premium Plan in Paris:\n---> Duration: 7 days\n---> Cost: $2000\n---> Details: Experience luxury in Paris with exclusive tours, gourmet dining, and personalized experiences.\n\n\n Press Enter To Proceed To Hotels\n";
        tourist_msg[14] = "Tour to Rome\nChoose your plan:\n1. Standard Plan\n2. Premium Plan\nEnter your choice: \n";
        tourist_msg[15] = "---> Details for Standard Plan in Rome:\n---> Duration: 7 days\n---> Cost: $1500\n---> Details: Discover the ancient ruins of Rome, including the Colosseum, Roman Forum, and Vatican City.\n\n\n Press Enter To Proceed To Hotels\n";
        tourist_msg[16] = "---> Details for Premium Plan in Rome:\n---> Duration: 10 days\n---> Cost: $2500\n---> Details: Explore Rome in luxury with private tours, VIP access, and deluxe accommodations.\n\n Press Enter To Proceed To Hotels\n\n";
        tourist_msg[17] = "Tour to Tokyo\nChoose your plan:\n1. Standard Plan\n2. Premium Plan\nEnter your choice: \n";
        tourist_msg[18] = "---> Details for Standard Plan in Tokyo:\n---> Duration: 10 days\n---> Cost: $2000\n---> Details: Experience the vibrant culture of Tokyo, with visits to shrines, temples, and bustling neighborhoods.\n\n\n Press Enter To Proceed To Hotels\n";
        tourist_msg[19] = "---> Details for Premium Plan in Tokyo:\n---> Duration: 14 days\n---> Cost: $3500\n---> Details: Immerse yourself in luxury in Tokyo with exclusive experiences, Michelin-starred dining, and private guide.\n\n\n Press Enter To Proceed To Hotels\n";
        tourist_msg[20] = "Tour to Bali\nChoose your plan:\n1. Standard Plan\n2. Premium Plan\nEnter your choice: \n";
        tourist_msg[21] = "---> Details for Standard Plan in Bali:\n---> Duration: 7 days\n---> Cost: $1200\n---> Details: Explore the beautiful beaches and rich culture of Bali with this standard plan.\n\n\n Press Enter To Proceed To Hotels\n";
        tourist_msg[22] = "---> Details for Premium Plan in Bali:\n---> Duration: 10 days\n---> Cost: $2500\n---> Details: Indulge in luxury with exclusive experiences and accommodations in Bali.\n\n\n Press Enter To Proceed To Hotels\n";
        tourist_msg[23] = "Tour to New York\nChoose your plan:\n1. Standard Plan\n2. Premium Plan\nEnter your choice: \n";
        tourist_msg[24] = "---> Details for Standard Plan in New York: \n---> Duration: 5 days.\n---> Cost: $1800\n---> Details: Explore the iconic landmarks and vibrant culture of New York City \n\n\n Press Enter To Proceed To Hotels\n";
        tourist_msg[25] = "---> Details for Premium Plan in New York:\n---> DDuration: 7 days\n ---> Cost: $3500\n---> Details: Experience luxury with VIP access, exclusive experiences, and deluxe accommodations in New York.\n\n\n Press Enter To Proceed To Hotels\n";
        tourist_msg[26] = "\tFamous hotels in Paris for your plan:\n 1. Hotel Ritz - $2000/night\n 2. The Peninsula Paris - $1800/night\n 3. Hotel Plaza Ath�n�e - $1700/night\n";
        tourist_msg[27] = "\tLuxury hotels in Paris for your plan:\n 1. Hotel de Crillon - $3000/night\n 2. Le Meurice - $2800/night\n 3. Shangri-La Hotel Paris - $2700/night\n";
        tourist_msg[28] = "\tFamous hotels in Rome for your plan:\n 1. Hotel Hassler Roma - $1600/night\n 2. Hotel Eden - $1500/night\n 3. Rome Cavalieri, A Waldorf Astoria Hotel - $1400/night\n";
        tourist_msg[29] = "\tLuxury hotels in Rome for your plan:\n 1. Grand Hotel Plaza - $2500/night\n 2. Hotel de Russie - $2400/night\n 3. Palazzo Manfredi - Small Luxury Hotels of the World - $2300/night\n";
        tourist_msg[30] = "\tStandard hotels in Tokyo for your plan:\n 1. Park Hyatt Tokyo - $1800/night\n 2. The Peninsula Tokyo - $1700/night\n 3. Mandarin Oriental, Tokyo - $1600/night\n";
        tourist_msg[31] = "\tLuxury hotels in Tokyo for your plan:\n 1. The Tokyo Station Hotel - $2500/night\n 2. Andaz Tokyo Toranomon Hills - $2400/night\n 3. Conrad Tokyo - $2300/night\n";
        tourist_msg[32] = "\tStandard hotels in Bali for your plan:\n 1. AYANA Resort and Spa Bali - $1400/night\n 2. Four Seasons Resort Bali at Sayan - $1300/night\n 3. The Mulia Bali - $1200/night\n";
        tourist_msg[33] = "\tLuxury hotels in Bali for your plan:\n 1. Alila Villas Uluwatu - $2200/night\n 2. COMO Uma Ubud - $2100/night\n 3. Mandapa, a Ritz-Carlton Reserve - $2000/night\n";
        tourist_msg[34] = "\tStandard hotels in New York for your plan:\n 1. The Plaza Hotel - $2000/night\n 2. The New Yorker, A Wyndham Hotel - $1800/night\n 3. Hilton Times Square - $1700/night\n";
        tourist_msg[35] = "\tLuxury hotels in New York for your plan:\n 1. The Plaza Hotel - $3000/night\n 2. Mandarin Oriental, New York - $2800/night\n 3. The St. Regis New York - $2700/night\n";
    }
    string get_msg_T(int i)
    {
        string temp;
        temp = tourist_msg[i];
        return temp;
    }

    void set_name()
    {
        // system("cls");
        func_no = 3;
        name = req;
        res = get_msg_T(1);
    }
    string get_name() const
    {
        return name;
    }
    void set_age()
    {
        func_no = 4;
        age = stoi(req);

        if (age >= 18 && age < 120)
        {

            res = get_msg_T(2);
        }
        else
        {
            // res = get_msg_T(6);
            res = "";
        }
    }
    void set_phone()
    {
        func_no = 5;
        phone = stoi (req);
        res = get_msg_T(3);
    }

    void set_gender()
    {
        func_no = 6;
        char g = req[0];
        if (g == 'M' || g == 'F')
        {
            gender = g;
            res = get_msg_T(4);
        }
        else
        {
            res = "";
        }
    }
    void set_nationality()
    {
        func_no = 7;
        nationality = req;
        res = get_msg_T(9);
    }

    void set_plann()
    {
        func_no = 9;
        if (stoi(req) == 1)
        {
            plann = "standard"; // Assigning string directly
            if (destinationn == "Paris")
            {
                res = get_msg_T(12);
            }
            else if (destinationn == "Rome")
            {
                res = get_msg_T(15);
            }
            else if (destinationn == "Tokyo")
            {
                res = get_msg_T(18);
            }
            else if (destinationn == "Bali")
            {
                res = get_msg_T(21);
            }
            else if (destinationn == "New York")
            {
                res = get_msg_T(24);
            }
            else
            {
                // res = get_msg_T(5);
                res = "";
            }
        }
        else if (stoi(req) == 2)
        {
            plann = "Premium"; // Assigning string directly
            if (destinationn == "Paris")
            {
                res = get_msg_T(13);
            }
            else if (destinationn == "Rome")
            {
                res = get_msg_T(16);
            }
            else if (destinationn == "Tokyo")
            {
                res = get_msg_T(19);
            }
            else if (destinationn == "Bali")
            {
                res = get_msg_T(22);
            }
            else if (destinationn == "New York")
            {
                res = get_msg_T(25);
            }
            else
            {
                // res = get_msg_T(5);
                res = "";
            }
        }
        else
        {
            res = ""; // Handle invalid input
        }
    }

    void set_hotels()
    {
        func_no = 10;
        if (destinationn == "Paris" && plann == "standard")
        {
            res = get_msg_T(26);
            if (stoi(req) == 1)
            {
                hotel = "Hotel Ritz";
            }
        }
        else if (destinationn == "Paris" && plann == "Premium")
        {
            res = get_msg_T(27);
            hotel = req;
        }
        else if (destinationn == "Rome" && plann == "standard")
        {
            res = get_msg_T(28);
        }
        else if (destinationn == "Rome" && plann == "Premium")
        {
            res = get_msg_T(29);
            hotel = req;
        }
        else if (destinationn == "Tokyo" && plann == "standard")
        {
            res = get_msg_T(30);
            hotel = req;
        }
        else if (destinationn == "Tokyo" && plann == "Premium")
        {
            res = get_msg_T(31);
            hotel = req;
        }
        else if (destinationn == "Bali" && plann == "standard")
        {
            res = get_msg_T(32);
            hotel = req;
        }
        else if (destinationn == "Bali" && plann == "Premium")
        {
            res = get_msg_T(33);
            hotel = req;
        }
        else if (destinationn == "New York" && plann == "standard")
        {
            res = get_msg_T(34);
            hotel = req;
        }
        else if (destinationn == "New York" && plann == "Premium")
        {
            res = get_msg_T(35);
            hotel = req;
        }
        else
        {
            res = ""; // Handle invalid input
        }
    }

    void set_d()
    {
        func_no = 8;
        int d;
        d = stoi(req);
        switch (d)
        {
        case 1: // Use int values for switch cases
            destinationn = "Paris";
            res = get_msg_T(10);
            break;
        case 2:
            destinationn = "Rome";
            res = get_msg_T(10);
            break;
        case 3:
            destinationn = "Tokyo";
            res = get_msg_T(10);
            break;
        case 4:
            destinationn = "Bali";
            res = get_msg_T(10);
            break;
        case 5:
            destinationn = "New York";
            res = get_msg_T(10);
            break;
        default:
            cout << "Invalid destination" << endl;
            res = "";
            break;
        }
    }

    void set_plan_cost()
    {
        if (plann == "standard")
        {
            switch (destinationn[0])
            {
            case 'P':
                plan_cost = 1000;
                break;
            case 'R':
                plan_cost = 1500;
                break;
            case 'T':
                plan_cost = 2000;
                break;
            case 'B':
                plan_cost = 1200;
                break;
            case 'N':
                plan_cost = 1800;
                break;
            default:
                // Handle invalid destination
                break;
            }
        }
        else if (plann == "Premium")
        {
            switch (destinationn[0])
            {
            case 'P':
                plan_cost = 2000;
                break;
            case 'R':
                plan_cost = 2500;
                break;
            case 'T':
                plan_cost = 3500;
                break;
            case 'B':
                plan_cost = 2500;
                break;
            case 'N':
                plan_cost = 3500;
                break;
            default:
                // Handle invalid destination
                break;
            }
        }
        else
        {
            // Handle invalid plan
            res = "";
        }
    }

    void set_hotel_cost() {
        if (destinationn == "Paris") {
            if (plann == "standard") {
                if (hotel == "Hotel Ritz") {
                    hotel_cost = 2000;
                }
                else if (hotel == "The Peninsula Paris") {
                    hotel_cost = 1800;
                }
                else if (hotel == "Hotel Plaza Ath�n�e") {
                    hotel_cost = 1700;
                }
                else {
                    hotel_cost = 0;
                }
            }
            else if (plann == "Premium") {
                if (hotel == "Hotel de Crillon") {
                    hotel_cost = 3000;
                }
                else if (hotel == "Le Meurice") {
                    hotel_cost = 2800;
                }
                else if (hotel == "Shangri-La Hotel Paris") {
                    hotel_cost = 2700;
                }
                else {
                    hotel_cost = 0;
                }
            }

        }//

        else if (destinationn == "Rome") {
            if (plann == "standard") {
                if (hotel == "Hotel Hassler Roma") {
                    hotel_cost = 1600;
                }
                else if (hotel == "Hotel Eden") {
                    hotel_cost = 1500;
                }
                else if (hotel == "Rome Cavalieri, A Waldorf Astoria Hotel") {
                    hotel_cost = 1400;
                }
                else {
                    hotel_cost = 0;
                }
            }
            else if (plann == "Premium") {
                if (hotel == "Grand Hotel Plaza") {
                    hotel_cost = 2500;
                }
                else if (hotel == "Hotel de Russie") {
                    hotel_cost = 2400;
                }
                else if (hotel == "Palazzo Manfredi - Small Luxury Hotels of the World") {
                    hotel_cost = 2300;
                }
                else {
                    hotel_cost = 0;
                }
            }
        }//

        else if (destinationn == "Tokyo") {
            if (plann == "standard") {
                if (hotel == "Park Hyatt Tokyo") {
                    hotel_cost = 1800;
                }
                else if (hotel == "The Peninsula Tokyo") {
                    hotel_cost = 1700;
                }
                else if (hotel == "Mandarin Oriental, Tokyo") {
                    hotel_cost = 1600;
                }
                else {
                    hotel_cost = 0;
                }
            }
            else if (plann == "Premium") {
                if (hotel == "The Tokyo Station Hotel") {
                    hotel_cost = 2500;
                }
                else if (hotel == "Andaz Tokyo Toranomon Hills") {
                    hotel_cost = 2400;
                }
                else if (hotel == "Conrad Tokyo") {
                    hotel_cost = 2300;
                }
                else {
                    hotel_cost = 0;
                }
            }
        }//
        else if (destinationn == "Bali") {
            if (plann == "standard") {
                if (hotel == "AYANA Resort and Spa Bali") {
                    hotel_cost = 1400;
                }
                else if (hotel == "Four Seasons Resort Bali at Sayan") {
                    hotel_cost = 1300;
                }
                else if (hotel == "The Mulia Bali") {
                    hotel_cost = 1200;
                }
                else {
                    hotel_cost = 0;
                }
            }
            else if (plann == "Premium") {
                if (hotel == "Alila Villas Uluwatu") {
                    hotel_cost = 2200;
                }
                else if (hotel == "COMO Uma Ubud") {
                    hotel_cost = 2100;
                }
                else if (hotel == "Mandapa, a Ritz-Carlton Reserve") {
                    hotel_cost = 2000;
                }
                else {
                    hotel_cost = 0;
                }
            }
        }

        else if (destinationn == "New York") {
            if (plann == "standard") {
                if (hotel == "The Plaza Hotel") {
                    hotel_cost = 2000;
                }
                else if (hotel == "The New Yorker, A Wyndham Hotel") {
                    hotel_cost = 1800;
                }
                else if (hotel == "Hilton Times Square") {
                    hotel_cost = 1700;
                }
                else {
                    hotel_cost = 0;
                }
            }
            else if (plann == "Premium") {
                if (hotel == "The Plaza Hotel") {
                    hotel_cost = 3000;
                }
                else if (hotel == "Mandarin Oriental, New York") {
                    hotel_cost = 2800;
                }
                else if (hotel == "The St. Regis New York") {
                    hotel_cost = 2700;
                }
                else {
                    hotel_cost = 0;
                }
            }
            }//

            total_cost = hotel_cost + plan_cost;

    }
    void writeToFile() const
    {
        func_no = 11;
        ofstream outFile;
        outFile.open(path);
        if (outFile.is_open())
        {
            outFile << "Tourist ID: " << id << endl;
            outFile << "Name: " << name << endl;
            outFile << "Age: " << age << endl;
            outFile << "Phone: " << phone << endl;
            outFile << "Gender: " << gender << endl;
            outFile << "Nationality: " << nationality << endl;
            outFile << "Destination: " << destinationn << endl;
            outFile << "Plan: " << plann << endl;
            outFile << "Hotel: " << hotel << endl;
            outFile << endl;
            outFile.close(); // Close the file
        }
        else
        {
            cout << "Unable to open file for writing." << endl;
        }
    }

    //
    // void set_all(string var,string value) {
    // if (var == "name") {
    // set_name(value);
    // }
    // if (var == "age") {
    // set_age(stoi(value));
    // }
    // if (var == "phone") {
    //
    // set_phone(stoi(value));
    //
    // }
    // if (var == "gender") {
    // set_gender(value[0]);
    // }
    // if (var == "nationality") {
    // set_nationality(value);
    // }
    // if (var == "plan") {
    // set_plann(stoi(value));
    // }
    // if (var == "destination") {
    // set_destination(stoi(value));
    // }
    //}

    tourist(string n = "", int ag = 0, long long phon = 0, char gendr = ' ', string national = "", string plannn = " ", string destinationnn = " ")
        : id(++count), name(n), age(ag), phone(phon), gender(gendr), nationality(national), plann(plannn), destinationn(destinationnn)
    {
        set_messages();
        path = "D:/VISUAL STUDIO/oop project2/user_file" + to_string(id) + ".txt";
    }

    // Const pointer getters
    const int* getId() const { return &id; }
    const string* getName() const { return &name; }
    const int* getAge() const { return &age; }
    unsigned long long* getPhone() const { return const_cast<unsigned long long*>(&phone); }
    const char* getGender() const { return &gender; }
    const string* getNationality() const { return &nationality; }

    /// making a array of message to print

    // void checkp_d(int p, int d)
    //{
    //  if (p == 1) {
    //  plann = "standard"; // Assigning string directly
    //  }
    //  else {
    //  plann = "Premium"; // Assigning string directly
    //  }

    // switch (d)
    // {
    // case 1: // Use int values for switch cases
    // destinationn = "Paris";
    // break;
    // case 2:
    // destinationn = "Rome";
    // break;
    // case 3:
    // destinationn = "Tokyo";
    // break;
    // case 4:
    // destinationn = "Bali";
    // break;
    // case 5:
    // destinationn = "New York";
    // break;
    // default:
    // cout << "Invalid destination!" << endl;
    // break;
    // }
    //}

    ~tourist()
    {
        delete[] tourist_msg;
    }
};

int tourist::count = 0;
string* tourist::tourist_msg = new std::string[48];

class TourManager
{
private:
    string managerName;

public:
    TourManager() : managerName("Jahanzaib") {}

    void managerr()
    {
        cout << "Welcome!" << managerName << endl;
    }
};

int line_num_user_type = 0;
class UserTypeSelector
{
private:
    // TouristInterface interfacee;
    TourManager manager;
    string* typeselector;
    string t_id;
    stringstream ss;
    string filePath;
    char choice;

public:
    UserTypeSelector()
    {
        typeselector = new string[15];
        set_lines();
    }
    void set_lines()
    {

        typeselector[1] = "Welcome, tourist! \n Do you want to : \n 1. Make a new reservation \n 2. View previous reservations \n Enter your choice: ";
        typeselector[2] = "You chose to make a new reservation. \n ";
        typeselector[3] = "You chose to view Your previous reservations. \n";
        typeselector[4] = "Invalid choice. Please enter 'T' for tourist or 'M' for manager. \n";
        typeselector[5] = "Invalid choice. Please try again. \n";
    }

    string get_line()
    {
        string temp;
        temp = (typeselector[line_num_user_type]);
        return temp;
    }

    /*  void set_user() {
          func_no = 1;
          line_num_user_type = 1;
          res = get_line();



      }*/
    void set_reserv_choice()
    {
        int reservationChoice = stoi(req);
        func_no = 2;
        if (reservationChoice == 1)
        {
            line_num_user_type = 2;
            res = get_line();
            res = "\n Enter your name: ";

        }

        else if (reservationChoice == 2)
        {
            tourist_flag = 1;
            line_num_user_type = 3;
            res = get_line();
            res = "\n Enter your ID: ";
            t_id = stoi(req);
            filePath = "D:/VISUAL STUDIO/oop project2/user_file" + t_id + ".txt";

            /*ifstream file(filePath);

            if (!file.is_open()) {
                res = "Error opening the file! \n " ;
                return;
            }

            string line;
            while (getline(file, line)) {
                ss << line << std::endl;
            }

            file.close();
            res = ss.str();*/
        }

        else if (reservationChoice != 1 && reservationChoice != 2)
        {
            line_num_user_type = 5;
            res = get_line();
            res = "";
        }
    }

    void view_previous_reservations()
    {
        ifstream file(filePath);
        if (!file.is_open())
        {
            res = "Error opening the file!\n";
            return;
        }

        string line;
        while (getline(file, line))
        {
            ss << line << endl;
        }
        file.close();
        res = ss.str();
    }


    // void handleTourist() {
    // cout << "Welcome, tourist!" << endl;
    // char reservationChoice;
    // cout << "Do you want to:" << endl;
    // cout << "1. Make a new reservation" << endl;
    // cout << "2. View previous reservations" << endl;
    // cout << "Enter your choice: ";
    // cin >> reservationChoice;

    // switch (reservationChoice) {
    // case '1':
    // // Add code here to handle making a new reservation
    // cout << "You chose to make a new reservation." << endl;
    // interfacee.start();
    // break;
    // case '2':
    // // Add code here to handle viewing previous reservations
    // cout << "You chose to view Your previous reservations." << endl;
    // break;
    // default:
    // cout << "Invalid choice. Please try again." << endl;
    // handleTourist(); // Ask again if the choice is invalid
    // }
    //}

    // cout << "Are you a tourist (T) or a manager (M)? ";
    //// cin >> choice;

    // if (tolower(choice) == 't') {
    // handleTourist();
    // }
    // else if (tolower(choice) == 'm') {
    // manager.managerr();
    // }
    // else {
    // cout << "Invalid choice. Please enter 'T' for tourist or 'M' for manager." << endl;
    // selectUserType();
    // }
    //}
};

int user_level = 0;

/// <summary>
/// from here all code belongs to socket programming.
/// First class buffer is for sending and receiving data from client.
/// second class server belongs to creating server socket and putting on listening
/// and then it contains composition as it has buffer object which deals with sending and receiving data from and to client
/// in connection function
/// </summary>
class buffer
{
    static int clientno;
    char* bufferrecv;
    char* buffersend;
    int bytesrecv;
    int bytes_send;
    string request;
    string response;
    string filename;
    thread threadrecv;
    thread threadsend;
    string client_name;
    // composition
    UserTypeSelector object1;
    // TouristInterface object2;
    tourist object3;

public:
    void set_name(string n)
    {
        client_name = n;
    }

    string show_recv(char* recv, int size)
    {

        string temp_msg(recv, size);
        request = temp_msg;
        if (request == "exit")
        {
            ofstream file(filename);
            file.open(filename);
            cout << "CLIENT IS REQUESTING TO BREAK CONNECTION!" << endl;
            file << request;
            file.close();
            return "Break";
        }
        else
        {
            ofstream file(filename);
            file.open(filename);
            cout << "The message from " << client_name << ": " << request << endl;
            file << request;
            file.close();
        }
        return request;
    }

    void call_all_func(int z)
    {
        ///*if (z == 1) {
        //    object1.set_user();
        //}*/
        //if (z == 2)
        //{
        //    object1.set_reserv_choice();
        //}
        if (z == 1)
        {
            object3.set_name();
        }
        else if (z == 2)
        {
            object3.set_age();
        }
        else if (z == 3)
        {
            object3.set_phone();
        }
        else if (z == 4)
        {
            object3.set_gender();
        }
        else if (z == 5)
        {
            object3.set_nationality();
        }
        else if (z == 6)
        {
            object3.set_d();
        }
        else if (z == 7)
        {
            object3.set_plann();
        }
        else if (z == 8)
        {
            object3.set_hotels();
            object3.set_plan_cost();
            object3.set_hotel_cost();
        }
        else if (z == 9)
        {
            object3.set_ticket();
            object3.writeToFile();
        }
        // default
        else
        {
            connection_flag = 1;
        }
    }

    void call_func_M(int y)
    {
        if (y == 1)
        {
            res = "Enter Name: \n";
        }
        else if (y == 2)
        {
            res = "Enter Password \n";
        }

        // default
        else
        {
            connection_flag = 1;
        }
    }

    void set_response(string val)
    {
        res = val;
    }
    void setbufferrecv()
    {
        int i = 1;
        while (connection_flag == 0)
        {
            i++;
            lock_guard<mutex> locking_for_r(receiver);
            bytesrecv = recv(connected_socket, bufferrecv, 2048, 0);
            req = show_recv(bufferrecv, bytesrecv);
            if (req == "exit" || bytesrecv == SOCKET_ERROR)
            {
                connection_flag = 1;
                closesocket(connected_socket);
                WSACleanup();
                connection_break.notify_one();
                break;
            }
            else
            {
                if (user_level == 2)
                {
                    object1.set_reserv_choice();

                    if (tourist_flag == 1)
                    {
                        object1.view_previous_reservations();
                    }
                    else
                    {
                        call_all_func(i);
                    }
                }
                else if (user_level == 1)
                {
                    call_func_M(i);
                }
                while (res == "")
                {

                    string error = "\t\t Error Invalid Input! \n try again \n Enter: ";
                    cerr << "Invalid input from Client " << endl;
                    send(connected_socket, error.c_str(), (error.length() + 1), 0);
                    bytesrecv = recv(connected_socket, bufferrecv, 2048, 0);
                    req = show_recv(bufferrecv, bytesrecv);
                    if (user_level == 2)
                    {
                        if (tourist_flag == 1) 
                        {
                            object1.view_previous_reservations();
                        }
                        else
                        {
                            call_all_func(i);
                        }
                    }
                }

                cv.notify_one();
            }
            // message received

            // setbuffersend();
            //  remember
            // bytesrecv = SOCKET_ERROR;
        }
    }

    void setbuffersend()
    {
        while (connection_flag == 0)
        {
            unique_lock<mutex> locking_to_s(sender);
            cv.wait(locking_to_s, [this]()
                { return (bytesrecv != SOCKET_ERROR); });
            int size;
            cout << "Generated response for client: " << res << endl;
            // res = "Your choice is : "+ request+"\n";
            size = (res.length() + 1);
            for (int i = 0; i < size; i++)
            {
                buffersend[i] = res[i];
            }
            buffersend[size] = '\0';
            bytes_send = send(connected_socket, buffersend, size, 0);
            if (bytes_send == SOCKET_ERROR)
            {
                cout << "FAILED TO SEND \n message: " << res << endl;
                cout << "ERROR: " << WSAGetLastError() << endl;
                break;
            }
            bytesrecv = SOCKET_ERROR;
        }
    }

    buffer()
    {
        clientno++;
        filename = "chat" + to_string(clientno) + ".txt";
        ifstream file(filename);
        bufferrecv = new char[2048];
        buffersend = new char[2048];
        bytesrecv = SOCKET_ERROR;
        bytes_send = 0;
        client_name = "No_client_name_yet";
    }
    void invoke_threads()
    {
        threadrecv = std::thread(&buffer::setbufferrecv, this);
        threadsend = std::thread(&buffer::setbuffersend, this);
        threadrecv.join();
        threadsend.join();
    }

    void set_cli_name()
    {
        while (client_name.size() >= 10)
        {
            char* request = new char[256];
            string response = "Enter userame: ";
            send(connected_socket, response.c_str(), (response.length() + 1), 0);
            int bytesr = recv(connected_socket, request, 256, 0);
            string message(request, bytesr);
            set_name(message);
        }
    }

    void display_intro()
    {
        char* responseMessage = new char[256];
        char title[] = " \t\t\t\t Welcome \n \t\t\t OOPs Travel and Co. !\n\n \n\n Enter T for tourist interface \n M for Manager interface \n";
        char* ptr = &title[0];
        for (int i = 0; i < sizeof(title); i++)
        {
            responseMessage[i] = *(ptr + i);
            send(connected_socket, &(responseMessage[i]), 1, 0);
            Sleep(40);
        }
        int bytesr = recv(connected_socket, responseMessage, 256, 0);
        string message(responseMessage, bytesr);
        if (message[0] == 'T')
        {
            user_level = 2;
            set_cli_name();
            res = "Welcome, tourist! \n Do you want to : \n 1. Make a new reservation \n 2. View previous reservations \n Enter your choice: ";
            send(connected_socket, res.c_str(), (res.length() + 1), 0);
        }
        else if (message[0] == 'M')
        {
            user_level = 1;
            res = "Welcome to MANAGER INTERFACE \n";
            send(connected_socket, res.c_str(), (res.length() + 1), 0);
        }
        // char menu[] = "Welcome, tourist! \n Do you want to: \n 1. Make a new reservation 2. View previous reservations 3. Edit previous reservations \n Enter your choice: ";
        // ptr = &menu[0];
        // for (int i = 0; i < strlen(menu); i++)
        //{
        //     responseMessage[i] = *(ptr + i);
        //     send(connected_socket, &(responseMessage[i]), 1, 0);
        //     //cout << *(ptr + i);
        //     Sleep(40);
        // }
        delete[] responseMessage;
    }

    void display_all()
    {
        cout << "The data received of client is here! " << endl;
    }

    void update_socket(SOCKET S)
    {
        S = connected_socket;
    }
    void check_exec()
    {
        if (threadrecv.joinable())
        {
            threadrecv.join();
        }
        if (threadsend.joinable())
        {
            threadsend.join();
        }
    }
    ~buffer()
    {

        delete[] bufferrecv;
        delete[] buffersend;
    }
};
// buffer member and methods
int buffer::clientno = 0;

// temp

// class request_response {
// public:
//  int flag = 0;
//  buffer connection;
//  UserTypeSelector id;
//  SOCKET cli;
//  request_response() {
//
//  connection.update_socket(connected_socket);
//  connection.display_intro();
//
//  }
//  request_response(SOCKET cli1) : cli(cli1) {
//  connection.update_socket(cli);
//  connection.display_intro();
//
//  }
//
//
//
//
// };

class SERVER
{

    static int server_no;
    SOCKET server_socket;

    // wstring socket_ip;
    int socket_port;
    int backlogs;
    SOCKET* cli_sock;
    sockaddr_in* cli_info;
    thread t_for_rececive;
    thread thread_for_send;

public:
// below all members and methods belongs to class SERVER
    SERVER()
    {
        // tmut.try_lock_for(chrono::seconds(15));
        lock_guard<mutex> locking(mut);
        cout << "SERVER SOCKET " << server_no << " is in production" << endl;

        // for port
        [&]()
            {
                initialize_winsock();
                server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
                socket_port = 4443;
            }();

            server_no++;
            backlogs = 3;
            cli_sock = new SOCKET[backlogs];
            cli_info = new sockaddr_in[backlogs];

            // sleep for 10 sec before calling functions
            // Sleep(15000);
            check_flags();
    }

    int initialize_winsock()
    {
        int flag = 0;
        // declaring here for so it have function scope
        WORD version = MAKEWORD(2, 2);
        WSADATA implement;
        flag = WSAStartup(version, &implement);
        if (flag != 0)
        {
            cout << "Error WINDOWS SOCKET initialization failed! " << endl;
            cout << "Error: " << WSAGetLastError() << endl;
            WSACleanup();
            return flag;
        }
        else
        {
            cout << "WINDOWS SOCKET INITIALIZED Successfully! " << endl;
            return flag;
        }
    }

    // ADDING SOCKET info to structure for binding
    // wstring get_ip() {
    //  return socket_ip;
    // }
    int get_port()
    {
        return socket_port;
    }

    int set_ip_port()
    {

        // wcout << "Enter ip for SERVER SOCKET: ";
        // wcin >> socket_ip;
        // socket_ip(wsocket_ip.begin(), wsocket_ip.end());
        cout << "Enter port for listening: ";
        cin >> socket_port;
        return 0;
    }

    int assign_struct()
    {
        int flag = 1;
        memset(&sockinfo, 0, sizeof(sockinfo));
        sockinfo.sin_family = AF_INET;
        sockinfo.sin_addr.s_addr = htonl(INADDR_ANY);
        ////sockinfo.sin_addr.s_addr =  inet_addr(socket_ip);
        // std::wstring wsocket_ip(socket_ip, socket_ip + strlen(socket_ip) + 1);
        // flag = InetPton(AF_INET,wsocket_ip.c_str(), &sockinfo.sin_addr);
        /*wchar_t wsocket_ip[17];
        wstring socket_ip = L"192.168";*/
        // const wchar_t ipWide = socket_ip.c_str();
        // flag = InetPton(AF_INET, _T("192.168.243.105"), &sockinfo.sin_addr);
        // cout<<"Binary of ip is: "<<sockinfo.sin_addr.s_addr<<endl;
        // Call InetPton with PCWSTR argument

        if (flag == 0)
        {
            cout << "Failed to Assigned values to structure ";
            closesocket(server_socket);
            WSACleanup();
            return 1;
        }
        else
        {
            cout << "Structure is assigned with values for binding!" << endl;
        }
        sockinfo.sin_port = htons(socket_port);
        return 0;
    }

    // binding socket to given ip and port
    int bind_socket()
    {

        cout << "Binding socket " << "Port: " << socket_port << endl;

        if (bind(server_socket, (sockaddr*)&sockinfo, sizeof(sockinfo)) == SOCKET_ERROR)
        {
            cout << "SOCKET Binding Failed! " << endl;
            cout << "Error: " << WSAGetLastError() << endl;
            closesocket(server_socket);
            WSACleanup();
            return 1;
        }
        else
        {
            // wcout << "Socket bind to IP: " << socket_ip << endl;
            cout << "PORT: " << socket_port << endl;
            return 0;
        }
    }
    // putting socket on listening
    int server_listen()
    {
        int flag = 1;
        // currently setting backlogs to 3
        flag = listen(server_socket, backlogs);
        if (flag != 0)
        {
            cout << "ERROR: " << WSAGetLastError() << endl;
            cout << "Failed to put server on listening! " << endl;
            closesocket(server_socket);
            WSACleanup();
            return 1;
        }
        else
        {
            cout << "SERVER is listening on port: " << socket_port << endl;
            cout << "Waiting for incoming connections <" << endl;
            return 0;
        }
    }

    // accepting for connections

    int connection()
    {

        int addrlength = sizeof(sockinfo);
        buffer api;

        connected_socket = accept(server_socket, reinterpret_cast<sockaddr*>(&sockinfo), &addrlength);

        if (connected_socket != SOCKET_ERROR)
        {
            connection_flag = 0;
            cout << "CLIENT IS CONNECTED TO SERVER! " << endl;

            api.update_socket(connected_socket);
            api.display_intro();
            api.invoke_threads();
            api.check_exec();
            // api.setbufferrecv();
            // unique_lock<mutex> locking(mut);
            // connection_break.wait(locking, (connection_flag == 1) ? true : false);
            WSACleanup();
            closesocket(connected_socket);
        }
        else
        {
            cerr << "Connection Failed! " << endl;
            WSACleanup();
            closesocket(server_socket);
            return 1;
        }

        WSACleanup();
        closesocket(server_socket);
        return 0;
    }

    // flags to check
    int check_flags()
    {

        int flag = 0;
        flag = set_ip_port();
        if (flag != 0)
            return 1;

        flag = assign_struct();
        if (flag != 0)
            return 1;

        flag = bind_socket();
        if (flag != 0)
            return 1;

        flag = server_listen();
        if (flag != 0)
            return 1;

        flag = connection();
        if (flag != 0)
            return 1;

        return flag;
    }
    ~SERVER()
    {
        delete[] cli_sock;
        delete[] cli_info;
        closesocket(server_socket);
        WSACleanup();
    }
};


int SERVER::server_no = 1;

// ends here
//

int main(void)
{

    SERVER check;
    cout << "Program terminating ..." << endl;

    return 9;
}

