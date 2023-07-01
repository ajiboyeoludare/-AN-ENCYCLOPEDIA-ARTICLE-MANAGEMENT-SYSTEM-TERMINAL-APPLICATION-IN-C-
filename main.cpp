#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// This section  defines the attributes that an article will have
struct Article {
    std::string title;
    std::string abstract;
    std::string keywords;
    std::string author;
    std::string date;
    std::vector<std::string> subsections;
};


// Function to add an new article to the database file article.txt in a vector structure
void addArticle(std::ofstream& file) {
    Article article;
    std::cout << "Enter article title: ";
    std::getline(std::cin, article.title);
    std::cout << "Enter short abstract: ";
    std::getline(std::cin, article.abstract);
    std::cout << "Enter keywords: ";
    std::getline(std::cin, article.keywords);
    std::cout << "Enter author: ";
    std::getline(std::cin, article.author);
    std::cout << "Enter date of last edit: ";
    std::getline(std::cin, article.date);

    std::string subsection;
    std::cout << "Enter main subsection titles (Enter 'done' to finish):\n";
    while (true) {
        std::getline(std::cin, subsection);
        if (subsection == "done") {
            break;
        }
        article.subsections.push_back(subsection);
    }

    // Display the article before writing it to the file
    std::cout << "\nNew Article:\n";
    std::cout << "Title: " << article.title << '\n';
    std::cout << "Abstract: " << article.abstract << '\n';
    std::cout << "Keywords: " << article.keywords << '\n';
    std::cout << "Author: " << article.author << '\n';
    std::cout << "Date: " << article.date << '\n';
    std::cout << "Main Subsections:\n";
    for (const auto& subsec : article.subsections) {
        std::cout << "- " << subsec << '\n';
    }
    std::cout << "-----\n";

    // Prompt to save the article
    std::string saveChoice;
    std::cout << "Do you want to save this article? (yes/no): ";
    std::getline(std::cin, saveChoice);

    // Display the article to the file if the user chooses to save it
    if (saveChoice == "yes") {
        file << article.title << '\n';
        file << article.abstract << '\n';
        file << article.keywords << '\n';
        file << article.author << '\n';
        file << article.date << '\n';
        for (const auto& subsec : article.subsections) {
            file << subsec << '\n';
        }
        file << "-----\n";

        std::cout << "Article added successfully!\n";
    } else {
        std::cout << "Article not saved.\n";
    }
}



// Function to delete an new article in the database file article.txt 
void deleteArticle(const std::string& title, std::ifstream& inputFile, std::ofstream& outputFile) {
    std::string line;
    bool found = false;

    while (std::getline(inputFile, line)) {
        if (line == title) {
            found = true;
            // Skip the lines corresponding to the article
            for (int i = 0; i < 5; ++i) {
                std::getline(inputFile, line);
            }
        } else {
            // Write the non-matching lines to the output file
            outputFile << line << '\n';
        }
    }

    if (found) {
        std::cout << "Article deleted successfully!\n";
    } else {
        std::cout << "Article not found!\n";
    }
}

// Function to edit/update article information in the database file article.txt 
void editArticle(const std::string& oldTitle, std::ifstream& inputFile, std::ofstream& outputFile) {
    std::string line;
    bool found = false;

    while (std::getline(inputFile, line)) {
        if (line == oldTitle) {
            found = true;
            // Read and discard the existing article information
            std::string title = line;
            std::getline(inputFile, line); // Skip the old title
            std::getline(inputFile, line); // Skip the old abstract
            std::getline(inputFile, line); // Skip the old keywords
            std::getline(inputFile, line); // Skip the old author
            std::getline(inputFile, line); // Skip the old date

            // Prompt the user to enter the updated information
            Article updatedArticle;
            std::cout << "Enter updated article title: ";
            std::getline(std::cin, updatedArticle.title);
            std::cout << "Enter updated short abstract: ";
            std::getline(std::cin, updatedArticle.abstract);
            std::cout << "Enter updated keywords: ";
            std::getline(std::cin, updatedArticle.keywords);
            std::cout << "Enter updated author: ";
            std::getline(std::cin, updatedArticle.author);
            std::cout << "Enter updated date of last edit: ";
            std::getline(std::cin, updatedArticle.date);

            std::string subsection;
            std::cout << "Enter updated main subsection titles (Enter 'done' to finish):\n";
            while (true) {
                std::getline(std::cin, subsection);
                if (subsection == "done") {
                    break;
                }
                updatedArticle.subsections.push_back(subsection);
            }

            // Write the updated article to the output file
            outputFile << updatedArticle.title << '\n';
            outputFile << updatedArticle.abstract << '\n';
            outputFile << updatedArticle.keywords << '\n';
            outputFile << updatedArticle.author << '\n';
            outputFile << updatedArticle.date << '\n';
            for (const auto& subsec : updatedArticle.subsections) {
                outputFile << subsec << '\n';
            }
            outputFile << "-----\n";

            std::cout << "Article updated successfully!\n";
        } else {
            // Write the non-matching lines to the output file
            outputFile << line << '\n';
        }
    }

    if (!found) {
        std::cout << "Article not found!\n";
    }
}

// Function to search for an article in the database file article.txt 
void searchArticle(const std::string& title, std::ifstream& inputFile) {
    std::string line;
    bool found = false;

    while (std::getline(inputFile, line)) {
        if (line == title) {
            found = true;
            std::cout << "Article found!\n";
            std::cout << "Title: " << line << '\n';
            std::getline(inputFile, line); // Read and display the abstract
            std::cout << "Abstract: " << line << '\n';
            std::getline(inputFile, line); // Read and display the keywords
            std::cout << "Keywords: " << line << '\n';
            std::getline(inputFile, line); // Read and display the author
            std::cout << "Author: " << line << '\n';
            std::getline(inputFile, line); // Read and display the date
            std::cout << "Date: " << line << '\n';
            std::cout << "Main Subsections:\n";
            while (std::getline(inputFile, line) && line != "-----") {
                std::cout << "- " << line << '\n';
            }
            break;
        }
    }

    if (!found) {
        std::cout << "Article not found!\n";
    }
}

// Function to list all articles and count total letters in each articlein in database file article.txt 
void listArticles(std::ifstream& inputFile) {
    std::string line;
    std::cout << "Listing and Compare all articles:\n";

    while (std::getline(inputFile, line)) {
        int totalLetters = 0;
        std::cout << "Title: " << line << '\n';
        totalLetters += line.length(); // Count letters in the title

        for (int i = 0; i < 5; ++i) {
            std::getline(inputFile, line);
            totalLetters += line.length(); // Count letters in other parts of the article
        }

        std::string subsection;
        while (std::getline(inputFile, subsection) && subsection != "-----") {
            totalLetters += subsection.length(); // Count letters in subsection titles
        }

        std::cout << "Total number of letters in this  article is: " << totalLetters << '\n';
    }
}


int main() {
    std::ofstream file("articles.txt", std::ios::app); // Open file in append mode
    if (!file) {
        std::cerr << "Error opening file.\n";
        return 1;
    }
    file.close(); // Close the file

    while (true) {
      std::cout << "\n    AN ENCYCLOPEDIA ARTICLE MANAGEMENT SYSTEM BY AJIBOYE OLUDARE:\n";
      std::cout << "\n\n";
        std::cout << "\nChoose an option:\n";
        std::cout << "a. Add an article\n";
        std::cout << "b. Delete an article\n";
        std::cout << "c. Edit/update article information\n";
        std::cout << "s. Search for an article by title\n";
        std::cout << "l. List and Compare all articles\n";
        std::cout << "q. Quit\n";
        std::cout << "Enter your choice a, b, c, s, l or q: ";

        std::string choice;
        std::getline(std::cin, choice);

        if (choice == "a") {
            std::ofstream outputFile("articles.txt", std::ios::app); // Open file in append mode
            if (!outputFile) {
                std::cerr << "Error opening file.\n";
                return 1;
            }
            addArticle(outputFile);
            outputFile.close(); // Close the file
        } else if (choice == "b") {
            std::ifstream inputFile("articles.txt");
            if (!inputFile) {
                std::cerr << "Error opening file.\n";
                return 1;
            }
            std::ofstream outputFile("articles_temp.txt"); // Create a temporary file
            if (!outputFile) {
                std::cerr << "Error opening file.\n";
                return 1;
            }
            std::string title;
            std::cout << "Enter the title of the article to delete: ";
            std::getline(std::cin, title);
            deleteArticle(title, inputFile, outputFile);
            inputFile.close();   // Close the input file
            outputFile.close();  // Close the temporary file

            // Remove the original file and rename the temporary file
            std::remove("articles.txt");
            std::rename("articles_temp.txt", "articles.txt");
        } else if (choice == "c") {
            std::ifstream inputFile("articles.txt");
            if (!inputFile) {
                std::cerr << "Error opening file.\n";
                return 1;
            }
            std::ofstream outputFile("articles_temp.txt"); // Create a temporary file
            if (!outputFile) {
                std::cerr << "Error opening file.\n";
                return 1;
            }
            std::string title;
            std::cout << "Enter the title of the article to edit: ";
            std::getline(std::cin, title);
            editArticle(title, inputFile, outputFile);
            inputFile.close();   // Close the input file
            outputFile.close();  // Close the temporary file

            // Remove the original file and rename the temporary file
            std::remove("articles.txt");
            std::rename("articles_temp.txt", "articles.txt");
        } else if (choice == "s") {
            std::ifstream inputFile("articles.txt");
            if (!inputFile) {
                std::cerr << "Error opening file.\n";
                return 1;
            }
            std::string title;
            std::cout << "Enter the title of the article to search: ";
            std::getline(std::cin, title);
            searchArticle(title, inputFile);
            inputFile.close(); // Close the input file
        } else if (choice == "l") {
            std::ifstream inputFile("articles.txt");
            if (!inputFile) {
                std::cerr << "Error opening file.\n";
                return 1;
            }
            listArticles(inputFile);
            inputFile.close(); // Close the input file
        } else if (choice == "q") {
            std::cout << "Goodbye!\n";
            break;
        } else {
            std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
