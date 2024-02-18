#pragma once

#include <iostream>
#include <map>
#include <set>
#include <string>
#include <istream>
#include <fstream>
#include <sstream>

using namespace std;

/**
 * Cleans a specific token by:
 * - Removing leading and trailing punctuation
 * - Converting to lowercase
 * If the token has no letters, returns the empty string.
 */
string cleanToken(string s){
    string cleaned = "";
    int alpha = 0, count = 0;

    /*Counts number of alphanumeric chars*/
    for (char i : s)
        alpha += isalpha(i);

    /*Returns empty string if string contains no alphanumeric chars*/
    if (alpha == 0)
        return "";
    else{
        /*Adds lowercase-d chars to string if they're not leading ot trailing punctuation*/
        for (char i : s){
            if ((count != 0 && count != alpha) || !ispunct(i))
                cleaned += tolower(i);
            count += isalpha(i);
        }
    }

    return cleaned;
}

/**
 * Returns a set of the cleaned tokens in the given text.
 */
set<string> gatherTokens(string text){
    set<string> tokens;
    string temp;
    istringstream ss(text);

    /*Creates a set of words cleaned by the cleanToken function*/
    while (ss >> temp){
        if (cleanToken(temp) != "")
            tokens.insert(cleanToken(temp));
    }

    return tokens;
}

/**
 * Builds the inverted index from the given data file. The existing contents
 * of `index` are left in place.
 */
int buildIndex(string filename, map<string, set<string>> &index){
    int processed = -1;
    string url;
    string tokenline;
    set<string> tokens;

    ifstream inFile;
    inFile.open(filename);

    if (!inFile.is_open()){
        cout << "Invalid filename." << endl;
        return 0;
    }

    while (!inFile.eof()){
        getline(inFile, url);
        getline(inFile, tokenline);

        /*Creates set of tokens for each url-token pair*/
        tokens = gatherTokens(tokenline); 

        /*Does actions for every token in line*/
        for (string i : tokens){
            /*If map(index) has key-value pair with token as key*/
            if (index.find(i) != index.end()){
                /*Inserts url into value set*/
                index[i].insert(url);
            }
            else{ 
                /*If map doesn't have a key-value pair with token as key*/
                /*Creates a new set with just this url*/
                set<string> temp = {url};
                /*Creates new key value pair with token and new set*/
                index[i] = temp;
            }

            if (index[i].count("") != 0)
                index[i].erase("");
        }

        processed++;
    }

    inFile.close();
    return processed;
}

/**
 * Runs a search query on the provided index, and returns a set of results.
 *
 * Search terms are processed using set operations (union, intersection, difference).
 */
set<string> findQueryMatches(map<string, set<string>> &index, string sentence){
    string temp;
    istringstream ss(sentence);
    set<string> results;
    set<string> tempSet;

    while (ss >> temp){
        /*Determines if word is a union, intersection, or difference word*/
        if (temp.at(0) == '+'){
            temp = cleanToken(temp.substr(1));
            /*If no urls have this word, return empty set*/
            if (index.count(temp) == 0){
                results.clear();
                return results;
            }

            /*Removes every url that doesn't have this word from results set*/
            tempSet = results;
            for (string j : results){
                bool found = false;

                for (string i : index[temp]){
                    if (i == j)
                        found = true; 
                }

                if (!found)
                    tempSet.erase(j);
            }
            results = tempSet;
        }
        else if (temp.at(0) == '-'){
            temp = cleanToken(temp.substr(1));

            /*Removes every url that has this word from results set*/
            if(index.count(temp) > 0){
                for (string i : index[temp]){
                    if (results.find(i) != results.end())
                        results.erase(i);
                }
            }
        }
        else{
            temp = cleanToken(temp);
            
            /*Adds all urls with this word to results set*/
            for (string i : index[temp])
                results.insert(i);
        }
    }
    return results;
}

/**
 * Runs the main command loop for the search program
 */
void searchEngine(string file){
    map<string, set<string>> index;
    set<string> results;
    string query;

    int count = buildIndex(file, index);

    cout << "Stand by while building index..." << endl;
    cout << "Indexed " << count << " pages containing " << index.size() << " unique terms" << endl;

    cout << endl << "Enter query sentence (press enter to quit): ";
    getline(cin, query);

    /*Runs queries and prints results until user presses enter*/
    while (query != ""){
        results = findQueryMatches(index, query);
        cout << "Found " << results.size() << " matching pages" << endl;

        for (string i : results)
            cout << i << endl;

        cout << endl;

        cout << "Enter query sentence (press enter to quit): ";
        getline(cin, query);
    }
    cout << "Thank you for searching!";
}
