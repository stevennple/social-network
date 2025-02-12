#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include "network.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " users.txt posts.txt\n";
        return 1;
    }

    Network network;

    // Read user data from the first file argument
    if (network.readUsers(argv[1]) == -1) {
        std::cerr << "Error: Failed to read users from file " << argv[1] << '\n';
        return 1;
    }

    // Read post data from the second file argument
    if (network.readPosts(argv[2]) == -1) {
        std::cerr << "Error: Failed to read posts from file " << argv[2] << '\n';
        return 1;
    }

    // Infinite loop to display the menu options till the user exits
    while (true) {
        int choice; 

        std::cout << "\nWelcome to the Social Media Network!\n";
        std::cout << "1. Add a user\n";
        std::cout << "2. Add friend connection\n";
        std::cout << "3. Delete friend connection\n";
        std::cout << "4. Write users to file\n";
        std::cout << "5. View recent posts for a user\n";
        std::cout << "6. Exit the program\n";
        std::cout << "Please select and option from the menu above:\n";
        std::cin >> choice; 

        // Option 1: Add a user
        if (choice == 1) {
            std::string firstName, lastName, name;
            int year, zip; 

            // User inputs their info in one the same line
            std::cout << '\n' << "Enter the user's first name, last name, year of birth, and zip code (each separated by a space):\n";;
            std::cout << "ex: John Doe 1990 12345\n";
            std::cin >> firstName >> lastName >> year >> zip;

            // Concatenate the first name and last name to form the full name
            name = firstName + " " + lastName;

            // Add the user to the network
            network.addUser(name, year, zip);

            // Success message for adding the user
            std::cout << '\n' << name << " has been added to the network\n";
        }

        // Option 2: Add friend connection
        else if (choice == 2) {
            std::string firstName1, lastName1, firstName2, lastName2;

            // Prompt the user to enter the names of the two users
            std::cout << "\nEnter the 1st user's first name and last name:\n";
            std::cout << "ex: John Doe\n";
            std::cin >> firstName1 >> lastName1;         

            std::cout << "\nEnter the 2nd user's first name and last name:\n";
            std::cin >> firstName2 >> lastName2;

            std::string name1 = firstName1 + " " + lastName1;
            std::string name2 = firstName2 + " " + lastName2;
            
            // Add a friend connection between the two users
            if (network.addConnection(name1, name2) == -1) {
                std::cout << "\nError: One or both users do not exist, or they are already friends\n";
            }
            else {
                // Print a success message if the friend connection is added successfully
                std::cout << '\n' << name1 << " and " << name2 << " are added successfully\n";
            }
        }

        // Option 3: Delete friend connection
        else if (choice == 3) {
            std::string firstName1, lastName1, firstName2, lastName2;

            // Prompt the user to enter the names of the two users
            std::cout << "\nEnter the 1st user's first name and last name:\n";
            std::cout << "ex: John Doe\n";
            std::cin >> firstName1 >> lastName1;         

            std::cout << "\nEnter the 2nd user's first name and last name:\n";
            std::cin >> firstName2 >> lastName2;

            std::string name1 = firstName1 + " " + lastName1;
            std::string name2 = firstName2 + " " + lastName2;
            
            // Delete a friend connection between the two users
            if (network.deleteConnection(name1, name2) == -1) {
                std::cout << "\nError: One or both users do not exist, or they are not friends\n";
            }
            else {
                // Print a success message if the friend connection is deleted successfully
                std::cout << '\n' << name1 << " and " << name2 << " are deleted successfully\n";
            }
        }
        
        // Option 4: Write users to file
        else if (choice == 4) {
            std::string fname;

            // Prompt user to enter the file name that they'd like to write to
            std::cout << "\nEnter the file name to write the user data to: ";
            std::cout << "ex: users_new.txt\n";
            std::cin >> fname;

            network.writeUsers(fname.c_str());
            std::cout << network.numUsers() << " number of users written to " << fname << '\n';
        }
        
        // Option 5: View recent posts for a user
        else if (choice == 5) {
            std::string firstName, lastName;
            int howMany;

            // Prompt the user to enter the name of the user
            std::cout << "\nEnter the user's first name and last name:\n";
            std::cout << "ex: John Doe\n";
            std::cin >> firstName >> lastName;

            // Prompt the user to enter the number of recent posts to display
            std::cout << "\nEnter the number of posts to display:\n";
            std::cin >> howMany;

            std::string name = firstName + " " + lastName;
            int userId = network.getId(name);

            if (userId == -1) {
                std::cout << "\nError: User " << name << " does not exist\n";
            }
            else {
                // Display the user's most recent posts
                std::string posts = network.getPostsString(userId, howMany, false);
                std::cout << "\nRecent posts for " << name << ":\n" << posts << '\n';
            }
        }

        // Option 6, 7, ...: Exit the program 
        else {
            std::cout << "\nExiting the program...\n";
            break;
        }
    }   

    return 0;
}