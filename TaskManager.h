#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <stack>

#include "./Task.h"
#include "./Dependancy.h"

using namespace std;


class TaskManager {
private:

    struct TaskComparator {
        bool operator()(const Task* a, const Task* b) const {
          
            if (a->getPriority() != b->getPriority())
                return a->getPriority() < b->getPriority();

            return a->getID() > b->getID();
        }
    };


    enum ActionType {
        ADD,
        REMOVE
    };


    struct Action {
        ActionType type;
        Task* task;
    };


    unordered_map<int, Task*> tasks;

    DependencyTree tree;

    stack<Action> history;


public:

    TaskManager() = default;


    ~TaskManager() {

        for (auto& pair : tasks) {
            delete pair.second;
        }

    }


    void addTask(Task* task) {

        if (task == nullptr)
            return;

        int id = task->getID();

        if (tasks.find(id) != tasks.end())
            return;

        tasks[id] = task;

        history.push({
            ADD,
            task
        });
    }


    Task* findTask(int id) {

        auto it = tasks.find(id);

        if (it == tasks.end())
            return nullptr;

        return it->second;
    }


    bool removeTask(int id) {

        auto it = tasks.find(id);

        if (it == tasks.end())
            return false;

        Task* task = it->second;

        tasks.erase(it);

        history.push({
            REMOVE,
            task
        });

        return true;
    }

    void executeNext() {
        if (tasks.empty())
            return;


        priority_queue<Task*,vector<Task*>,TaskComparator> pq;


        for (auto& pair : tasks) {
            pq.push(pair.second);
        }


        Task* task = pq.top();

        task->execute();

        tasks.erase(task->getID());

        delete task;
    }

    vector<int> getExecutionOrder() const {

        priority_queue<Task*,vector<Task*>,TaskComparator> pq;
        vector<int> result;

        for (const auto& pair : tasks) {
            pq.push(pair.second);
        }
        
        while (!pq.empty()) {

            Task* task = pq.top();

            pq.pop();

            result.push_back(task->getID());
        }

        return result;
    }

    bool undo() {

        if (history.empty())
            return false;


        Action action = history.top();
        history.pop();

        if (action.type == ADD) {
            auto it = tasks.find(action.task->getID());
            if (it != tasks.end()) {
                tasks.erase(it);
                delete action.task;
            }
        }
        else {
            int id = action.task->getID();
            if (tasks.find(id) == tasks.end()) {
                tasks[id] = action.task;
            }
        }
        return true;
    }

    int countTasks() const {
        return static_cast<int>(tasks.size());
    }

    DependencyTree& getDependencyTree() {
        return tree;
    }
};