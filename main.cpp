#include <iostream>
#include "TaskManager.h"

using namespace std;

void menu() {
    cout << "\n========== TASK MANAGER ==========\n";
    cout << "1. Add Calculation Task\n";
    cout << "2. Add Report Task\n";
    cout << "3. Find Task\n";
    cout << "4. Remove Task\n";
    cout << "5. Execute Next Task\n";
    cout << "6. Undo Last Action\n";
    cout << "7. Show Execution Order\n";
    cout << "8. Add Dependency\n";
    cout << "9. Remove Dependency\n";
    cout << "10. Search Dependency\n";
    cout << "11. Print Dependency Tree\n";
    cout << "12. Show Tree Height\n";
    cout << "13. Check If Tree Is Balanced\n";
    cout << "0. Exit\n";
    cout << "==================================\n";
    cout << "Choice: ";
}


int main() {

    TaskManager manager;

    int choice;

    do {

        menu();
        cin >> choice;

        switch (choice) {

        case 1: {
            int id, priority;
            string name;

            cout << "Enter ID: ";
            cin >> id;

            cout << "Enter priority: ";
            cin >> priority;

            cout << "Enter name: ";
            cin.ignore();
            getline(cin, name);

            manager.addTask(
                new CalculationTask(id, priority, name)
            );

            cout << "Calculation task added.\n";

            break;
        }


        case 2: {
            int id, priority;
            string name;

            cout << "Enter ID: ";
            cin >> id;

            cout << "Enter priority: ";
            cin >> priority;

            cout << "Enter name: ";
            cin.ignore();
            getline(cin, name);

            manager.addTask(
                new ReportTask(id, priority, name)
            );

            cout << "Report task added.\n";

            break;
        }


        case 3: {
            int id;

            cout << "Enter task ID: ";
            cin >> id;

            Task* task = manager.findTask(id);

            if (task != nullptr) {
                cout << "Task found!\n";
                cout << "ID: " << task->getID() << endl;
                cout << "Priority: "
                     << task->getPriority() << endl;
            }
            else {
                cout << "Task not found.\n";
            }

            break;
        }


        case 4: {
            int id;

            cout << "Enter task ID: ";
            cin >> id;

            if (manager.removeTask(id))
                cout << "Task removed.\n";
            else
                cout << "Task not found.\n";

            break;
        }


        case 5: {

            cout << "Executing next task...\n";

            manager.executeNext();

            break;
        }


        case 6: {

            if (manager.undo())
                cout << "Last action undone.\n";
            else
                cout << "Nothing to undo.\n";

            break;
        }


        case 7: {

            vector<int> order =
                manager.getExecutionOrder();

            cout << "Execution order: ";

            for (int id : order)
                cout << id << " ";

            cout << endl;

            break;
        }


        case 8: {
            int id;

            cout << "Enter dependency ID: ";
            cin >> id;

            manager.getDependencyTree()
                   .insertDependency(id);

            cout << "Dependency added.\n";

            break;
        }


        case 9: {
            int id;

            cout << "Enter dependency ID: ";
            cin >> id;

            if (manager.getDependencyTree()
                       .removeDependency(id))
                cout << "Dependency removed.\n";
            else
                cout << "Dependency not found.\n";

            break;
        }


        case 10: {
            int id;

            cout << "Enter dependency ID: ";
            cin >> id;

            if (manager.getDependencyTree()
                       .dependencyExists(id))
                cout << "Dependency exists.\n";
            else
                cout << "Dependency not found.\n";

            break;
        }


        case 11: {

            cout << "Dependency tree: ";

            manager.getDependencyTree()
                   .printDependencies();

            break;
        }


        case 12: {

            cout << "Tree height: "
                 << manager.getDependencyTree()
                        .treeHeight()
                 << endl;

            break;
        }


        case 13: {

            if (manager.getDependencyTree()
                       .isBalanced())
                cout << "Tree is balanced.\n";
            else
                cout << "Tree is NOT balanced.\n";

            break;
        }


        case 0:
            cout << "Exiting...\n";
            break;


        default:
            cout << "Invalid choice.\n";
        }

    } while (choice != 0);


    return 0;
}