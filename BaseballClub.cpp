                                                                                                                                                                               #include<iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

struct players
{
    int registationNumber;
    string firstName;
    string lastName;
    string dateOfBirth;
    int runsScored;
    int numberOfMatches;
};

//Team arrays
int teamA[15];
int teamB[15];
int teamC[15];
int teamD[15];
int teamE[15];
//arrays
int Players[75];
int teamCount[75];
int store[75];
players p[75];

//Global variables
string reply,response;
string playerDetails;
int storePlayerCount=1; // this variable update number of players always
int countPlayers=0;
int const PlayerForEachTeam=15;
int const NoOfPlayers=75;
char team;
int choice;
int playerRegisterNo;
int CountA = 0, CountB = 0, CountC = 0, CountD = 0, CountE = 0;

//below function for write all the user details in file 
void myfile(){
        ofstream MyFile("F:\\Player_details.txt",ios::app);//we use ios::app to avoid overwrite
        {
            MyFile<<"player registation number: "<<p[countPlayers].registationNumber<<"\n\n";
            MyFile<<"player first name: "<<p[countPlayers].firstName<<"\n";
            MyFile<<"player last name: "<<p[countPlayers].lastName<<"\n";
            MyFile<<"player ID: "<<p[countPlayers].registationNumber<<"\n";
            MyFile<<"date of birth: "<<p[countPlayers].dateOfBirth<<"\n";
            MyFile<<"runs scored: "<<p[countPlayers].runsScored<<"\n";
            MyFile<<"number of match: "<<p[countPlayers].numberOfMatches<<"\n";
            MyFile<<"\n";
            MyFile.close();
        }
}

//below function for add players to the system
void addNewPlayers(){
    int registationNumber;
    int playersCount=NoOfPlayers-storePlayerCount; // this code calculate remaining players count that we can add

    do
    {   if (countPlayers < playersCount) {
            int registrationNumber;
            cout << "Player registration number: ";
            cin >> registrationNumber;

            bool alreadyExists = false;
            for (int i = 0; i < NoOfPlayers; i++) {
                if (registrationNumber == store[i] || p[i].registationNumber==registrationNumber) {
                    alreadyExists = true;
                    cout<<"\n";
                    cout << "This registration number already exists !\n\n";
                    break;
                }
            }

            if (!alreadyExists) {
                p[countPlayers].registationNumber = registrationNumber;

                cout << "Player first name: ";
                cin >> p[countPlayers].firstName;

                cout << "Player last name: ";
                cin >> p[countPlayers].lastName;

                cout << "Date of birth: ";
                cin >> p[countPlayers].dateOfBirth;

                cout << "Player's runs scored: ";
                cin >> p[countPlayers].runsScored;

                cout << "Number of matches played: ";
                cin >> p[countPlayers].numberOfMatches;
                cout << "\n";

                // Write in the file
                myfile();
                countPlayers++;
            }

            cout << "Do you want to add another player (Y/N): ";
            cin >> response;
            cout << "\n";
        } else {
            cout << "!!! Player list is full !!! \n\n";
            break;
        }
    } while (response == "Y" || response == "y");

}

// below function for display player infromation from file
void displayPlayerInformation(){
        string myText;
        ifstream MyReadFile("F:\\Player_details.txt");
        if(MyReadFile.is_open()){
            cout<<"\t****** Here all the players details ******\n\n";
            //use a while loop togther with the getline() function to read the file line by line
            while(getline (MyReadFile,myText)){
            cout<<myText<<"\n";
            }
            cout<<"\t****** Done ! ******\n\n";
        }
        else{
            cout<<"Unable to open the file !\n\n";
        }
}
//below function use to get playerid from the text file and store withing store array
void Storeplayer(){
    int num;
    ifstream f("F:\\Player_details.txt");
    string s;
    string condition; // to loop while loop contineuoly and go for the each line
    int line = 1;
    int count=0;

    while (count<NoOfPlayers)
    {
        for (int i = 0; i < line; i++){
        std::getline(f, s);
        }
        istringstream iss(s);
        string subs;

        while (iss >> subs) { 
            if (subs != condition) {
                line=1;
                line+=8;
            }
        }
            
        try {
            int num = stoi(subs); // Convert the string to an integer
            if (num!=0)
            {
                storePlayerCount++;
                store[count] = num; // Store the player registation nu in the array for availble list 
                Players[count]=num;// Store the player regisation no in the array for removeavaible list
            }
            else{
                break;
            }
        } catch (invalid_argument &e) {
            break;
        }

        count++;
    };
}

//below function help to remove players from the team 
void removePlayerFromAvailableList(int playerRegisterNo) {
    for (int i = 0; i < storePlayerCount; i++) {
        if (store[i] == playerRegisterNo) {
            // Shift elements to the left to remove the player
            for (int j = i; j < storePlayerCount - 1; j++) {
                store[j] = store[j + 1];
            }
            storePlayerCount--;
            break;
        }
    }
}

//this function use to remove players and check plyers consitions
void PlayerCheck(int &TeamCount,int teamArray[],int playerRegisterNo ){
    bool playerAlreadyExist=false;
     for (int i = 0; i < PlayerForEachTeam; i++)
        {
            if (teamArray[i]==playerRegisterNo)
            {
                playerAlreadyExist=true;
                break;
            }
        }
        if (!playerAlreadyExist)
        {
            if (TeamCount < PlayerForEachTeam) 
            {
                teamArray[TeamCount] = playerRegisterNo;
                TeamCount++;
                cout<< "player Added successfully !\n\n";
            } 
            else
            {
                cout << "Team is full. player cannot be added\n";
            }
        }

        else
        {
        cout<<"the player is already in the team !\n\n";
        }
    //below code will check the player id in the players array and increment teamcount by 1
    if (!playerAlreadyExist) {
        for (int i = 0; i < NoOfPlayers; i++) {
            if (playerRegisterNo == Players[i]) {
                teamCount[i]++;
                if (teamCount[i]==2) {
                    removePlayerFromAvailableList(playerRegisterNo);
                }
            }
        }
    }
}

//below function use to remove players from the team
void removePlayerFromTeam(int teamArray[],int playerRegisterNo){
     for (int i = 0; i < PlayerForEachTeam; i++) {
        if (teamArray[i] == playerRegisterNo) {
            // Shift elements to the left to remove the player
            for (int j = i; j < PlayerForEachTeam - 1; j++) {
                teamArray[j] = teamArray[j + 1];
            }
            reply="choosen player exist";
            break;
        }
     }
     if (reply!="choosen player exist")
     {
        cout<<"!! Choosen player doesn't exist !!\n\n";
     }
     else{
         cout<<"player removed succesfuly !\n\n";
     }
     
}

 //below function use to call specify array to add players
void CallArrayForAdd(char team,int playerRegisterNo) {
      team = toupper(team);
    if (team == 'A') {
        PlayerCheck(CountA,teamA,playerRegisterNo);
    } else if (team == 'B') {
        PlayerCheck(CountB,teamB,playerRegisterNo);
    } else if (team == 'C') {
        PlayerCheck(CountC,teamC,playerRegisterNo);
    } else if (team == 'D') {
        PlayerCheck(CountD,teamD,playerRegisterNo);
    } else if (team == 'E') {
        PlayerCheck(CountE,teamE,playerRegisterNo);
    } else {
        cout << "Invalid team!\n\n";
    }
}
//below function use to call specify array to remove players
void CallArrayForRemove(char team,int playerRegisterNo) {
      team = toupper(team);
    if (team == 'A') {
        removePlayerFromTeam(teamA, playerRegisterNo);
    } else if (team == 'B') {
        removePlayerFromTeam(teamB, playerRegisterNo);
    } else if (team == 'C') {
        removePlayerFromTeam(teamC, playerRegisterNo);
    } else if (team == 'D') {
        removePlayerFromTeam(teamD, playerRegisterNo);
    } else if (team == 'E') {
        removePlayerFromTeam(teamE, playerRegisterNo);
    } else {
        cout << "Invalid team!\n\n";
    }
}

//Below function for add members to team 
void addNewPlayersToTeam(){
    int number;
    do{
    cout <<"\t*Available Players*\n\n";
    for (int i = 0; i < NoOfPlayers; i++) {
            number = store[i];
            if(number!=0){
                cout << "\tPlayer Register No: " << number << "\n\n";
            }
    }
        cout << "What is team (A,B,C,D,E): ";
        cin >> team;
        cout << "Who is: ";
        cin >> playerRegisterNo;

        bool playerExists = false;
        for (int i = 0; i < NoOfPlayers; i++) {
            if (store[i] == playerRegisterNo) {
                playerExists = true;
                break;
            }
        }
        if (playerExists) {
            CallArrayForAdd(team, playerRegisterNo);
        } 
        else {
            cout << "Player not available\n";
        }
        cout << "Do you want to add another player (Y/N): ";
        cin >> reply;
        cout << "\n";
    } while (reply == "Y" || reply == "y");
}

//below function use to store team details in file
void StoreTeamDetails(){
     ofstream file("F:\\Team details.txt");

    int* teams[] = { teamA, teamB, teamC, teamD, teamE };
    string teamNames[] = { "A", "B", "C", "D", "E" };

    for (int t = 0; t < 5; t++) {
        file << "\t\t----Team " << teamNames[t] << " details---- \n\n";

        // Iterate through each player in the team
        for (int i = 0; i < PlayerForEachTeam; i++) {
            if (teams[t][i] != 0) {
                file << "\t\t  Reg No: " << teams[t][i] << " exist\n";
            }
        }

        file << "\t\t       Done !\n\n";
    }

    file.close(); 
}

//below function for the view team details
void viewTeamDetails(){

            string myText;
            ifstream MyReadFile("F:\\Team details.txt");
            if(MyReadFile.is_open()){
                cout<<"\t****** Here all the Teams details ******\n\n";
                //use a while loop togther with the getline() function to read the file line by line
                while(getline (MyReadFile,myText)){
                    cout<<myText<<"\n";
                }
            }
            else{
                cout<<"unable to open the file! \n\n";
            }
}

//below function for remove players from the team
void removePlayers(){
    do{

    int* teams[] = { teamA, teamB, teamC, teamD, teamE };
    string teamNames[] = { "A", "B", "C", "D", "E" };

    for (int t = 0; t < 5; t++) {
        cout << "\t\t----Team " << teamNames[t] << " details---- \n\n";

        // Iterate through each player in the team
        for (int i = 0; i < PlayerForEachTeam; i++) {
            if (teams[t][i] != 0) {
                cout << "\t\t Reg No: " << teams[t][i] << " exist\n";
            }
        }
         cout << "\t\t       Done !\n\n";
    }
        cout<<"select the team: ";
        cin>>team;
        cout<<"Which player: ";
        cin>>playerRegisterNo;

        CallArrayForRemove(team,playerRegisterNo);

        cout<<"do you want to continue: ";
        cin>>reply;
    } while (reply=="Y"||reply=="y");
}

//Below function for the search player by their name
void SearchPlayerbyname(){
    string response,reply;
    string playerDetails;
    do
    {   ifstream f("F:\\Player_details.txt");
        string s;
        string FirstName;
        int line = 3;
        int count=1;

        response.clear();
        playerDetails.clear();
        std::cout << "search player by first name: ";
        cin >> FirstName;
        cout<<"\n";
        
        while (count<=NoOfPlayers)
        {
            for (int i = 0; i < line; i++){
            std::getline(f, s);
         }
            istringstream iss(s);
            string subs;

            while (iss >> subs) {
                if (subs != FirstName) {
                    line=3;
                    line+=6;
                    
                }
            }
            if(subs==FirstName) {
                for (int i = 0; i < 6; i++) {
                    getline(f, s);
                    playerDetails += s + "\n";
                }
                response="!! player is available !!\n";
                break;
            }
            count++;
         };

        if(response!="!! player is available !!\n"){
            cout<<"!! player is not available !!\n\n";
        }
        else{
            cout<<response<<"\n";
            cout<<"player first name: "<<FirstName<<'\n';
            cout<<playerDetails;
        }
        cout<<"do you want to search another player(Y/N): ";
        cin>>reply;
        cout<<"\n";

        f.close();
    } while (reply=="Y" || reply=="y");
}
//Below function for the search players by their register No
void SearchPlayersbyID(){
    do
    {   
        ifstream f("F:\\Player_details.txt");
        string number,s;
        int line = 1;
        int count=1;

        response.clear();
        playerDetails.clear();
        std::cout << "Enter player registation number: ";
        cin >> number;
        cout<<"\n";

        while (count<=NoOfPlayers)
        {
            for (int i = 0; i < line; i++){
            std::getline(f, s);
            }
            istringstream iss(s);
            string subs;

            while (iss >> subs) {
                if (subs != number) {
                    line=1;
                    line+=8;
                }
            }
            if(subs==number) {
                for (int i = 0; i < 7; i++) {
                    getline(f, s);
                    playerDetails += s + "\n";
                }
                response="!! player is available !!\n";
                break;
             }
            count++;
        };

        if(response!="!! player is available !!\n"){
            cout<<"!! player is not available !!\n\n";
        }
        else{
            cout<<response;
            cout<<playerDetails;
            cout<<"\n";
        }
        cout<<"do you want to search another player(Y/N): ";
        cin>>reply;
        cout<<"\n";

        f.close();
    } while (reply=="Y" || reply=="y");
    
}

//Search main function
void Searchplayers(){
    cout<<"\t***** Here all the search options ! *****\n\n";
    cout<<"\t1.serach by Regsiter No\n";
    cout<<"\t2.serach by first name\n\n";
    cout<<"enter option no: ";
    cin>>choice;
    cout<<"\n";
    switch (choice)
    {
    case 1:
        SearchPlayersbyID();
        break;
    case 2:
        SearchPlayerbyname();
        break;
    
    default:
        cout<<"Invalid option\n";
        break;
    }
}

// Team manage main function
void TeamManage(){
    Storeplayer();
   do
   {
        cout<<"\t******All the manage team options*******\n\n";
        cout<<"\t1.Add players to the team \n";
        cout<<"\t2.Remove players from the team \n";
        cout<<"\t3.View team details \n";
        cout<<"\t4.Back to main menu \n\n";
        cout<<"input choice here: ";
        cin>>choice;
        cout<<"\n";
        switch (choice)
        {
        case 1:
            addNewPlayersToTeam();
            StoreTeamDetails();
            break;
        case 2:
            removePlayers();
            StoreTeamDetails();
            break;
        case 3:
            viewTeamDetails();
            break;
        case 4:
            break;
        default:
            cout<<"invalid choice\n";
            break;
        }
   } while (choice!=4);
   
}

//Below function for the user login
bool userLogin(){
    cout<<"**************************\n";
    cout<<  " \tLOG IN !\n";
    cout<<"**************************\n\n";
    string userName,Password;
    cout<<"enter username: ";
    cin>>userName;
    cout<<"enter password: ";
    cin>>Password;
    cout<<std::endl;
    if(userName=="dinod123"&& Password=="123" ){
        return true;
    }
    else{
        return false;
    }
}

// Below function for the user interface
int userInterface(){
    while (true)
    {
        int choice;
        int searchId;

        cout<<"\t\t..........Welcome to the Upcountry Warriors baseball club..........\n\n";
        cout<<"\t\t1.Add new players\n";
        cout<<"\t\t2.Display players information\n";
        cout<<"\t\t3.Search players\n";
        cout<<"\t\t4.Manage teams\n";
        cout<<"\t\t5.Log out\n";
        cout<<"\t\t6.Exit\n\n";

        cout<<"Enter the number: ";
        cin>>choice;
        cout<<"\n";
        
        switch (choice)
        {
        case 1:
            addNewPlayers();
            break;
        case 2:
            displayPlayerInformation();
            break;
        case 3:
            Searchplayers();
            break;
        case 4:
            TeamManage();
            break;
        case 5:
            cout<<"!! Logout suucessfull !!\n\n";
            return 1;
            break;
        case 6:
            cout<<"Good bye !";
            exit(0);
            break;
         default:
            cout<<"invalid choice !\n";
            break;
        }
    }
    
}

int main(){
    Storeplayer();
        int i;
        for(i=0;i<3;i++){
            if(userLogin()){
                cout<<"!! Login suucessfull !! \n\n";
                userInterface();
                i = -1;
            }

            else if(i==2){
            cout<<"Your attemts exceeded. Access denied.";
            }

            else{
                cout<<"Invalid username or password\n";
                cout<<"Please Try again...\n";
                cout<<std::endl;
            }
        }
}