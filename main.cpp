#include "todo.hpp"
#include <iostream>

int main() {
    // Create shared todo list
	SharedToDo shared_todo;

    // Add users
    shared_todo.add_user("Alice");
    shared_todo.add_user("Bob");

    // Add tasks for Alice
    shared_todo.add_task("Alice", std::make_unique<RegularTask>("Buy groceries."));
    shared_todo.add_task("Alice", std::make_unique<UrgentTask>("Submit assignment."));

    // Add tasks for Bob
    shared_todo.add_task("Bob", std::make_unique<RegularTask>("Walk the dog."));
    shared_todo.add_task("Bob", std::make_unique<UrgentTask>("Prepare for meeting."));

    // View tasks for all users
    std::cout << "\nAll Users' Tasks:\n";
    shared_todo.view_all_tasks();

    // View tasks for a specific user
    std::cout << "\nAlice's Tasks:\n";
    shared_todo.view_user_tasks("Alice");

    // Clear tasks for Alice
    shared_todo.clear_user_tasks("Alice");
    std::cout << "\nAlice's Tasks After Clearing:\n";
    shared_todo.view_user_tasks("Alice");

    // Remove user Bob
    shared_todo.remove_user("Bob");
    std::cout << "\nAll Users' Tasks After Removing Bob:\n";
    shared_todo.view_all_tasks();

    return 0;
}