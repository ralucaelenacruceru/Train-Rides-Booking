#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <regex>

#include <cmath>


class User {

public:


    static std::string RSA(std::string x){
        std::string y;
        for(int i=0;i<x.size();i++){
            auto message = double(x[i]);
            double c = pow(message, 7);
            c = fmod(c, 13*11);
            if(c == 44)
                c = c + 1;
            y.push_back(char(c));
        }
        return y;
    }


    static int ReadFile(std::string const &enteredName, std::string &filename) {


        std::vector<std::vector<std::string>> content;
        std::vector<std::string> row;
        std::string line, word;
        std::fstream file(filename, std::ios::in);
        if (file.is_open()) {
            while (getline(file, line)) {
                row.clear();
                std::stringstream str(line);
                while (getline(str, word, ','))
                    row.push_back(word);
                content.push_back(row);
            }
        } else
            std::cout << "Could not open the file\n";
        int contor = 0;
        for (int i = 0; i < content.size(); i++) {
            for (int j = 0; j < content[i].size(); j++) {
                if (content[i][j] == enteredName)
                    contor++;

            }

        }
        if (contor == 0)
            return 0;
        else
            return 1;
    }

    static int ReadFilePassword(std::string const &enteredName,std::string const &passwordName, std::string &filename) {


        std::vector<std::vector<std::string>> content;
        std::vector<std::string> row;
        std::string line, word;
        std::fstream file(filename, std::ios::in);
        if (file.is_open()) {
            while (getline(file, line)) {
                row.clear();
                std::stringstream str(line);
                while (getline(str, word, ','))
                    row.push_back(word);
                content.push_back(row);
            }
        } else
            std::cout << "Could not open the file\n";
        int save = 0;
        int contor = 0;
        for (int i = 0; i < content.size(); i++) {
            for (int j = 0; j < content[i].size(); j++) {
                if (content[i][j] == enteredName)
                    save = i;
            }
        }

        for (int j = 0; j < content[save].size(); j++) {
            if (content[save][j] == passwordName)
                contor++;
        }


        if (contor == 0)
            return 0;
        else
            return 1;
    }


    static int CheckPassword(std::string str) {
        int i;
        int Alphabets = 0, num = 0, special = 0, space = 0;

        i = 0;
        do {
            //check Alphabets
            if ((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z')) {
                Alphabets++;
            } else if (str[i] >= '0' && str[i] <= '9') {
                num++;
            } else if (str[i] == ' ') {
                space++;
            } else {
                special++;
            }
            i++;
        } while (str[i] != '\0');

        if (Alphabets >= 5 && num >= 2 && special >= 1 && space == 0)
            return 0;
        else
            return 1;
    }


    static int CheckEmailFormat(std::string const &s) {
        std::string format1 = "@gmail.com";
        std::string format2 = "@gmail.ro";
        std::string format3 = "@yahoo.com";
        std::string format4 = "@yahoo.ro";
        if (s.find('@') != std::string::npos) {

            std::size_t found = s.find_last_of("@");

            if (s.substr(found).compare(format1) == 0 || s.substr(found).compare(format2) == 0 ||
                s.substr(found).compare(format3) == 0 || s.substr(found).compare(format4) == 0) {

                return 0;

            } else
                return 1;
        } else
            return 1;


    }


    bool static is_Registered(std::string filename) {

        std::fstream fout;


        fout.open("conturi_Utilizatori.csv", std::ios::out | std::ios::app);

        std::cout << "You are allowed to register only as a USER" << std::endl;


        std::cout << "******** Enter your username *********" << std::endl;
        std::string username;

        while (true) {

            std::cin >> username;
            if (username.length() > 4 && username.length() < 20) {
                if (ReadFile(username, filename) == 0) {
                    break;
                } else if (ReadFile(username, filename) == 1) {
                    std::cout << "\n*Please enter another username this one is already taken :)*\n";
                }

            } else {
                std::cout << "\n*Please enter another username this one is too short or too long:)*\n";
            }
        }


        std::cout << "******** Enter your mail *********" << std::endl;
        std::string mail;


        while (true) {

            std::cin >> mail;
            if (ReadFile(mail, filename) == 0 && CheckEmailFormat(mail) == 0) {
                break;
            } else if (ReadFile(mail, filename) == 1) {
                std::cout << "\n*Please enter another e-mail this one was already used :(*\n";
            } else if (CheckEmailFormat(mail) == 1) {
                std::cout << "\n*Please enter a valid e-mail*\n";
            }

        }


        std::cout << "******** Enter your password *********" << std::endl;
        std::cout
                << "!!! MAKE SURE THE PASSWORD HAS AT LEAST: 5 letters, 2 numbers and a special character and no spaces!!!"
                << std::endl;

        std::string password;

        while (true) {

            std::cin >> password;
            if (CheckPassword(password) == 0) {
                break;
            } else {
                std::cout << "\n*Please enter a stronger password*\n";
                std::cout << "!!! MAKE SURE THE PASSWORD HAS AT LEAST: 5 letters, 2 numbers and a special character !!!"
                          << std::endl;
            }
        }


        std::cout << "******** Repeat your password *********" << std::endl;

        std::string againPassword;
        int flag = 0;

        while (true) {

            std::cin >> againPassword;
            if (password.compare(againPassword) == 0) {
                break;
            } else if (password.compare(againPassword) != 0) {
                if(flag < 3) {
                    std::cout << "\n*The password is incorrect, please repeat*\n";
                    flag++;
                } else return false;
            }
        }
        fout <<"\n";
        fout << username << ",";
        fout << mail << ",";
        std::string encryptedPass = RSA(password);
        fout << encryptedPass;

        username = " ";
        mail = " ";
        password =" ";

        return true;
    }

    bool static is_Login(std::string filename){

        std::cout << "******** Enter your username *********" << std::endl;
        std::string username;


        while (true) {
            std::cin >> username;
            if (ReadFile(username, filename) == 1) {
                    break;
                } else if (ReadFile(username, filename) == 0) {
                    std::cout << "\n*Please try again, username not in the database*\n";
                }
        }

        std::cout << "******** Enter your password *********" << std::endl;
        std::string password;
        int flag = 0;

        while (true) {
            std::cin >> password;
            std::string encryptedPassword = RSA(password);
            if (ReadFilePassword(username, encryptedPassword, filename) == 1) {
                break;
            } else {
                if(flag < 3) {
                    std::cout << "\n*Incorrect password! Try again!*\n";
                    flag++;
                }else return false;
            }
        }

        return true;
    }




    std::string isReserved(std::string const &trip, std::string filename){
        std::cout << "******** You have entered the booking page! To book the trip enter your Username again! *********" << std::endl;
        std::cout << "******** Enter your username again*********" << std::endl;
        std::string username;
        while (true) {
            std::cin >> username;
            if (ReadFile(username, filename) == 1) {
                break;
            } else if (ReadFile(username, filename) == 0) {
                std::cout << "\n*Please try again, username not in the database*\n";
            }
        }

        std::fstream fout;
        fout.open("booked_trips.csv", std::ios::out | std::ios::app);

        fout <<"\n";
        fout << username << ",";
        fout << trip;
        return username;
    }



};







class Schedule{
public:
    void static printSchedule(){
            std::vector<std::vector<std::string>> content;
            std::vector<std::string> row;
            std::string line, word;
            std::fstream file("train_schedule.csv", std::ios::in);
            if (file.is_open()) {
                while (getline(file, line)) {
                    row.clear();
                    std::stringstream str(line);
                    while (getline(str, word, ','))
                        row.push_back(word);
                    content.push_back(row);
                }
            } else {
                std::cout << "Could not open the file\n";

            }


            std::cout << "No    Day    Hour   City to Destination-City   Arrival-Hour" << std::endl;
            for (int i = 0; i < content.size(); i++) {
                for (int j = 0; j < content[i].size(); j++) {
                    std::cout << content[i][j] << "   ";
                }
                std::cout << std::endl;

            }

        }

        void static printOneLine(std::string const &str){

            std::vector<std::vector<std::string>> content;
            std::vector<std::string> row;
            std::string line, word;
            std::fstream file("train_schedule.csv", std::ios::in);
            if (file.is_open()) {
                while (getline(file, line)) {
                    row.clear();
                    std::stringstream str1(line);
                    while (getline(str1, word, ','))
                        row.push_back(word);
                    content.push_back(row);
                }
            } else {
                std::cout << "Could not open the file\n";

            }


            std::cout << "No    Day    Hour   City to Destination-City   Arrival-Hour" << std::endl;
            for (int i = 0; i < content.size(); i++) {
                for (int j = 0; j < content[i].size(); j++) {
                    if(content[i][0] == str)
                         std::cout << content[i][j] << "   ";
                }
            }

    }


};



class Operator: public User{

public:

    time_t Time = time(nullptr);
    tm *local_time = localtime(&Time);

    int currentYear = 1900 + local_time->tm_year;
    int currentMonth =  1 + local_time->tm_mon;
    int currentDay = local_time->tm_mday;
    int currentHour = local_time->tm_hour;







    bool checkDateFormat(int day, int month, int year) const{

        const int MAX_VALID_YR = 2024;
        const int MIN_VALID_YR = 2022;


        if(year == currentYear && month < currentMonth) {
            return false;
        }
        if(year == currentYear && month == currentMonth && day < currentDay) {
            return false;
        }

        if (year > MAX_VALID_YR || year <MIN_VALID_YR)
                return false;
        if (month < 1 || month > 12)
                return false;
        if (day < 1 || day > 31)
                return false;



            return true;
    }



    bool isValidTime(std::string &str, int flag1) const
    {


        const std::regex pattern("([0-1]?[0-9]|2[0-3]):[0-5][0-9]");

        if (str.empty()){
            return false;
        }

        if(regex_match(str, pattern)){
            if(flag1 == 1) {
                std::size_t found = str.find_last_of(":");
                if (std::stoi(str.substr(0, found)) > currentHour + 2) {
                    return true;
                } else return false;
            }
                return true;
        }
        else
        {
            return false;
        }


    }



    bool static isValidName(std::string str) {
        int flag, i = 0 ;
        do {
            if ((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z')) {
                flag = 0;
            } else if (str[i] >= '0' && str[i] <= '9') {
                flag++;
            } else if (str[i] == ' ') {
                flag = 0;
            } else {
                flag++;
            }
            i++;
        } while (str[i] != '\0');

        if (flag == 0)
            return true;
        else if(flag > 0)
            return false;
        return false;
    }




    int checkRideExistence(int day, int month, int year, std::string hour1, std::string city1, std::string city2, std::string hour2){
        std::vector<std::vector<std::string>> content;
        std::vector<std::string> row;
        std::string line, word;
        std::fstream file("train_schedule.csv", std::ios::in);
        std::string formatDate = std::to_string(day) + "." + std::to_string(month) + "." + std::to_string(year);
        if (file.is_open()) {
            while (getline(file, line)) {
                row.clear();
                std::stringstream str(line);
                while (getline(str, word, ','))
                    row.push_back(word);
                content.push_back(row);
            }
        } else {
            std::cout << "Could not open the file\n";

        }

       int contor = 0;

        for (int i = 0; i < content.size(); i++) {
            for (int j = 0; j < 5; j++) {
                if( content[i][0] == formatDate && content[i][1] == hour1 && content[i][2] == city1 && content[i][3] == city2 && content[i][4] == hour2)
                    contor++;
            }
        }

        if (contor == 0)
            return 1;
        else
            return 0;


    }


     bool addRide() {

         int NumberOfRide = 12;
         int day, month, year;
         int here = 0;
         std::cout << "******** Enter the date *********" << std::endl;
         while (true) {

             std::cout << "******** Enter the day *********" << std::endl;
             std::cin >> day;
             std::cout << "******** Enter the month *********" << std::endl;
             std::cin >> month;
             std::cout << "******** Enter the year *********" << std::endl;
             std::cin >> year;

             if (checkDateFormat(day, month, year)) {
                 break;
             } else {
                 std::cout << "\n*Please enter another date, this one is not correct !!Check the format!!\n";
             }
         }

         if (day == currentDay && month == currentMonth && year == currentYear)
             here = 1;


         std::string hour1;
         std::cout << "******** Enter the hour of departure [00:00]*********" << std::endl;
         std::cout << "******** You can only enter an hour that is 3 hours prior to the departure*********"
                   << std::endl;
         while (true) {
             std::cin >> hour1;
             if (isValidTime(hour1, here))
                 break;
             else
                 std::cout << "\n*Please enter another hour, this one is not correct !!Check the format!! *\n";

         }

         std::string departureCity;
         std::cout << "******** Enter the Departure City*********" << std::endl;
         while (true) {
             std::cin >> departureCity;
             if (isValidName(departureCity))
                 break;
             else
                 std::cout
                         << "\n*Please enter another name, this one is not correct !!Check if the name contains spaces/special characters or numbers!! *\n";

         }


         std::string destinationCity;
         std::cout << "******** Enter the Destinastion City*********" << std::endl;
         while (true) {
             std::cin >> destinationCity;
             if (isValidName(destinationCity))
                 break;
             else
                 std::cout
                         << "\n*Please enter another name, this one is not correct !!Check the name it contains spaces/special characters or numbers!! *\n";

         }


         std::string hour2;

         std::cout << "******** Enter the hour of arrival [00:00]*********" << std::endl;
         here = 0;

         while (true) {
             std::cin >> hour2;
             if (isValidTime(hour2, here)) {
                 break;
             }
             else
                 std::cout << "\n*Please enter another hour, this one is not correct !!Check the format!! *\n";

         }


         std::fstream fout;
         fout.open("train_schedule.csv", std::ios::out | std::ios::app);


        if (checkRideExistence(day, month, year, hour1, departureCity, destinationCity, hour2) == 1) {
             std::cout << "******** Successfully entered a new trip! *********" << std::endl;
             NumberOfRide++;
             fout << "\n";
             fout << NumberOfRide <<",";
             fout << std::to_string(day) + "." + std::to_string(month) + "." + std::to_string(year) + ",";
             fout << hour1 << ",";
             fout << departureCity << ",";
             fout << destinationCity << ",";
             fout << hour2;
             return true;

         } else {
             std::cout << "******** This trip already exists! I am sorry but you need to try again! *********" << std::endl;
             return false;
         }



     }

     bool static isRideExists(std::string const &enteredName){
         std::vector<std::vector<std::string>> content;
         std::vector<std::string> row;
         std::string line, word;
         std::fstream file("train_schedule.csv", std::ios::in);
         if (file.is_open()) {
             while (getline(file, line)) {
                 row.clear();
                 std::stringstream str(line);
                 while (getline(str, word, ','))
                     row.push_back(word);
                 content.push_back(row);
             }
         } else
             std::cout << "Could not open the file\n";
         int contor = 0;
         for (int i = 0; i < content.size(); i++) {
             for (int j = 0; j < content[i].size(); j++) {
                 if (content[i][j] == enteredName)
                     contor++;

             }

         }
         if (contor == 0)
             return false;
         else
             return true;
     }






     std::string static FindDeleteRide(){
         std::cout << "******** What is the number of the trip you want to delete? *********" << std::endl;
         std::string number;

         while (true) {
             std::cin >> number;
             if (isRideExists(number))
                 break;
             else
                 std::cout << "\n*Please enter another number, this one does not exist *\n";

         }
         return number;
     }


     void static DeleteRide(std::string const &number){



             std::fstream fin, fout;


             fin.open("train_schedule.csv", std::ios::in);


             fout.open("train_schedule_updated.csv", std::ios::out);

             int i;
             std::string line, word;
             std::vector<std::string> row;


             while (!fin.eof()) {

                 row.clear();

                 getline(fin, line);
                 std::stringstream s(line);

                 while (getline(s, word, ',')) {
                     row.push_back(word);
                 }


                 int row_size = row.size();

                 for (i = 0; i < row_size - 1; i++) {
                         if (row[0] != number)
                            fout << row[i] << ",";
                     }
                 if (row[0] != number)
                     fout << row[row_size - 1] << "\n";

                 if (fin.eof())
                     break;
             }


             fin.close();
             fout.close();


             remove("train_schedule.csv");
             rename("train_schedule_updated.csv", "train_schedule.csv");
         }

};




int main() {
    __attribute__((unused)) User aUser;
    __attribute__((unused)) Schedule aSchedule;
Operator anOperator;
std::cout << "********** Login or Register ************" << std::endl;
std::cout << "==========================================" << std::endl;
std::cout << "Please enter <login> or <register>" << std::endl;




std::string answear;


    while(true){

        std::cin >> answear;
        //  LOGIN
        if(answear == "login"){
            answear = " ";
            std::cout<<"Do you want to login as an operator or as a user?" << std::endl;
            std::cout << "Please enter <operator> or <user>" << std::endl;
            while(true) {
                std::cin >> answear;
                //OPERATOR
                if (answear == "operator") {
                    answear = " ";
                    bool status =  Operator::is_Login("conturi_Operatori.csv");
                    if (!status)
                        std::cout << "******** LOGIN FAILED:( *********";
                    else {
                        std::cout << "******** LOGIN COMPLETED *********" << std::endl;
                        std::cout << "******** To add a new trip enter <add>, to delete enter <delete> *********"
                                  << std::endl;
                        start:
                            std::cin >> answear;
                            start2:
                            if (answear == "add") {
                                anOperator.addRide();
                                answear = " ";
                                std::cout << "\n*If you want to add one more trip write <add>, if not write <exit>*\n";
                                std::cout << "\n*!!YOU CAN ONLY TRY TO ADD TWO TRIPS AT A TIME!!*\n";
                                std::cin >> answear;
                                if (answear == "add") {
                                        anOperator.addRide();
                                            std::cout << "\n*Your session has ended!*\n";
                                            break;
                                } else if (answear == "exit") {
                                        break;
                                } else {
                                        std::cout << "\n*Please write <add> or <exit> correctly*\n";
                                        goto start2;
                                }


                            } else if (answear == "delete") {
                                std::cout << "******** Here is the current schedule: *********" << std::endl;
                                Schedule::printSchedule();
                                std::string line = Operator::FindDeleteRide();
                                std::cout << "******** Are you sure you want to delete this trip? *********" << std::endl;
                                std::cout << std::endl;
                                Schedule::printOneLine(line);
                                std::cout << std::endl;
                                std::cout << "******** Write <yes> or <no> *********" << std::endl;
                                answear = " ";
                                while(true) {
                                    std::cin >> answear;
                                    if (answear == "yes") {
                                       Operator::DeleteRide(line);
                                        std::cout << "******** You have successfully deleted the trip! *********" << std::endl;
                                        std::cout << "******** This is the updated schedule: *********" << std::endl;
                                        Schedule::printSchedule();
                                        std::cout << "\n*Your session has ended!To further modify login again!*\n";
                                        break;
                                    } else if (answear == "no") {
                                        std::cout << "\n*Your session has ended!To further modify login again!*\n";
                                        break;
                                    } else
                                        std::cout << "\n*Please write <yes> or <no> correctly*\n";
                                }
                                break;
                            } else{
                                std::cout << "\n*Please write <add> or <delete> correctly*\n";
                        goto start;
                        }
                    }
                    break;



                    // USER
                } else if (answear == "user") {
                    answear = " ";
                    bool status = User::is_Login("conturi_Utilizatori.csv");
                    if (!status) {
                        std::cout << "******** LOGIN FAILED:( *********";
                    } else {
                        std::cout << "******** LOGIN COMPLETED *********" << std::endl;
                        std::cout << "******** To see the complete schedule enter <yes>, else enter <no> and you will exit the app *********" << std::endl;
                        while (true) {
                            answear = " ";
                            std::cin >> answear;
                            if (answear == "yes") {
                                Schedule::printSchedule();
                                std::cout << "******** Do you want to book a ticket? *********" << std::endl;
                                std::cout << "******** To enter the booking page enter <yes>, else enter <no> and you will exit the app *********" << std::endl;
                                answear = " ";
                                while (true) {
                                    std::cin >> answear;
                                    if (answear == "yes") {
                                        answear = " ";
                                        std::cout << "******** Enter the NUMBER of the trip you want to book: *********" << std::endl;
                                        while (true) {
                                            std::cin >> answear;
                                            if (Operator::isRideExists(answear)) {
                                                std::string username = aUser.isReserved(answear, "conturi_Utilizatori.csv");
                                                std::cout << "******** Trip successfully booked! *********" << std::endl;
                                                std::cout << "******** Trip booked: *********" << std::endl;
                                                Schedule::printOneLine(answear);
                                                break;
                                            }else
                                                std::cout << "\n*Please enter another number, this one does not exist *\n";
                                        }
                                        break;
                                    } else if (answear == "no") {
                                        std::cout << "\n*Your session has ended!To further modify login again!*\n";
                                        break;
                                    } else
                                        std::cout << "\n*Please write <yes> or <no> correctly*\n";
                                }
                                break;
                            } else if (answear == "no") {
                                std::cout << "\n*Your session has ended!To further modify login again!*\n";
                                break;
                            } else
                                std::cout << "\n*Please write <yes> or <no> correctly*\n";
                        }
                        break;
                    }

                } else {
                    std::cout << "\n*Please write <operator> or <user> correctly*\n";
                }
            }
            break;

            // REGISTER
        }else if(answear == "register"){
            bool status = User::is_Registered("conturi_Utilizatori.csv");
            if(!status)
                std::cout << "******** REGISTRATION FAILED:( *********";

            else {
                std::cout << "******** REGISTRATION COMPLETED *********" << std::endl;
                std::cout << "******** !!! TO ENTER YOUR ACCOUNT YOU HAVE TO ENTER AGAIN AND LOGIN !!!*********"
                          << std::endl;
            }
            break;
        }else{
            std::cout << "\n*Please write (login) or (register) correctly*\n" ;
        }
    }








    return 0;
}
