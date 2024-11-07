#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <cstdlib>

std::map<std::string, int> votes;

void loadVotes() {
    std::ifstream file("votes.txt");
    std::string candidate;
    int count;
    while (file >> candidate >> count) {
        votes[candidate] = count;
    }
    file.close();
}

void saveVotes() {
    std::ofstream file("votes.txt");
    for (const auto& vote : votes) {
        file << vote.first << " " << vote.second << std::endl;
    }
    file.close();
}

void castVote(const std::string& candidate) {
    votes[candidate]++;
    saveVotes();
}

void displayResults() {
    std::cout << "Content-Type: text/html\n\n";
    std::cout << "<html><body>";
    for (const auto& vote : votes) {
        std::cout << "<p>" << vote.first << ": " << vote.second << " votes</p>";
    }
    std::cout << "</body></html>";
}

int main() {
    loadVotes();
    std::string query = getenv("QUERY_STRING");
    if (query.find("vote=") != std::string::npos) {
        std::string candidate = query.substr(query.find("=") + 1);
        castVote(candidate);
    }
    displayResults();
    return 0;
}
