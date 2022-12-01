#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>
#include "calendar.h"
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

//Linked List
class NodeList{
    public:
    int data;
    NodeList *link;
};

//function to insert to the linked list
NodeList *insertList(NodeList *head, int temp_exp){
    NodeList *temp = new NodeList();
    temp -> data = temp_exp;
    temp -> link = NULL;
    if(head != NULL){
        temp -> link = head;
    }
    head = temp;
    return head;
}
//print linked list
void PrintList(NodeList *head){
	cout << "list is: ";

	while(head != NULL){
		cout << head -> data << " ";
		head = head -> link;

	}
	cout << "\n";
}
//function to sum of the linked list
void sumList(NodeList *head){
    cout << "Total Spending \t\t: ";
    int sum = 0;
    while(head != NULL){
        sum += head -> data;
        head = head -> link;
    }
    cout << sum;
}

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

// function to convert get the elements in a list and return with array data type
void getList(NodeList *head, vector<int>& arrList)
{
    while(head != NULL) {
        arrList.push_back(head -> data);
        head = head -> link;
    }
}

void printVectors(vector<int> k) {
    for(int i : k)
        cout << i << endl;
}

// function for finding the Total, Min, Max, Avg spending
void MinMaxAvg(vector<int> data) {
  int size = data.size();

  if (size > 0) {
    int min = data[0];
    int max = 0;
    int sum = 0;
    double avg = 0;

    for (int i = 0; i < size; i++) {
      sum += data[i];

      if (data[i] > max) {
        max = data[i];
      }

      else if (data[i] < min) {
        min = data[i];
      }
    }
    avg = sum / size;
    cout << endl;
    cout << "LOWEST  spending was\t: " << min << endl;
    cout << "HIGHEST spending was\t: " << max << endl;
    cout << "AVERAGE spending is\t: " << avg << endl;
  } else {
    cout << "\nNo Data can Calculated!" << endl;
  }
}

int main()
{
    cout << "================================ WELCOME! ================================" << endl;
    cout << "=======================MONTHLY FINANCIAL TRACKER APP======================\n\n" << endl;
    cout << "This app tracks your spendings on each day of a choosen month.\n" << endl;
    cout << "Functionalities of this app:\n1) View Calendar -> view the monthly calendar of any month in any year" << endl;
    cout << "\t- You can check the dates and day of the week" << endl;
    cout << "2) Add -> Add spending to a date of the month\n\t- The spendings will be organized in a tree based on month, week, and day of week" << endl;
    cout << "\t- preorder or tree is given after input\n3) Summary -> View current summary\n\n" << endl;
    cout << "Input requirements:\n1) The program only accepts numbers as input\n\t- Month (1 to 12)\n\t- Expense (no symbols or currency attched)" << endl;
    cout << "2) This app tracks the spendings of 1 month, you can not jump between months" << endl;

    do {
      cout << "\nClick Enter to Start!";
    } while (cin.get () != '\n');

    string menus[] = {
        "View Calendar",
        "Add",
        "Summary",
        "Exit"
    };

    string month[] = {
        "January",
        "February",
        "March",
        "April",
        "May",
        "June",
        "July",
        "August",
        "September",
        "October",
        "November",
        "December"
    };

    // VARIABLE & CLASS INITIALIZATION
    // current date/time based on current system
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int currentYear = 1900 + ltm->tm_year;

    // DEFINE TREE
    NAryTree *tree = new NAryTree();

    // DEFINE LINKED LIST
    NodeList *head = NULL;

    // VARIABLES
    int tmp, tmp_month, tmp_week, tmp_day, tmp_expense, coba;
    bool exited = false, root_data_exist = false;
    vector<int> week_vector;
    vector<vector<int>> day_vector = {{}, {}, {}, {}};

    // PROGRAM START
    while(!exited) {
        cout << "\n";
        for(int i = 0; i < 4; i++) {
            cout << i+1 << ") " << menus[i] << endl;
        }
        cout << ">>> ";
        cin >> tmp;

        // add if temp is string invalid input and try again
        if(tmp == 1) {
            cout << "\n";
            printCalendar();
            cout << "\n";
        } else if(tmp == 2) {
            // ADD
            // MONTHS
            // only run when first data entered (which is tmp_month)
            if(!root_data_exist) {
                // LOOP UNTIL USER ENTER CORRECT INPUT OF MONTH
                while(true) {
                    cout << "INSERT MONTH (1-12) >>> ";
                    cin >> tmp_month;

                    // Insert if function so when user input more than 12 it prints invalid
                    if (tmp_month > 12 || tmp_month < 1) {
                        cout << "Invalid Input!" << endl << "Please try again" << endl << endl;
                    }
                    else
                        break;
                }

                // DEFINE ROOT
                tree->root = new TreeNode(tmp_month);
                root_data_exist = true;
            } else {
                // Print this word if program already on second iteration
                cout << "\nSELECTED MONTH : " << month[tmp_month-1] << endl;
            }


            //insert for loop that prints invalid when user inputs exceeding days of the month
            //insert currency function so user can input which currency they want

            while(true) {
                //Input date for week and day
                cout << "INSERT DATE >>> ";
                cin >> coba;

                if (tmp_month == 2) {
                    int limit = 28;

                    // run only for year of leap / kabisat
                    if(currentYear % 4 == 0)
                        limit = 29;

                    if (coba > limit || coba < 1)
                        cout << "Invalid Input!" << endl << "Please try again" << endl << endl;
                    else
                        break;
                }
                // for months that has maximum day of 31
                else if (tmp_month == 1 || tmp_month == 3 || tmp_month == 5 || tmp_month == 7 || tmp_month == 8 || tmp_month == 10 || tmp_month == 12) {
                    if (coba > 31 || coba < 1)
                        cout << "Invalid Input!" << endl << "Please try again" << endl << endl;
                    else
                        break;
                }
                // for months that has maximum day of 30
                else if (tmp_month == 4 || tmp_month == 6 || tmp_month == 9 || tmp_month == 11) {
                    if (coba > 30 || coba < 1)
                        cout << "Invalid Input!" << endl << "Please try again" << endl << endl;
                    else
                        break;
                }
            }

            // doing some calculation of date
            // decide what number of day on that week
            tmp_week=((coba-1)/7)+1;
            tmp_day=((coba-1)%7)+1;

            // TREE STORING
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

            // ADD EXPENSES TO LINKED LIST FOR FUTHER ANALYSIS
            head = insertList(head, tmp_expense);

            // create #3 sub-tree from day
            tree->root->child.at(week_index)->child.at(day_index)->addChild(tmp_expense);

            // [CHECKING METHODS] print preoder of the tree
            cout << "\n  Preorder : \n";
            tree->printPreorder(tree->root);
            cout << "\n\n";

        } else if(tmp == 3) {
            cout << "\nSUMMARY OF FINANCIAL TRACKER\n" << endl;
            sumList(head);
            // calling function for finding the Total, Min, Max, Avg spending
            vector<int> arrList;
            getList(head, arrList); // Put money spendings here
            MinMaxAvg(arrList);

        } else if(tmp == 4) {
            // EXIT
            char c;
	        cout << "\n\n!!!Confirm End Program!!!\nEnter 0 to confirm exit and 1 to cancel" << endl;
			cin >> c;
			if (toupper(c) == '0'){
		        cout << "\n\n\n\n\n\nThank you for using this financial tracker, See you again!" << endl;
		        exited = true;
			}

        } else {
            cout << "Invalid Input!" << endl;
            break;
        }
    }
    return 0;
}
