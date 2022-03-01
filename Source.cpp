#include "BinarySearchTree.h"
#include <string>


using namespace std;

int main() {
	int loop = 1;
	BinarySearchTree* tree = new BinarySearchTree();

	do {
		int input = 0;
		cout << "What would you like to do?" << endl << "1. Insert a Node" << endl << "2. Delete Node" << endl
			<< "3. Find a Node" << endl << "4. Report all Nodes" << endl << "5. Exit" << endl;
		cin >> input;
		if (input <= 5 || input >= 1) {
			if (input == 1) {
				string name;
				int id;
				int age;

				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Enter Employee name:";
				getline(cin, name);
				cout << endl;

				cout << "Enter ID: ";
				cin >> id;
				cout << endl;

				cout << "Enter age: ";
				cin >> age;
				cout << endl;

				Employee temp = Employee(id, age, name);

				tree->insert(temp);
			}
			else if (input == 2) {
				int removal;
				cout << "Input ID of the employee to be removed: ";
				cin >> removal;

				tree->remove(removal);
			}
			else if (input == 3) {
				int search;
				cout << "What is the ID of the employee to find: ";
				cin >> search;

				tree->find(search);
			}
			else if (input == 4) {
				tree->report();
			}
			else {
				loop = 0;
			}
		}
	} while (loop == 1);
	return 0;
}