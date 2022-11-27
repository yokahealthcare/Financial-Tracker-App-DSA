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



// function for finding the Total, Min, Max, Avg spending
void MinMaxAvg(double data[], int size, double& min, double& max, double& avg)
{
    if(size<=0)
    return;

    min = data[0];
    max = 0;
    int count = 0;
    double sum = 0;
    int i;
    avg = 0;

    for (i=0; i < size; i++)
    {
		count++;
        sum += data[i];

        if ( data[i] > max)
        {
            max=data[i];
        }

        else if (data[i] < max)
        {
            min=data[i];
        }
    }
    avg = sum/(double)count;
    cout<< "Your TOTAL spending was: Rp." << sum << endl;
}





int main()
{
    cout << "# WELCOME! #" << endl;
    cout << "FINANCIAL TRACKER APP\n" << endl;

    // to print a calendar. Just for user references
    //printCalendar();

    string menus[] = {
        "View Calendar",
        "Add",
        "Exit"
    };

    // DEFINE TREE
    NAryTree *tree = new NAryTree();

    int tmp, tmp_month, tmp_week, tmp_day, tmp_expense, coba;
    bool exited = false, root_data_exist = false;
    vector<int> week_vector;
    vector<vector<int>> day_vector = {{}, {}, {}, {}};

    // PROGRAM START
    while(!exited) {
        for(int i = 0; i < 3; i++) {
            cout << i+1 << ") " << menus[i] << endl;
        }
        cout << ">>> ";
        cin >> tmp;

        if(tmp == 1) {
            cout << "\n";
            printCalendar();
            cout << "\n";
        } else if(tmp == 2) {
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

        } else if(tmp == 3) {
            // EXIT
            exited = true;
        } else {
            cout << "Invalid Input!" << endl;
        }
    }

    // calling function for finding the Total, Min, Max, Avg spending
    double min,max,avg;
    double data[]={1,2,3,4,5};                                        // Put money spendings here
    int sizeofdata = sizeof(data)/sizeof(data[0]);

    MinMaxAvg (data, sizeofdata, min, max, avg);

    cout<< "Your LOWEST spending was: Rp. " << min << endl;
    cout<< "Your HIGHEST spending was: Rp." << max << endl;
    cout<< "Your AVERAGE spending was: Rp." << avg << endl;


    return 0;
}
