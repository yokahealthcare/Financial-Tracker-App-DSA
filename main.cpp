#include <iostream>
#include <list>
#include <vector>
using namespace std;

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


// function for printing the elements in a list
void showlist(list<int> g)
{
    list<int>::iterator it;
    for (it = g.begin(); it != g.end(); ++it)
        cout << '\t' << *it;
    cout << '\n';
}

int main()
{
    int tmp;
    bool exited = false;
    string menus[] = {
        "Add",
        "Exit"
    };

    string months[] = {
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
        "December",
    };

    string week[] = {
        "week 1",
        "week 2",
        "week 3",
        "week 4"
    };

    list<int> expenses;
    NAryTree *tree = new NAryTree();

    vector<int> week_component_tracker;
    vector<vector<int>> day_component_tracker = {{}, {}, {}, {}};
    bool first_time = true;


    while(!exited) {
        cout << "\t\t\t#FINANCIAL TRACKER#" << endl;
        cout << "\t\t\t===================" << endl;
        cout << "\t\t\tCreated by GROUP 3" << endl;
        cout << "MENU" << endl;
        cout << "----" << endl;
        for(int i = 0; i < 2; i++) {
            cout << i+1 << ") " << menus[i] << endl;
        }

        cout << "> ";
        cin >> tmp;
        if(tmp == 1) {
            int tmp_month, tmp_week, tmp_day, tmp_expense;
            if(first_time) {
                // Print months
                cout << "MONTHS" << endl;
                for(int i = 0; i < 12; i++) {
                    cout << i+1 << ") " << months[i] << endl;
                }

                cout << "Pick a Month : ";
                cin >> tmp_month;
            }

            cout << "\nWEEK" << endl;
            for(int i = 0; i < 4; i++) {
                cout << i+1 << ") " << week[i] << endl;
            }

            cout << "Pick a Week : ";
            cin >> tmp_week;

            cout << "\nDAY" << endl;
            cout << "Pick a Day (1 to 7) : ";
            cin >> tmp_day;

            cout << "\nEXPENSES" << endl;
            cout << "$ ";
            cin >> tmp_expense;

            // Only runned when first time run the program
            if(first_time) {
                tree->root = new TreeNode(tmp_month);
                first_time = false;
            }


            // WEEK
            int selected_week_index;
            if(week_component_tracker.size() == 0) {
                // if first time
                tree->root->addChild(tmp_week);
                week_component_tracker.push_back(tmp_week); // to track the index
                selected_week_index = 0;
            } else {
                for(int i = 0; i < week_component_tracker.size(); i++) {
                    // check if it already there
                    cout << "HERE!" << " i : " << i <<endl;
                    if(tree->root->child.at(i)->data == tmp_week) {
                        cout << "Already Here | WEEK" << endl;
                        selected_week_index = i;
                        break;
                    } else if(i == week_component_tracker.size()-1){ // running only on last iteration
                      tree->root->addChild(tmp_week);
                      week_component_tracker.push_back(tmp_week); // to track the index
                      selected_week_index = i;
                      break;
                    }
                }
            }

            // DAY
            int selected_day_index;
            if(day_component_tracker[selected_week_index].size() == 0) {
                // if first time
                tree->root->child.at(selected_week_index)->addChild(tmp_day);
                day_component_tracker[selected_week_index].push_back(tmp_day); // to track the index
                selected_day_index = 0;
            } else {
                for(int i = 0; i < day_component_tracker[selected_week_index].size(); i++) {
                    // check if it already there
                    cout << "HERE! | DAY" << " i : " << i <<endl;
                    if(tree->root->child.at(selected_week_index)->child.at(i)->data == tmp_day) {
                        cout << "Already Here | DAY" << endl;
                        selected_day_index = i;
                        break;
                    } else if(i == day_component_tracker[selected_week_index].size()-1){ // running only on last iteration
                      tree->root->child.at(selected_week_index)->addChild(tmp_day);
                      day_component_tracker[selected_week_index].push_back(tmp_day); // to track the index
                      selected_day_index = i;
                      break;
                    }
                }
            }

            // EXPENSES (can be multiple expenses in one day)
            tree->root->child.at(selected_week_index)->child.at(selected_day_index)->addChild(tmp_expense);
            selected_day_index = NULL;
            selected_week_index = NULL;

        } else if(tmp == 2) {
            return 0;
        }


        cout << "\n  Preorder : \n";
        // Print tree element
        tree->printPreorder(tree->root);

    }

    return 0;
}
