#pragma once

#include <iostream>
#include <string>

using namespace std;

class Task {
protected:
    int id;
    int priority;
    string name;

public:
    Task(int id, int priority, const string& name)
        : id(id), priority(priority), name(name) {}

    virtual ~Task() = default;

    int getID() const {
        return id;
    }

    int getPriority() const {
        return priority;
    }

    virtual void execute() const = 0;
};


class CalculationTask : public Task {
public:
    CalculationTask(int id, int priority, const string& name)
        : Task(id, priority, name) {}

    void execute() const override {
        cout << "Executing Calculation Task: "
             << name << endl;
    }
};


class ReportTask : public Task {
public:
    ReportTask(int id, int priority, const string& name)
        : Task(id, priority, name) {}

    void execute() const override {
        cout << "Executing Report Task: "
             << name << endl;
    }
};