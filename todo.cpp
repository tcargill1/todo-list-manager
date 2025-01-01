#include "todo.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>

// Task class implementation
Task::Task(const std::string& task) : task(task) {
    std::cout << "task object created" << std::endl;
}

// Destructor
Task::~Task() {
    std::cout << "task object destroyed" << std::endl;
}

// Get task description
std::string Task::get_task() const {
    return task;
}

// Regular task class implmentation
RegularTask::RegularTask(const std::string& task) : Task(task) {
    std::cout << "regular task object created" << std::endl;
}

// Destructor
RegularTask::~RegularTask() {
    std::cout << "regular task object destroyed" << std::endl;
}

// Display task description for regular task
void RegularTask::display_task() const {
    std::cout << "Regular task: " << get_task() << std::endl;
}

// Urgent task class implementation
UrgentTask::UrgentTask(const std::string& task) : Task(task) {
    std::cout << "urgent task object created" << std::endl;
}

// Destructor
UrgentTask::~UrgentTask() {
    std::cout << "urgent task object destroyed" << std::endl;
}

// Display task description for urgent task
void UrgentTask::display_task() const {
    std::cout << "Urgent task: " << get_task() << std::endl;
}

// SharedToDo class implementation
SharedToDo::SharedToDo() {
    std::cout << std::endl << "shared todo object created" << std::endl;
}

// Destructor
SharedToDo::~SharedToDo() {
    std::cout << "shared todo object destroyed" << std::endl;
}

// Add user to the shared todo list
void SharedToDo::add_user(const std::string& user) {
    user_tasks.emplace(user, std::make_unique<Todo>());
}

// Remove user from the shared todo list
void SharedToDo::remove_user(const std::string& user) {
    user_tasks.erase(user);
}

// Add task to a specific user on shared todo list
void SharedToDo::add_task(const std::string& user, std::unique_ptr<Task> task) {
    // Checks if user exists in the map before adding task to user's todo list
    if (user_tasks.find(user) == user_tasks.end()) {
        std::cout << "User not found." << std::endl;
        return;
    }
    user_tasks[user] -> add_task(std::move(task));
}

// Remove task from a specific user on shared todo list
void SharedToDo::remove_task(const std::string& user, std::unique_ptr<Task> task) {
    // Checks if user exists in the map before removing task from user's todo list
    if (user_tasks.find(user) == user_tasks.end()) {
        std::cout << "User not found." << std::endl;
        return;
    }
    // Removes task based on string description
    std::string task_str = task->get_task();
    user_tasks[user] -> remove_task(task_str);
}

// View all tasks for all users on shared todo list
void SharedToDo::view_all_tasks() const {
    // Iterates through all users and prints their tasks
    for (const auto& user : user_tasks) {
        std::cout << "User: " << user.first << std::endl;
        user.second -> print_tasks();
    }
}

// View all tasks for a specific user on shared todo list
void SharedToDo::view_user_tasks(const std::string& user) const {
    // Checks if user exists in the map before printing user's tasks
    if (user_tasks.find(user) == user_tasks.end()) {
        std::cout << "User not found." << std::endl;
        return;
    }  
    user_tasks.at(user) -> print_tasks();      
}

// Clear all tasks for a specific user on shared todo list
void SharedToDo::clear_user_tasks(const std::string& user) {
    // Checks if user exists in the map before printing user's tasks
    if (user_tasks.find(user) == user_tasks.end()) {
        std::cout << "User not found." << std::endl;
        return;
    }
    user_tasks.at(user) -> clear_tasks();
}

// Clear all tasks for all users on shared todo list
void SharedToDo::clear_all_tasks() {
    user_tasks.clear();
}

// Todo class implementation
Todo::Todo() {
    std::cout << std::endl << "todo object created" << std::endl;
}
// Destructor
Todo::~Todo() {
    std::cout << "todo object destroyed" << std::endl;
}

// Add task object to vector
void Todo::add_task(std::unique_ptr<Task> task) {
    tasks.push_back(std::move(task));
}

// Remove task object from vector based on task description
void Todo::remove_task(std::string& task) {
    // Iterates through all tasks and removes task based on string description
    for (int i = 0; i < tasks.size(); i++) {
        if (tasks[i]->get_task() == task) {
            tasks.erase(tasks.begin() + i);
            return;
        }
    }
    std::cout << "Task not found." << std::endl;
}

// Remove task object from vector based on index
void Todo::remove_task_index(int index) {
    // Check if index is within valid range to remove task
    if (index < 0 || index >= tasks.size()) {
        std::cout << "Invalid index." << std::endl;
        return;
    }

    tasks.erase(tasks.begin() + index);
}

// Print all tasks in vector
void Todo::print_tasks() const {
    for (int i = 0; i < tasks.size(); i++) {
        std::cout << i + 1 << ": ";
        tasks[i] -> display_task();
    }
}

// Clear all tasks in vector
void Todo::clear_tasks() {
    tasks.clear();
}

// Save tasks to file
void Todo::save_tasks(const std::string& file_name) {
    // Open file for saving tasks
    std::ofstream file(file_name);

    // Check if file is open before saving tasks
    if (!file.is_open()) {
        std::cerr << "Error opening file for saving." << std::endl;
        return;
    }

    // Save tasks to file based on task type
    for (const auto& task : tasks) {
        if (dynamic_cast<RegularTask*>(task.get())) {
            file << "Regular " << task->get_task() << std::endl;
        } else if (dynamic_cast<UrgentTask*>(task.get())) {
            file << "Priority " << task->get_task() << std::endl;
        }
    }

    // Save tasks to file and print message
    file.close();
    std::cout << "Tasks saved to file: " << file_name << std::endl;
}

void Todo::load_tasks(const std::string& file_name) {
    // Open file for loading tasks
    std::ifstream file(file_name);
    // Check if file is open before loading tasks
    if (!file.is_open()) {
        std::cerr << "Error opening file for loading." << std::endl;
        return;
    }

    tasks.clear(); // Clear existing tasks before loading new ones

    // Load tasks from file based on task type
    std::string line;
    while (std::getline(file, line)) {
        // Parse line into task type and description
        std::istringstream iss(line);
        std::string type, task_description;
        iss >> type; // Read the type identifier
        std::getline(iss, task_description); // Read the task description

        // Create task object based on type and add to vector
        if (type == "Regular") {
            tasks.push_back(std::make_unique<RegularTask>(task_description));
        } else if (type == "Urgent") {
            tasks.push_back(std::make_unique<UrgentTask>(task_description));
        } else {
            std::cerr << "Unknown task type in file: " << type << std::endl;
        }
    }

    // Close file and print message
    file.close();
    std::cout << "Tasks loaded from file: " << file_name << std::endl;
}