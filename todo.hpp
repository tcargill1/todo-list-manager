#ifndef TODO_HPP
#define TODO_HPP

#include <vector>
#include <string>
#include <set>
#include <unordered_map>
#include <memory>

// Task class for regular and urgent tasks
class Task {
    private:
        // Task description
        std::string task;
    public:
        // Constructor and destructor
        Task(const std::string& task);
        virtual ~Task();

        // Get task description
        std::string get_task() const;
        // Display task description (virtual function for polymorphism)
        virtual void display_task() const = 0;
};

// Regular Task class (inherits from Task)
class RegularTask : public Task {
    public:
        // Constructor and destructor
        RegularTask(const std::string& task);
        ~RegularTask();

        // Display task description (override virtual function)
        void display_task() const override;
};


// Urgent Task class (inherits from task)
class UrgentTask : public Task {
    public:
        // Constructor and destructor
        UrgentTask(const std::string& task);
        ~UrgentTask();
        // Display task description (override virtual function)
        void display_task() const override;
};

// Todo class to manaage individual tasks
class Todo {
    private:
        // Vector to store tasks as unique pointers
        std::vector<std::unique_ptr<Task>> tasks;
    public: 
        // Constructor and destructor
        Todo();

        ~Todo();

        // Add task object to vector
        void add_task(std::unique_ptr<Task> task);

        // Remove task object from vector based on task description
        void remove_task(std::string& task);

        // Remove task object from vector based on index
        void remove_task_index(int index);

        // Print all tasks in vector
        void print_tasks() const;

        // Clear all tasks in vector
        void clear_tasks();

        // Save tasks to file based on file name
        void save_tasks(const std::string& file_name);

        // Load tasks from file based on file name
        void load_tasks(const std::string& file_name);
};

// SharedToDo class to manage tasks for multiple users
class SharedToDo {
    private:
        // Dictionary to store user tasks as unique pointers from Todo class
        std::unordered_map<std::string, std::unique_ptr<Todo>> user_tasks;
    public:
        // Constructor and destructor
        SharedToDo();
        ~SharedToDo();

        // Add user to dictionary with empty Todo object as key-value pair
        void add_user(const std::string& user);
        
        // Remove user from dictionary based on key
        void remove_user(const std::string& user);

        // Add task to user based on user key and task object
        void add_task(const std::string& user, std::unique_ptr<Task> task);

        // Remove task from user based on user key and task object
        void remove_task(const std::string& user, std::unique_ptr<Task> task);
        
        // Print all tasks for all users
        void view_all_tasks() const;

        // Print all tasks for a specific user based on user key
        void view_user_tasks(const std::string& user) const;

        // Clear all tasks for a specific user based on user key
        void clear_user_tasks(const std::string& user);

        // Clear all tasks for all users
        void clear_all_tasks();
};

#endif // TODO_HPP