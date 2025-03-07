#include<iostream>
#include<time.h>
#include<math.h>
#include<iomanip>
#include<conio.h>
#include<stdlib.h>
#include<string>
#include<fstream>
#include<stdio.h>
#define MAX_CLUBS 16
#define DIR "clubs.bin"
using namespace std;

class FClub {
public:
	char cName[50], city[50];
	int registrationNumber = 0, year, numberOfPlayers;
	int wins = 0, losses = 0, draws = 0;
};
void DisplayMenu(FClub clubs[]);
void AddClubs(FClub clubs[]);
bool CheckClubs(FClub clubs[]);
int GetLength(FClub clubs[]);
void ShowAllClubs(FClub clubs[]);
string FindLongestName(FClub clubs[]);
string FindLongestCity(FClub clubs[]);
string ConvertCharToString(char a[], int lenght);
void GetClubWithMostWins(FClub clubs[]);
void GetClubsWithLeastPlayers(FClub clubs[]);
void SortClubs(FClub clubs[]);
void AddInFile(FClub clubs[]);
void FillClubsFromFile(FClub clubs[]);
void SortFile(FClub clubs[]);
string FillGaps(char a[]);
void DisplaySubMenu(FClub clubs[]);
void ShowClubsWithWins(FClub clubs[]);
void SearchClubs(FClub clubs[]);
void Tournament(FClub clubs[]);
void ShowLeaderboard(FClub clubs[]);
void DeleteClub(FClub clubs[]);
int ContainsId(FClub clubs[], int id);
void Delay();
void Reset();

int main() {
	setlocale(LC_ALL, "");
	FClub clubs[MAX_CLUBS];
	srand(time(0));
	FillClubsFromFile(clubs);
	DisplayMenu(clubs);
	return 0;
}

void DisplayMenu(FClub clubs[]) {
	int option;
	string opt = "";
	do {
		do {
			cout << "Choose option:\n" <<
				"1 - Add Football club\n" <<
				"2 - Display all clubs\n" <<
				"3 - Delete club\n" <<
				"4 - Sort clubs\n" <<
				"5 - Sub menu\n" <<
				"6 - Organize tournament\n" <<
				"7 - Leave\n";
			getline(cin, opt);
		} while (isdigit(atoi(opt.c_str())));
		option = atoi(opt.c_str());
		switch (option)
		{
		case 1:
			AddClubs(clubs);
			break;
		case 2:
			ShowAllClubs(clubs);
			break;
		case 3:
			DeleteClub(clubs);
			break;
		case 4:
			SortClubs(clubs);
			break;
		case 5:
			DisplaySubMenu(clubs);
			break;
		case 6:
			Reset();
			Tournament(clubs);
			break;
		case 7:
			exit(0);
			break;
		default:
			cout << "Please enter valid number\n";
			Delay();
			Reset();
			continue;
		}
		Delay();
		cout << "\nPress any button to continue\n";
		_getch();
		Reset();
	} while (true);
}

void AddClubs(FClub* clubs) {
	FClub* added = new FClub[MAX_CLUBS - GetLength(clubs)];
	if (GetLength(clubs) < MAX_CLUBS)
	{
		int n;
		do {
			Reset();
			cout << "Type number of clubs you want to enter:";
			cin >> n;
		} while (n > MAX_CLUBS || n <= 0 || n > MAX_CLUBS - GetLength(clubs));
		FClub club;
		for (int i = 0; i < n; i++)
		{
			cin.ignore();
			cout << "\nEnter the data for club " << i + 1 << endl;
			if (GetLength(clubs) == 0)
				club.registrationNumber = 1;
			else club.registrationNumber = clubs[GetLength(clubs) - 1].registrationNumber + 1;			//NUMBER
			cout << "\nEnter the club name: ";							cin.getline(club.cName, 50);	//NAME
			cout << "Enter the club's city: ";							cin.getline(club.city, 50);		//CITY
			cout << "Enter when the club has been created(year): ";		cin >> club.year;				//YEAR
			cout << "Enter the number of players: ";					cin >> club.numberOfPlayers;	//PLAYERS
			added[GetLength(added)] = club;
			clubs[GetLength(clubs)] = added[GetLength(added) - 1];
		}
		AddInFile(added);
	}
	else
	{
		cout << "The max number of clubs is " << MAX_CLUBS << endl;
	}
}

bool CheckClubs(FClub clubs[]) {
	if (clubs[0].registrationNumber != 0)
		return true;
	return false;
}

int GetLength(FClub clubs[]) {
	int count = 0;
	for (int i = 0; i < MAX_CLUBS; i++) {
		if (!CheckClubs(clubs) || clubs[i].registrationNumber == 0) {
			return count;
		}
		count++;
	}
}

void ShowAllClubs(FClub clubs[]) {
	Reset();
	int defaultWidth = 4, idWidth;
	int longestName = FindLongestName(clubs).length();
	int longestCity = FindLongestCity(clubs).length();
	int nameWidth, cityWidth;
	nameWidth = (longestName > 9) ? defaultWidth + longestName - 9 : defaultWidth;
	cityWidth = (longestCity > 4) ? defaultWidth + longestCity - 4 : defaultWidth;
	cout << "Reg. number" << setw(defaultWidth + 9) << "Club name" << setw(nameWidth + 4) << "City" << setw(cityWidth + 4) << "Year" << setw(defaultWidth + 7) << "Players" << setw(defaultWidth + 4) << "Wins" << setw(defaultWidth + 6) << "Losses" << setw(defaultWidth + 5) << "Draws" << endl;
	for (int i = 0; i < GetLength(clubs); i++)
	{
		FClub cur = clubs[i];
		if (cur.registrationNumber != -1)
		{
			idWidth = (cur.registrationNumber > 9) ? defaultWidth + 10 + strlen(cur.cName) - 1 : defaultWidth + 10 + strlen(cur.cName);
			int finN, finC, tempw;
			if (strlen(cur.cName) > 9)
			{
				if (strlen(cur.cName) < longestName)
				{
					tempw = longestName - strlen(cur.cName);
					finN = tempw + defaultWidth + strlen(cur.city);
				}
				else
				{
					tempw = 0;
					finN = defaultWidth + strlen(cur.city);
				}
			}
			else {
				tempw = longestName - 9;
				nameWidth = (longestName > 9) ? defaultWidth + abs(tempw) : defaultWidth;
				tempw = strlen(cur.cName) - 9;
				finN = abs(tempw) + nameWidth + strlen(cur.city);
			}
			if (strlen(cur.city) > 4)
			{
				if (strlen(cur.city) < longestCity)
				{
					tempw = longestCity - strlen(cur.city);
					finC = tempw + defaultWidth + 4;
				}
				else
				{
					tempw = 0;
					finC = defaultWidth + 4;
				}
			}
			else {
				tempw = longestCity - 4;
				cityWidth = (longestCity > 4) ? defaultWidth + abs(tempw) : defaultWidth;
				tempw = strlen(cur.city) - 4;
				finC = abs(tempw) + cityWidth + 4;
			}
			cout <<
				cur.registrationNumber << setw(idWidth) <<
				cur.cName << setw(finN) <<
				cur.city << setw(finC) <<
				cur.year << "    " <<
				cur.numberOfPlayers << setw(7 - to_string(cur.numberOfPlayers).length() + defaultWidth + to_string(cur.wins).length()) <<
				cur.wins << setw(4 - to_string(cur.wins).length() + defaultWidth + to_string(cur.losses).length()) <<
				cur.losses << setw(6 - to_string(cur.losses).length() + defaultWidth + to_string(cur.draws).length()) <<
				cur.draws << endl;
		}
	}
}

void DeleteClub(FClub clubs[]) {
	ShowAllClubs(clubs);
	cout << "\nAnything that is not a valid registration number will take you back to the main menu!\nType the registration number of the club you want to delete:\n";
	int option;
	string opt = "";
	getline(cin, opt);
	if (isdigit(atoi(opt.c_str())))
		return;
	option = ContainsId(clubs, atoi(opt.c_str()));
	if (option == -1)
		return;
	clubs[option].registrationNumber = -1;
	SortFile(clubs);
	cout << "\nDeleting complete!\n";
}

int ContainsId(FClub clubs[], int id) {
	for (int i = 0; i < GetLength(clubs); i++)
	{
		if (id == clubs[i].registrationNumber)
		{
			return i;
		}
	}
	return -1;
}

string FindLongestName(FClub clubs[]) {
	int k = 0;
	for (int i = 1; i < GetLength(clubs); i++)
	{
		if (strlen(clubs[k].cName) < strlen(clubs[i].cName))
		{
			k = i;
		}
	}
	return ConvertCharToString(clubs[k].cName, strlen(clubs[k].cName));
}

string FindLongestCity(FClub clubs[]) {
	int k = 0;
	for (int i = 1; i < GetLength(clubs); i++)
	{
		if (strlen(clubs[k].city) < strlen(clubs[i].city))
		{
			k = i;
		}
	}
	return ConvertCharToString(clubs[k].city, strlen(clubs[k].city));
}

string ConvertCharToString(char a[], int length) {
	string s = "";
	for (int i = 0; i < length; i++)
	{
		s += a[i];
	}
	return s;
}

void GetClubWithMostWins(FClub clubs[]) {
	if (CheckClubs(clubs))
	{
		FClub most = clubs[0];
		for (int i = 0; i < GetLength(clubs); i++)
		{
			if (clubs[i].wins > most.wins)
			{
				most = clubs[i];
			}
		}
		cout << "The club with the most wins is: " << most.cName << " with " << most.wins << " wins";
	}
	else cout << "There is no clubs added.";
}

void GetClubsWithLeastPlayers(FClub clubs[]) {
	if (CheckClubs(clubs))
	{
		bool f = false;
		for (int i = GetLength(clubs) - 1; i >= 0; i--)
		{
			if (clubs[i].numberOfPlayers < 16)
			{
				f = true;
				cout << "Reg. number: " << clubs[i].registrationNumber << setw(4 + 9) << "Club name: " << clubs[i].cName << setw(4 + 7) << "Players: " << clubs[i].numberOfPlayers << endl;
			}
		}
		if (!f)
		{
			cout << "There are no clubs with players less than 16";
			return;
		}
	}
	else cout << "There is no clubs added.";
}

void SortClubs(FClub clubs[]) {
	bool f;
	int count = 0;
	int option;
	string opt = "";
	do {
		Reset();
		cout << "Choose option:\n" <<
			"1 - Sort by registration number\n" <<
			"2 - Sort by year of creation\n" <<
			"3 - Sort by number of tabulated players\n" <<
			"4 - Back\n";
		getline(cin, opt);
	} while (isdigit(atoi(opt.c_str())));
	option = atoi(opt.c_str());
	switch (option) {
	case 1:
		for (int i = 0; i < GetLength(clubs) - 1; i++)
		{
			f = false;
			for (int j = 0; j < GetLength(clubs) - i - 1; j++)
			{
				if (clubs[j].registrationNumber > clubs[j + 1].registrationNumber)
				{
					FClub temp = clubs[j];
					clubs[j] = clubs[j + 1];
					clubs[j + 1] = temp;
					f = true;
				}
			}
			if (!f) break;
			count++;
		}
		if (count > 0) {
			SortFile(clubs);
		}
		break;
	case 2:
		for (int i = 0; i < GetLength(clubs) - 1; i++)
		{
			f = false;
			for (int j = 0; j < GetLength(clubs) - i - 1; j++)
			{
				if (clubs[j].year > clubs[j + 1].year)
				{
					FClub temp = clubs[j];
					clubs[j] = clubs[j + 1];
					clubs[j + 1] = temp;
					f = true;
				}
			}
			if (!f) break;
			count++;
		}
		if (count > 0) {
			SortFile(clubs);
		}
		break;
	case 3:
		for (int i = 0; i < GetLength(clubs) - 1; i++)
		{
			f = false;
			for (int j = 0; j < GetLength(clubs) - i - 1; j++)
			{
				if (clubs[j].numberOfPlayers < clubs[j + 1].numberOfPlayers)
				{
					FClub temp = clubs[j];
					clubs[j] = clubs[j + 1];
					clubs[j + 1] = temp;
					f = true;
				}
			}
			if (!f) break;
			count++;
		}
		if (count > 0) {
			SortFile(clubs);
		}
		break;
		break;
	case 4:
		return;
	}
}

void AddInFile(FClub clubs[]) {
	fstream file;
	file.open(DIR, ios::binary | ios::app);
	string line = "";
	for (int i = 0; i < GetLength(clubs); i++)
	{
		if (clubs[i].registrationNumber != -1)
			file
			<< clubs[i].registrationNumber << " " <<
			FillGaps(clubs[i].cName) << " " <<
			FillGaps(clubs[i].city) << " " <<
			clubs[i].year << " " <<
			clubs[i].numberOfPlayers << " " <<
			clubs[i].wins << " " <<
			clubs[i].losses << " " <<
			clubs[i].draws << endl;
	}
	file.close();
}

void FillClubsFromFile(FClub clubs[]) {
	ifstream file;
	file.open(DIR, ios::binary | ios::in);
	if (file.is_open())
	{
		string line, lines[8];
		FClub club;
		int count = 0;
		while (file >> line)
		{
			lines[count++] = line;
			if (count == 8)
			{
				club.registrationNumber = stoi(lines[0]);
				strcpy_s(club.cName, lines[1].c_str());
				strcpy_s(club.city, lines[2].c_str());
				club.year = stoi(lines[3]);
				club.numberOfPlayers = stoi(lines[4]);
				club.wins = stoi(lines[5]);
				club.losses = stoi(lines[6]);
				club.draws = stoi(lines[7]);
				clubs[GetLength(clubs)] = club;
				count = 0;
			}
		}
		file.close();
	}
}

void SortFile(FClub clubs[]) {
	fstream file;
	file.open(DIR, ios::out);
	file.clear();
	AddInFile(clubs);
	file.close();
}

string FillGaps(char a[]) {
	string s = "";
	for (int i = 0; i < strlen(a); i++)
	{
		if (a[i] == ' ')
		{
			s += '_';
		}
		else s += a[i];
	}
	return s;
}

void DisplaySubMenu(FClub clubs[]) {
	int option;
	string opt = "";
	do {
		do {
			Reset();
			cout << "Choose option:\n" <<
				"1 - Show the club with the most wins\n" <<
				"2 - Show the clubs with the least tabulated players\n" <<
				"3 - Show clubs with wins more than 0, sorted by name\n" <<
				"4 - Search club by name and year\n" <<
				"5 - Back\n";
			getline(cin, opt);
		} while (isdigit(atoi(opt.c_str())));
		option = atoi(opt.c_str());
		switch (option)
		{
		case 1:
			GetClubWithMostWins(clubs);
			break;
		case 2:
			GetClubsWithLeastPlayers(clubs);
			break;
		case 3:
			ShowClubsWithWins(clubs);
			break;
		case 4:
			SearchClubs(clubs);
			break;
		case 5:
			return;
		default:
			cout << "Please enter valid number\n";
			break;
		}
		Delay();
		cout << "\nPress any button to continue\n";
		_getch();
		Reset();
	} while (true);
}

void ShowClubsWithWins(FClub clubs[]) {
	FClub winners[MAX_CLUBS];
	for (int i = 0; i < GetLength(clubs); i++)
	{
		if (clubs[i].wins > 0)
		{
			winners[GetLength(winners)] = clubs[i];
		}
	}
	if (CheckClubs(winners))
	{
		bool f;
		for (int i = 0; i < GetLength(winners) - 1; i++)
		{
			f = false;
			for (int j = 0; j < GetLength(winners) - i - 1; j++)
			{
				if (strcmp(winners[j].cName, winners[j + 1].cName) == 1)
				{
					FClub temp = winners[j];
					winners[j] = winners[j + 1];
					winners[j + 1] = temp;
					f = true;
				}
			}
			if (!f)break;
		}
		ShowAllClubs(winners);
	}
	else cout << "There aren't clubs with wins more than 0\n";
}

void SearchClubs(FClub clubs[]) {
	FClub matches[MAX_CLUBS];
	string opt = "";
	char name[50];
	int option, year;
	do {
		do {
			Reset();
			cout << "Choose how do you want to search:\n" <<
				"1 - By name\n" <<
				"2 - By year\n" <<
				"3 - By name and year\n" <<
				"4 - Back\n";
			getline(cin, opt);
		} while (isdigit(atoi(opt.c_str())));
		option = atoi(opt.c_str());
		switch (option)
		{
		case 1:
			cout << "Type the name of the club:" << endl;
			cin.getline(name, 50);
			for (int i = 0; i < GetLength(clubs); i++)
			{
				if (!strcmp(name, clubs[i].cName))
				{
					matches[GetLength(matches)] = clubs[i];
				}
			}
			if (CheckClubs(matches))
			{
				ShowAllClubs(matches);
			}
			else cout << "There aren't clubs with that name\n";
			break;
		case 2:
			cout << "Enter the year of the club:" << endl;
			cin >> year;
			for (int i = 0; i < GetLength(clubs); i++)
			{
				if (year == clubs[i].year)
				{
					matches[GetLength(matches)] = clubs[i];
				}
			}
			if (CheckClubs(matches))
			{
				ShowAllClubs(matches);
			}
			else cout << "There aren't clubs created at that year\n";
			break;
		case 3:
			cout << "Type name and year\n";
			cin.getline(name, 50) >> year;
			for (int i = 0; i < GetLength(clubs); i++)
			{
				if (!strcmp(name, clubs[i].cName) && year == clubs[i].year)
				{
					matches[GetLength(matches)] = clubs[i];
				}
			}
			if (CheckClubs(matches))
			{
				ShowAllClubs(matches);
			}
			else cout << "There aren't clubs with that name created at that year\n";
			break;
		case 4:
			return;
		default:
			cout << "Please enter valid number\n";
			break;
		}
		Delay();
		cout << "\nPress any button to continue\n";
		_getch();
		Reset();
	} while (true);
}

void Tournament(FClub clubs[]) {
	fstream file;
	string opt = "", c1, c2;
	int option, result, index1, index2;
	bool f1 = false, f2 = f1;
	do {
		do {
			cout << "Choose:\n" <<
				"1 - Team vs Team\n" <<
				"2 - All vs All\n" <<
				"3 - Show Leaderboard\n" <<
				"4 - Back\n";
			getline(cin, opt);
		} while (isdigit(atoi(opt.c_str())));
		option = atoi(opt.c_str());
		switch (option) {
		case 1:
			cout << "Type any 2 club names you choose\n";
			cout << endl << "Club 1:\n";
			getline(cin, c1);
			cout << endl << "Club 2:\n";
			getline(cin, c2);
			for (int i = 0; i < GetLength(clubs); i++)
			{
				if (c1 == clubs[i].cName && !f1)
				{
					index1 = i;
					f1 = true;
				}
				else if (c2 == clubs[i].cName && !f2)
				{
					index2 = i;
					f2 = true;
				}
				if (f1 && f2)break;
			}
			if (f1 && f2)
			{
				result = rand() % 3;
				if (result == 0)
				{
					clubs[index1].wins++;
					clubs[index2].losses++;
					cout << c1 << " won the match\n";
				}
				else if (result == 1)
				{
					clubs[index2].wins++;
					clubs[index1].losses++;
					cout << c2 << " won the match\n";
				}
				else
				{
					clubs[index2].draws++;
					clubs[index1].draws++;
					cout << "The match was a draw\n";
				}
				SortFile(clubs);
			}
			else
			{
				cout << "The clubs' names you entered are not valid\n";
			}
			break;
		case 2:
			for (int i = 0; i < GetLength(clubs); i++)
			{
				for (int j = 0; j < GetLength(clubs); j++)
				{
					if (clubs[i].registrationNumber != clubs[j].registrationNumber)
					{
						result = rand() % 3;
						if (result == 0)
						{
							clubs[i].wins++;
							clubs[j].losses++;
						}
						else if (result == 1)
						{
							clubs[j].wins++;
							clubs[i].losses++;
						}
						else {
							clubs[i].draws++;
							clubs[j].draws++;
						}
					}
				}
			}
			SortFile(clubs);
			break;
		case 3:
			ShowLeaderboard(clubs);
			break;
		case 4:
			return;
		default:
			cout << "Please enter valid number\n";
			Delay();
			Reset();
			continue;
		}
		Delay();
		cout << "\nPress any button to continue\n";
		_getch();
		Reset();
	} while (true);
}

void ShowLeaderboard(FClub clubs[]) {
	FClub* copy = clubs;
	for (int i = 0; i < GetLength(copy) - 1; i++)
	{
		for (int j = 0; j < GetLength(copy) - i - 1; j++)
		{
			if (copy[j].wins * 3 + copy[j].draws < copy[j + 1].wins * 3 + copy[j + 1].draws)
			{
				FClub temp = copy[j];
				copy[j] = copy[j + 1];
				copy[j + 1] = temp;
			}
			else if (copy[j].wins * 3 + copy[j].draws == copy[j + 1].wins * 3 + copy[j + 1].draws && copy[j].losses > copy[j + 1].losses)
			{
				FClub temp = copy[j];
				copy[j] = copy[j + 1];
				copy[j + 1] = temp;
			}
		}
	}
	for (int i = 0; i < GetLength(copy); i++)
	{
		if (i == 0)
			cout << "FIRST - " << copy[i].cName << setw(13) << "points: " << copy[i].wins * 3 + copy[i].draws << endl;
		else if (i == 1)
			cout << "SECOND - " << copy[i].cName << setw(13) << "points: " << copy[i].wins * 3 + copy[i].draws << endl;
		else if (i == 2)
			cout << "THIRD - " << copy[i].cName << setw(13) << "points: " << copy[i].wins * 3 + copy[i].draws << endl;
		else cout << copy[i].cName << setw(13) << "points: " << copy[i].wins * 3 + copy[i].draws << endl;
	}
}

void Delay() {
	for (int i = 0; i < INT_MAX / 4; i++);
}

void Reset() {
	system("CLS");
	cout << flush;
}