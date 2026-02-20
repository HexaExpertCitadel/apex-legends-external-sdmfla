#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

struct Task
{
    string title;
    bool done;
};

void printTasks(const vector<Task>& tasks)
{
    cout << "\n=== TASK LIST ===\n";
    for (size_t i = 0; i < tasks.size(); i++)
    {
        cout << i + 1 << ". [" << (tasks[i].done ? "x" : " ") << "] "
             << tasks[i].title << endl;
    }
}

void addTask(vector<Task>& tasks)
{
    cout << "Enter task: ";
    string title;
    getline(cin, title);

    tasks.push_back({title, false});
}

void toggleTask(vector<Task>& tasks)
{
    int index;
    cout << "Task number: ";
    cin >> index;
    cin.ignore();

    if (index > 0 && index <= tasks.size())
        tasks[index - 1].done = !tasks[index - 1].done;
}

void deleteTask(vector<Task>& tasks)
{
    int index;
    cout << "Delete number: ";
    cin >> index;
    cin.ignore();

    if (index > 0 && index <= tasks.size())
        tasks.erase(tasks.begin() + index - 1);
}

void saveTasks(const vector<Task>& tasks)
{
    ofstream file("tasks.txt");
    for (auto& t : tasks)
        file << t.done << "|" << t.title << endl;
}

void loadTasks(vector<Task>& tasks)
{
    ifstream file("tasks.txt");
    if (!file) return;

    tasks.clear();
    string line;

    while (getline(file, line))
    {
        bool done = line[0] == '1';
        string title = line.substr(2);
        tasks.push_back({title, done});
    }
}

int main()
{
    vector<Task> tasks;
    loadTasks(tasks);

    while (true)
    {
        cout << "\n1 Add\n2 Toggle\n3 Delete\n4 Show\n5 Exit\n> ";
        int cmd;
        cin >> cmd;
        cin.ignore();

        switch (cmd)
        {
            case 1: addTask(tasks); break;
            case 2: toggleTask(tasks); break;
            case 3: deleteTask(tasks); break;
            case 4: printTasks(tasks); break;
            case 5: saveTasks(tasks); return 0;
        }
    }
}
