#include<iostream>
#include<string>
#include<algorithm>
#include<cmath>
#include<cctype>
#include<iomanip>
#include<climits>
#include<cstdlib>
#include<numeric>
#include<vector>
#include<utility>
#include<set>
#include<unordered_set>
#include<map>
#include<stack>
#include<queue>
#include<fstream>
#pragma warning(disable : 4996)
using namespace std;
struct ClientData
{
    string AccountNumber, PinCode, Name, Phone;
    double AccountBalance;
    ClientData()
    {
        AccountNumber = PinCode = Name = Phone = "";
        AccountBalance = 0;
    }
};

struct User
{
    string userName, password;
    short access;
    User()
    {
        access = 0;
    }
};

short IntPow(short N, short power)
{
    short ogN = N;
    if (!power)
        N = 1;
    else
        while (power - 1)
        {
            N *= ogN;
            power--;
        }
    return N;
}

bool isYes(char ans)
{
    return ans == 'y' || ans == 'Y';
}

void PauseProgram(const string& Message)
{
    cout << "\n\n" << Message;
    system("pause > nul");
}

vector<ClientData>LoadClientsToVector(const string& fileName);

vector<User>LoadUsersToVector(const string& fileName);

bool IsClientFound(const string& accountNumber, const string& fileName)
{
    vector<ClientData>fileRecord = LoadClientsToVector(fileName);
    for (const ClientData& x : fileRecord)
        if (x.AccountNumber == accountNumber)
            return 1;
    return 0;
}

bool IsUserFound(const string& userName, const string& fileName)
{
    vector<User>fileRecord = LoadUsersToVector(fileName);
    for (const User& x : fileRecord)
        if (x.userName == userName)
            return 1;
    return 0;
}

void EnterClientData(ClientData& Client, const string& fileName, bool forUpdate = 0)
{
    if (!forUpdate)
    {
        string tmp;
        cout << "Enter account number ? ";
        cin >> tmp;
        while (IsClientFound(tmp, fileName))
        {
            cout << "account number already exists,Enter another one: ";
            cin >> tmp;
        }
        Client.AccountNumber = tmp;
    }
    cout << "\nEnter pincode ? ";
    cin >> Client.PinCode;
    cout << "\nEnter name ? ";
    getline(cin >> ws, Client.Name);
    cout << "\nEnter phone ? ";
    cin >> Client.Phone;
    cout << "\nEnter Account balance ? ";
    cin >> Client.AccountBalance;
}

void EnterUserData(User& user, const string& fileName, bool forUpdate = 0)
{
    char ans;
    if (!forUpdate)
    {
        string tmp;
        cout << "Enter userName ? ";
        getline(cin >> ws, tmp);
        while (IsUserFound(tmp, fileName))
        {
            cout << "User Name already exists,Enter another one: ";
            cin >> tmp;
        }
        user.userName = tmp;
    }
    cout << "Enter password ? ";
    getline(cin >> ws, user.password);
    cout << "Do you want to give full access ? y/n ? ";
    cin >> ans;
    if (isYes(ans))
        user.access = 127;
    else
    {
        user.access = 0;
        cout << "Do you want to give access to : (y / n) ? \n";
        cout << "Show client list ? ";
        cin >> ans;
        user.access += isYes(ans) * 1;
        cout << "Add new client ? ";
        cin >> ans;
        user.access += isYes(ans) * 2;
        cout << "Delete client ? ";
        cin >> ans;
        user.access += isYes(ans) * 4;
        cout << "Update client ? ";
        cin >> ans;
        user.access += isYes(ans) * 8;
        cout << "Find client ? ";
        cin >> ans;
        user.access += isYes(ans) * 16;
        cout << "Transactions ? ";
        cin >> ans;
        user.access += isYes(ans) * 32;
        cout << "Manage users ? ";
        cin >> ans;
        user.access += isYes(ans) * 64;
    }
}

string ConvertRecordToLine(const ClientData& client, const string& Separator = "#//#")
{
    string s;
    s += client.AccountNumber + Separator;
    s += client.PinCode + Separator;
    s += client.Name + Separator;
    s += client.Phone + Separator;
    s += to_string(client.AccountBalance);
    return s;
}

string ConvertRecordToLine(const User& user, const string& Separator = "#//#")
{
    string s;
    s += user.userName + Separator;
    s += user.password + Separator;
    s += to_string(user.access);
    return s;
}

vector<string>SplitString(string& s, const string& Separator = "#//#")
{
    vector<string>words;
    string tmp;
    int pos;
    while ((pos = s.find(Separator)) != -1)
    {
        tmp = s.substr(0, pos);
        words.push_back(tmp);
        tmp = "";
        s.erase(0, pos + Separator.size());
    }
    words.push_back(s);
    return words;
}

ClientData ConvertLineToRecordForClients(string& Line, const string& Separator = "#//#")
{
    ClientData tmp;
    vector<string>Data = SplitString(Line);
    tmp.AccountNumber = Data[0];
    tmp.PinCode = Data[1];
    tmp.Name = Data[2];
    tmp.Phone = Data[3];
    tmp.AccountBalance = stod(Data[4]);
    return tmp;
}

User ConvertLineToRecordForUsers(string& Line, const string& Separator = "#//#")
{
    User tmp;
    vector<string>Data = SplitString(Line);
    tmp.userName = Data[0];
    tmp.password = Data[1];
    tmp.access = stoi(Data[2]);
    return tmp;
}

vector<ClientData>LoadClientsToVector(const string& fileName)
{
    fstream f;
    string tmp1;
    ClientData tmp2;
    vector<ClientData>Clients;
    f.open(fileName, ios::in);
    while (getline(f >> ws, tmp1))
    {
        tmp2 = ConvertLineToRecordForClients(tmp1);
        Clients.push_back(tmp2);
    }
    return Clients;
}

vector<User>LoadUsersToVector(const string& fileName)
{
    fstream f;
    string tmp1;
    User tmp2;
    vector<User>users;
    f.open(fileName, ios::in);
    while (getline(f >> ws, tmp1))
    {
        tmp2 = ConvertLineToRecordForUsers(tmp1);
        users.push_back(tmp2);
    }
    return users;
}

template<class T>
void SaveVectorToFile(const string& fileName, const vector<T>& Persons)
{
    fstream file;
    file.open(fileName, ios::out);
    for (const T& x : Persons)
        file << ConvertRecordToLine(x) << endl;
    file.close();
}

void AddClients(const string& fileName)
{
    char AnotherClient = 'Y';
    fstream file;
    ClientData c;
    file.open(fileName, ios::app);
    while (AnotherClient == 'y' || AnotherClient == 'Y')
    {
        EnterClientData(c, fileName);
        file << ConvertRecordToLine(c) << endl;
        cout << "Do you want to add another client Y/N ? ";
        cin >> AnotherClient;
    }
    file.close();
}

void AddUsers(const string& fileName)
{
    char AnotherUser = 'Y';
    fstream file;
    User u;
    file.open(fileName, ios::app);
    while (isYes(AnotherUser))
    {
        cout << "Adding new user :\n";
        EnterUserData(u, fileName);
        file << ConvertRecordToLine(u) << endl;
        cout << "Do you want to add another user Y/N ? ";
        cin >> AnotherUser;
    }
    file.close();
}

void PrintClientData(const ClientData& client)
{
    cout << "The following are the client details: \n\n";
    cout << setw(15) << left << "Account number" << " : " << client.AccountNumber << "\n\n";
    cout << setw(15) << left << "Pin code" << " : " << client.PinCode << "\n\n";
    cout << setw(15) << left << "Name" << " : " << client.Name << "\n\n";
    cout << setw(15) << left << "Phone" << " : " << client.Phone << "\n\n";
    cout << setw(15) << left << "Account balance" << " : " << fixed << setprecision(10) << client.AccountBalance << "\n\n";
}

void PrintUserData(const User& user)
{
    cout << "The following are the user details: \n";
    cout << "----------------------------------------------\n";
    cout << setw(12) << left << "Username" << " : " << user.userName << "\n";
    cout << setw(12) << left << "Password" << " : " << user.password << "\n";
    cout << setw(12) << left << "Permissions" << " : " << user.access << "\n";
    cout << "----------------------------------------------\n";
}

void PrintClientsList(const string& fileName)
{
    vector<ClientData>Clients = LoadClientsToVector(fileName);
    cout << "\t\t\t\t\tClient List (" << Clients.size() << ") Client(s).\n";
    cout << "___________________________________________________________________________________________________________\n\n";
    cout << "| Account Number | ";
    cout << "Pin Code | ";
    cout << "Client Name                                       | ";
    cout << "Phone        | ";
    cout << "Balance\n";
    cout << "___________________________________________________________________________________________________________\n\n";
    if (Clients.size())
        for (int i = 0; i < Clients.size(); i++)
        {
            cout << "| " << setw(15) << left << Clients[i].AccountNumber;
            cout << "| " << setw(9) << left << Clients[i].PinCode;
            cout << "| " << setw(50) << left << Clients[i].Name;
            cout << "| " << setw(13) << left << Clients[i].Phone;
            cout << "| " << fixed << setprecision(10) << Clients[i].AccountBalance << endl;
        }
    else
        cout << "No clients in the system.\n";
}

void PrintUsersList(const string& fileName)
{
    vector<User>Users = LoadUsersToVector(fileName);
    cout << "\t\t\t\t\tUsers List (" << Users.size() << ") User(s).\n";
    cout << "___________________________________________________________________________________________________________\n\n";
    cout << setw(20) << left << "| User Name";
    cout << setw(15) << "| Password";
    cout << "| Permissions\n";
    cout << "___________________________________________________________________________________________________________\n\n";
    if (Users.size())
        for (int i = 0; i < Users.size(); i++)
        {
            cout << "| " << setw(18) << left << Users[i].userName;
            cout << "| " << setw(13) << left << Users[i].password;
            cout << "| " << Users[i].access << endl;
        }
    else
        cout << "No users in the system.\n";
}

bool FindClientByACN(const string& accountNumber, const string& fileName, ClientData& client)
{
    vector<ClientData>Clients = LoadClientsToVector(fileName);
    for (ClientData& x : Clients)
        if (x.AccountNumber == accountNumber)
        {
            client = x;
            return 1;
        }
    return 0;
}

bool FindUserByName(const string& userName, const string& fileName, User& user)
{
    vector<User>Users = LoadUsersToVector(fileName);
    for (User& x : Users)
        if (x.userName == userName)
        {
            user = x;
            return 1;
        }
    return 0;
}

void DeleteClientFromFile(const string& fileName, const string& accountNumber)
{
    fstream file;
    string tmp;
    vector<ClientData>clients = LoadClientsToVector(fileName);
    file.open(fileName, ios::out);
    for (ClientData& x : clients)
        if (x.AccountNumber != accountNumber)
        {
            tmp = ConvertRecordToLine(x);
            file << tmp << '\n';
        }
    file.close();
}

void DeleteUserFromFile(const string& fileName, const string& userName)
{
    fstream file;
    string tmp;
    vector<User>clients = LoadUsersToVector(fileName);
    file.open(fileName, ios::out);
    for (User& x : clients)
        if (x.userName != userName)
        {
            tmp = ConvertRecordToLine(x);
            file << tmp << '\n';
        }
    file.close();
}

void DeleteClient(const string& fileName)
{
    char ans;
    string accountNumber;
    ClientData client;
    cout << "Please enter account number : ";
    cin >> accountNumber;
    if (FindClientByACN(accountNumber, fileName, client))
    {
        PrintClientData(client);
        cout << "Are you sure you want to delete this client ? Y/N ";
        cin >> ans;
        if (tolower(ans) == 'y')
        {
            DeleteClientFromFile(fileName, accountNumber);
            cout << "\nClient deleted successfully.";
        }
        else
            cout << "\nClient stil not deleted.";
    }
    else
        cout << "Client with account number (" << accountNumber << ") not found!";

}

void DeleteUser(const string& fileName)
{
    char ans;
    string name;
    User user;
    cout << "Please enter Username: ";
    cin >> name;
    if (name == "Admin")
        cout << "You cannot delete this user.\n";
    else
        if (FindUserByName(name, fileName, user))
        {
            PrintUserData(user);
            cout << "Are you sure you want to delete this user ? Y/N ";
            cin >> ans;
            if (tolower(ans) == 'y')
            {
                DeleteUserFromFile(fileName, name);
                cout << "\nUser deleted successfully.";
            }
            else
                cout << "\nUser stil not deleted.";
        }
        else
            cout << "User with name (" << name << ") not found!";


}

void UpdateClientInFile(const string& fileName, const ClientData& Updated)
{
    vector<ClientData>clients = LoadClientsToVector(fileName);
    for (ClientData& x : clients)
        if (x.AccountNumber == Updated.AccountNumber)
        {
            x = Updated;
            break;
        }
    SaveVectorToFile(fileName, clients);
}

void UpdateUserInFile(const string& fileName, const User& Updated)
{
    vector<User>users = LoadUsersToVector(fileName);
    for (User& x : users)
        if (x.userName == Updated.userName)
        {
            x = Updated;
            break;
        }
    SaveVectorToFile(fileName, users);
}

void UpdateClient(const string& fileName)
{
    char ans;
    string accountNumber;
    ClientData client;
    cout << "Please Enter account Number : ";
    cin >> accountNumber;
    if (FindClientByACN(accountNumber, fileName, client))
    {
        PrintClientData(client);
        cout << "Are you sure you want to Update this client ? Y/N ";
        cin >> ans;
        if (tolower(ans) == 'y')
        {
            cout << "Enter new information\n\n";
            EnterClientData(client, fileName, 1);
            UpdateClientInFile(fileName, client);
            cout << "\nClient Updated successfully.";
        }
        else
            cout << "\nClient stil not updated.";
    }
    else
        cout << "Client with account number (" << accountNumber << ") not found!";
}

void UpdateUser(const string& fileName)
{
    char ans;
    string name;
    User user;
    cout << "Please Enter Username : ";
    cin >> name;
    if (FindUserByName(name, fileName, user))
    {
        PrintUserData(user);
        cout << "Are you sure you want to Update this user ? Y/N ";
        cin >> ans;
        if (tolower(ans) == 'y')
        {
            cout << "Enter new information\n\n";
            EnterUserData(user, fileName, 1);
            UpdateUserInFile(fileName, user);
            cout << "\nUser Updated successfully.";
        }
        else
            cout << "\nUser stil not updated.";
    }
    else
        cout << "User with Username (" << name << ") not found!";
}

void ShowLoginScreen()
{
    cout << "\n--------------------------------------\n";
    cout << "\t    Login screen\n";
    cout << "--------------------------------------\n";
}

void ShowMenuScreen()
{
    cout << "===============================================================\n";
    cout << "\t\t\tMain menu screen\n";
    cout << "===============================================================\n";
    cout << "\t[1] Show client list.\n";
    cout << "\t[2] Add new client.\n";
    cout << "\t[3] Delete client.\n";
    cout << "\t[4] Update client info.\n";
    cout << "\t[5] Find client.\n";
    cout << "\t[6] Transactions.\n";
    cout << "\t[7] Manage Users.\n";
    cout << "\t[8] Logout.\n";
    cout << "===============================================================\n";
    cout << "Choose what do you want to do ([1 to 7]) ? ";
}

void ShowAddClientScreen()
{
    cout << "\n----------------------------------------------\n";
    cout << "\t     Add new client screen\n";
    cout << "----------------------------------------------\n";
    cout << "Adding new client :\n";
}

void ShowAddUserScreen()
{
    cout << "\n----------------------------------------------\n";
    cout << "\t     Add new User screen\n";
    cout << "----------------------------------------------\n";
}

void ShowDeleteUserScreen()
{
    cout << "\n----------------------------------------------\n";
    cout << "\t     Delete User screen\n";
    cout << "----------------------------------------------\n";
}

void ShowDeleteClientScreen()
{
    cout << "\n--------------------------------------\n";
    cout << "\t  Delete client screen\n";
    cout << "--------------------------------------\n";
}

void ShowUpdateClientScreen()
{
    cout << "\n---------------------------------\n";
    cout << "    Update client info screen\n";
    cout << "---------------------------------\n";
}

void ShowUpdateUserScreen()
{
    cout << "\n---------------------------------\n";
    cout << "    Update user info screen\n";
    cout << "---------------------------------\n";
}

void ShowFindClientScreen()
{
    cout << "\n---------------------------------\n";
    cout << "\tFind Client Screen\n";
    cout << "---------------------------------\n";
}

void ShowTransactionsMenuScreen()
{
    cout << "=====================================================\n";
    cout << "\t\tTransactions menu screen\n";
    cout << "=====================================================\n";
    cout << "\t[1] Deposit.\n";
    cout << "\t[2] Withdraw.\n";
    cout << "\t[3] Total balances.\n";
    cout << "\t[4] Main menu.\n";
    cout << "=====================================================\n";
    cout << "Choose what do you want to do [1 to 4] ? ";
}

void ShowManageUsersMenuScreen()
{
    cout << "=====================================================\n";
    cout << "\t\tManage Users menu screen\n";
    cout << "=====================================================\n";
    cout << "\t[1] List Users.\n";
    cout << "\t[2] Add New User.\n";
    cout << "\t[3] Delete User.\n";
    cout << "\t[4] Update User.\n";
    cout << "\t[5] Find User.\n";
    cout << "\t[6] Main menu.\n";
    cout << "=====================================================\n";
    cout << "Choose what do you want to do [1 to 6] ? ";
}

void ShowDepositScreen()
{
    cout << "\n---------------------------------\n";
    cout << "\t Deposit Screen\n";
    cout << "---------------------------------\n";
}

void ShowWithdrawScreen()
{
    cout << "\n---------------------------------\n";
    cout << "\t    Withdraw\n";
    cout << "---------------------------------\n";
}

void ShowTotalBalancesScreen(const string& fileName)
{
    long long Total = 0;
    vector<ClientData>c = LoadClientsToVector(fileName);
    PrintClientsList(fileName);
    for (const ClientData& x : c)
        Total += x.AccountBalance;
    cout << "___________________________________________________________________________________________________________\n\n";
    cout << "\t\t\t\t\t Total balances = " << Total << "\n\n";
}

void Deposit(const string& fileName)
{
    double amount;
    char ans;
    ClientData c;
    string ac;
    cout << "Please enter account number : ";
    cin >> ac;
    while (!FindClientByACN(ac, fileName, c))
    {
        cout << "Client with account number [" << ac << "] does not exist.\n";
        cout << "Please enter account number : ";
        cin >> ac;
    }
    PrintClientData(c);
    cout << "Please enter deposit amount : ";
    cin >> amount;
    cout << "Are you sure you want to perform this transaction (Y/N) ? ";
    cin >> ans;
    if (tolower(ans) == 'y')
    {
        c.AccountBalance += amount;
        UpdateClientInFile(fileName, c);
        cout << "Deposit done succesfully.";
    }
    else
        cout << "Deposit transaction discarded.";
    cout << "\n\n";
}

void Withdraw(const string& fileName)
{
    double amount;
    char ans;
    ClientData c;
    string ac;
    cout << "Please enter account number : ";
    cin >> ac;
    while (!FindClientByACN(ac, fileName, c))
    {
        cout << "Client with account number [" << ac << "] does not exist.\n";
        cout << "Please enter account number : ";
        cin >> ac;
    }
    PrintClientData(c);
    cout << "Please enter Withdraw amount : ";
    cin >> amount;
    while (amount > c.AccountBalance)
    {
        cout << "Amount exceeds the balance , you can withdraw up to : " << c.AccountBalance << ".\n";
        cout << "Please enter another amount: ";
        cin >> amount;
    }
    cout << "Are you sure you want to perform this transaction (Y/N) ? ";
    cin >> ans;
    if (tolower(ans) == 'y')
    {
        c.AccountBalance -= amount;
        UpdateClientInFile(fileName, c);
        cout << "Withdraw done succesfully.";
    }
    else
        cout << "Withdraw transaction discarded.";
    cout << "\n\n";
}

void ShowEnd()
{
    cout << "\n---------------------------------\n";
    cout << "\tProgram ends :-)\n";
    cout << "---------------------------------\n";
}

char ReadInterfaceChoice(short from, short to)
{
    short num;
    cin >> num;
    while (num < from || num > to)
    {
        cout << "Number is not in the range (" << from << " to " << to << ") please reEnter your choice : ";
        cin >> num;
    }
    return num;
}

User Login(const string& usersFileName)
{
    bool  wrong = 0;
    User tmp;
    string Name, Password;
    do
    {
        ShowLoginScreen();
        if (wrong)
            cout << "Invalid userName/password !\n";
        cout << "Enter userName : "; getline(cin >> ws, Name);
        cout << "Enter userPassword :"; getline(cin >> ws, Password);
        FindUserByName(Name, usersFileName, tmp);
        wrong = (tmp.password != Password);
        system("cls");
    } while (wrong);
    return tmp;
}

bool HavePermission(short choice, short access)
{
    return ((IntPow(2, choice - 1) & access) > 0);
}

void PrintAccessDenied()
{
    cout << "\n---------------------------------\n";
    cout << "Access Denied,\n";
    cout << "You dont have permission to do this,\n";
    cout << "Please contact your admin.\n";
    cout << "---------------------------------\n";
}

void StartProgram(const string& clientsFileName, const string& usersFileName)
{
    User user = Login(usersFileName);
    short cM;
    do
    {
        ShowMenuScreen();
        cM = ReadInterfaceChoice(1, 8);
        system("cls");
        if (cM == 1)
        {
            if (HavePermission(cM, user.access))
                PrintClientsList(clientsFileName);
            else
                PrintAccessDenied();
        }
        else if (cM == 2)
        {
            if (HavePermission(cM, user.access))
            {
                ShowAddClientScreen();
                AddClients(clientsFileName);
            }
            else
                PrintAccessDenied();
        }
        else if (cM == 3)
        {
            if (HavePermission(cM, user.access))
            {
                ShowDeleteClientScreen();
                DeleteClient(clientsFileName);
            }
            else
                PrintAccessDenied();
        }
        else if (cM == 4)
        {
            if (HavePermission(cM, user.access))
            {
                ShowUpdateClientScreen();
                UpdateClient(clientsFileName);
            }
            else
                PrintAccessDenied();
        }
        else if (cM == 5)
        {
            if (HavePermission(cM, user.access))
            {
                ClientData tmp;
                string accountNumber;
                ShowFindClientScreen();
                cout << "Please enter account number : ";
                cin >> accountNumber;
                if (FindClientByACN(accountNumber, clientsFileName, tmp))
                    PrintClientData(tmp);
                else
                    cout << "Client with account number (" << accountNumber << ") not found!";
            }
            else
                PrintAccessDenied();
        }
        else if (cM == 6)
        {
            if (HavePermission(cM, user.access))
            {
                short cT;
                do
                {
                    ShowTransactionsMenuScreen();
                    cT = ReadInterfaceChoice(1, 4);
                    system("cls");
                    if (cT == 1)
                    {
                        ShowDepositScreen();
                        Deposit(clientsFileName);
                    }
                    else if (cT == 2)
                    {
                        ShowWithdrawScreen();
                        Withdraw(clientsFileName);
                    }
                    else if (cT == 3)
                        ShowTotalBalancesScreen(clientsFileName);
                    if (cT != 4)
                        PauseProgram("Press any key to go back to Transactions menu screen . . .");
                    system("cls");
                } while (cT != 4);
            }
            else
            {
                PrintAccessDenied();
                PauseProgram("Press any key to go back to main menu . . .");
            }
        }
        else if (cM == 7)
        {
            if (HavePermission(cM, user.access))
            {
                short cMG;
                do
                {
                    ShowManageUsersMenuScreen();
                    cMG = ReadInterfaceChoice(1, 6);
                    system("cls");
                    if (cMG == 1)
                        PrintUsersList(usersFileName);
                    else if (cMG == 2)
                    {
                        ShowAddUserScreen();
                        AddUsers(usersFileName);
                    }
                    else if (cMG == 3)
                    {
                        ShowDeleteUserScreen();
                        DeleteUser(usersFileName);
                    }
                    else if (cMG == 4)
                    {
                        ShowUpdateUserScreen();
                        UpdateUser(usersFileName);
                    }
                    else if (cMG == 5)
                    {
                        User tmp;
                        string Name;
                        ShowFindClientScreen();
                        cout << "Please enter Username : ";
                        cin >> Name;
                        if (FindUserByName(Name, usersFileName, tmp))
                            PrintUserData(tmp);
                        else
                            cout << "User with account number (" << Name << ") not found!";
                    }
                    if (cMG != 6)
                        PauseProgram("Press any key to go back to Manage users menu screen . . .");
                    system("cls");
                } while (cMG != 6);
            }
            else
            {
                PrintAccessDenied();
                PauseProgram("Press any key to go back to main menu . . .");
            }
        }
        else
        {
            user = Login(usersFileName);
        }
        if (cM != 8 && cM != 7 && cM != 6)
            PauseProgram("Press any key to go back to main menu . . .");
        system("cls");
    } while (1);
}

int main(void)
{
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), srand(time(0));
    StartProgram("clients.txt", "users.txt");




    return 0;
}
/* {
 first for background
 second for text
        0 = Black       8 = Gray
        1 = Blue        9 = Light Blue
        2 = Green       A = Light Green
        3 = Aqua        B = Light Aqua
        4 = Red         C = Light Red
        5 = Purple      D = Light Purple
        6 = Yellow      E = Light Yellow
        7 = White       F = Bright White
}*/