#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>
#include "printCalendar.h"
using namespace std;

// NODE
class TreeNode
{
	public:

    int data;
	vector <TreeNode*> child;
	TreeNode(int data)
    {
        this->data = data;
    }
	void addChild(int data)
	{
		TreeNode *t = new TreeNode(data);
		this->child.push_back(t);
	}
};

// TREE
class NAryTree
{
	public:
    TreeNode *root;
	NAryTree()
	{
		this->root = nullptr;
	}
	void printPreorder(TreeNode *node)
	{
		if (node == nullptr)
		{
			return;
		}
		int i = 0;
		TreeNode *temp = nullptr;
		cout << "  " << node->data;
		// iterating the child of given node
		while (i < node->child.size())
		{
			temp = node->child.at(i);
			this->printPreorder(temp);
			i++;
		}
	}
};

int getIndex(vector<int> v, int K)
{
    auto it = find(v.begin(), v.end(), K);

    // If element was found
    if (it != v.end())
    {

        // calculating the index
        // of K
        int index = it - v.begin();
        return index;
    }
    else {
        // If the element is not
        // present in the vector
        return -1;
    }
}


// function for printing the elements in a list
void showlist(list<int> g)
{
    list<int>::iterator it;
    for (it = g.begin(); it != g.end(); ++it)
        cout << '\t' << *it;
    cout << '\n';
}

void printVectors(vector<int> k) {
    for(int i : k)
        cout << i << endl;
}

// Function to print the calendar
#include<bits/stdc++.h>
#include "printCalendar.h"

using namespace std;

/*A Function that returns the index of the day
of the date- day/month/year

Index	 Day
0		 Sunday
1		 Monday
2		 Tuesday
3		 Wednesday
4		 Thursday
5		 Friday
6		 Saturday
*/
int dayNumber(int day, int month, int year)
{

	static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
	year -= month < 3;

	return ( year + year/4 - year/100 + year/400 + t[month-1] + day) % 7;
}


/* Month Number Index
0		January
1		February
2		March
3		April
4		May
5		June
6		July
7		August
8		September
9		October
10		November
11		December    */

string getMonthName(int monthNumber){
	string months[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

	return (months[monthNumber]);
}


// Return the number of days in a month
int numberOfDays (int monthNumber, int year){
	// January, March, May, July, October, December
	if (monthNumber == 0 || monthNumber == 2 || monthNumber == 4 || monthNumber == 6 || monthNumber == 7 || monthNumber == 9 || monthNumber == 11)
		return (31);

	// April, June, September, November
	if (monthNumber == 3 || monthNumber == 5 || monthNumber == 8 || monthNumber == 10)
		return (30);

	// February
	if (monthNumber == 1)
	{
		// if leap year
		if (year % 400 == 0 ||
				(year % 4 == 0 && year % 100 != 0))
			return (29);
		else
			return (28);
	}
	else cout<< "Invalid month";
	    return 0;
}

// Function to print the calendar of the given year
void printCalendar(int year){

	int monthNumber, days, i;

	cout << "Enter year: ";
	cin >> year;
	cout << "\n";

	cout << "Enter month number (1-12): ";
	cin >> monthNumber;
	cout << "\n";

	cout << "	Year: " << year << "\n";  //print year

	monthNumber -= 1; //adjust month number

	days = numberOfDays (monthNumber, year);

	// Print the month name
	cout << "------------"<<getMonthName (monthNumber).c_str() << "------------\n";
	cout << "number of days: "<< numberOfDays(monthNumber, year)<< "\n";

		// Print the columns
	cout << " Sun Mon Tue Wed Thu Fri Sat\n";

    int current = dayNumber (1, monthNumber+1, year);   // Index of the day from 0 to 6

	// Print appropriate spaces
	for (i = 0; i < current; i++) cout << "     ";     //spacing still needs to be fixed

	for (int j = 1; j <= days; j++){
		cout << " " << j << "  ";

		if (++i > 6){
			i = 0;
			cout << "\n";
			}
	}

	if (i)
	cout << "\n";

	current = i;

	return;
}

int main()
{
    cout << "\t\tWelcome to your\n\tMonthly Financial Tracker\n";
    int year;
    printCalendar(year);

    string menus[] = {
        "Add",
        "Exit"
    };

    // DEFINE TREE
    NAryTree *tree = new NAryTree();

    int tmp, tmp_month, tmp_week, tmp_day, tmp_expense, coba;
    bool exited = false, root_data_exist = false;
    vector<int> week_vector;
    vector<vector<int>> day_vector = {{}, {}, {}, {}};

    while(!exited) {
        // Print the menus
        //cout << "\n ===> FINANCIAL TRACKER" << endl;
        for(int i = 0; i < 2; i++) {
            cout << i+1 << ") " << menus[i] << endl;
        }
        cout << ">>> ";
        cin >> tmp;

        if(tmp == 1) {
            // ADD
            // MONTHS
            // only run when first data entered (which is tmp_month)
            if(!root_data_exist) {
                cout << "INSERT MONTH (1-12) >>> ";
                cin >> tmp_month;
                // DEFINE ROOT
                tree->root = new TreeNode(tmp_month);
                root_data_exist = true;
            }


            //Input date for week and day
            cout << "INSET DATE >>> ";
            cin >> coba;
            tmp_week=((coba-1)/7)+1;
            tmp_day=((coba-1)%7)+1;

            // WEEK
            // check whether week has been entered before
            int week_index = getIndex(week_vector, tmp_week);
            if(week_index == -1) {
                // week element not exist
                // create #1 sub-tree from root
                tree->root->addChild(tmp_week);
                // store data in vector for tracking index later
                week_vector.push_back(tmp_week);
                // update week_index
                week_index = week_vector.size()-1;
            }

            // DAY
            // check whether week has been entered before
            int day_index = getIndex(day_vector.at(week_index), tmp_day);
            if(day_index == -1) {
                // day element not exist
                // create #2 sub-tree from week
                tree->root->child.at(week_index)->addChild(tmp_day);
                // store data in vector for tracking index later
                day_vector.at(week_index).push_back(tmp_day);
                day_index = day_vector.at(week_index).size()-1;
            }

            // EXPENSES
            cout << "INSERT YOUR EXPENSE ON THIS DAY >>> ";
            cin >> tmp_expense;
            // create #3 sub-tree from day
            tree->root->child.at(week_index)->child.at(day_index)->addChild(tmp_expense);



            // [CHECKING METHODS] print preoder of the tree
            cout << "\n  Preorder : \n";
            tree->printPreorder(tree->root);
            cout << "\n\n";

        } else if(tmp == 2) {
            // EXIT
            exited = true;
        } else {
            cout << "Invalid Input!" << endl;
        }
    }

    return 0;
}
