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

    int tmp, tmp_month, tmp_week, tmp_day, tmp_expense;
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


            // WEEK
            cout << "INSERT WEEK (1-4) >>> ";
            cin >> tmp_week;
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
            cout << "INSERT DAY (1-7) >>> ";
            cin >> tmp_day;
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
