#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;
namespace fs = std::filesystem;

void searchFolders( string search_path, string word)
{
    fs::path p;
    for (fs::directory_iterator itr(search_path); itr != fs::directory_iterator(); ++itr)
    {
        if (fs::is_directory(itr->path()))
        {   
            searchFolders(itr->path().string(), word);
        }
        if (itr->path().filename() != "." && itr->path().filename() != "..")
        {
            p = itr->path();
            if (fs::is_regular_file(p) && !p.empty())
            {
                ifstream file(p.string());
                string line;
                if(file.is_open())
                {
                    while (getline(file, line))
                    {
                        if(line.find(word) != string::npos)
                        {
                        cout << "Found \"" << word << "\" in file: " << p.string() << endl;
                        }
                    }
                    file.close();
                }
                else
                {
                    cout << "cant read file " << p.string() << endl;
                }
            }       
        }
    }
}

int main(int argc, char **argv)
{
    string search_path = "/your directory";
    string word = "";
    cout << "Enter search word:" << endl;
    cin >> word;
    searchFolders(search_path, word);
}
