#include "MovieDatabase.h"
#include "Movie.h"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <cctype>
using namespace std;

MovieDatabase::MovieDatabase()
{
    m_loaded = false;
}

bool MovieDatabase::load(const string& filename)
{
    if (m_loaded){
        return false;
    } else {
        ifstream movieDBfile (filename);
        if ( ! movieDBfile ) {
            return false;
        }
        string s;
        while (getline(movieDBfile, s)){
            string tempID = s;
            for (int i=0; i<tempID.size(); i++)
                tempID[i] = tolower(tempID[i]);
            
            string tempTitle;
            getline(movieDBfile, tempTitle);
            string tempRY;
            getline(movieDBfile, tempRY);
            
            vector<string> tempDirectors;
            getline(movieDBfile, s);
            string2Vector(s, tempDirectors);
            
            vector<string> tempActors;
            getline(movieDBfile, s);
            string2Vector(s, tempActors);
            
            vector<string> tempGenres;
            getline(movieDBfile, s);
            string2Vector(s, tempGenres);
            
            float tempRating;
            movieDBfile >> tempRating;
            movieDBfile.ignore(10000, '\n');
            
            Movie* tempMovie = new Movie(tempID, tempTitle, tempRY, tempDirectors, tempActors, tempGenres, tempRating);
            m_movies.push_back(tempMovie);
            //map each ID to a Movie pointer
            id2Movie.insert(tempID, tempMovie);
            //map each director string to a Movie pointer
            for (int i=0; i<tempDirectors.size(); i++){
                string temp = tempDirectors[i];
                for (int i=0; i<temp.size(); i++)
                    temp[i] = tolower(temp[i]);
                director2Movie.insert(temp, tempMovie);
            }
            //map each actor string to a Movie pointer
            for (int i=0; i<tempActors.size(); i++){
                string temp = tempActors[i];
                for (int i=0; i<temp.size(); i++)
                    temp[i] = tolower(temp[i]);
                actor2Movie.insert(temp, tempMovie);
            }
            //map each genre string to a Movie pointer
            for (int i=0; i<tempGenres.size(); i++){
                string temp = tempGenres[i];
                for (int i=0; i<temp.size(); i++)
                    temp[i] = tolower(temp[i]);
                genre2Movie.insert(temp, tempMovie);
            }
            movieDBfile.ignore(10000, '\n');
        }
        m_loaded = true;
        return true;
    }
    return false;
}

Movie* MovieDatabase::get_movie_from_id(const string& id) const
{
    //convert the id to lowercase and return the Movie pointer with that id
    string id2 = id;
    for (int i=0; i<id2.size(); i++)
        id2[i] = tolower(id2[i]);
    if (id2Movie.find(id2).is_valid()){
        Movie* tempMovie = id2Movie.find(id2).get_value();
        if (tempMovie->get_id() == id2){
            return tempMovie;
        }
    }
    return nullptr;
}

vector<Movie*> MovieDatabase::get_movies_with_director(const string& director) const
{
    //convert the director to lowercase and return a vector of Movie pointers with that director
    string director2 = director;
    for (int i=0; i<director2.size(); i++)
        director2[i] = tolower(director2[i]);
    vector<Movie*> tempVec;
    TreeMultimap<string, Movie*>::Iterator it = director2Movie.find(director2);
    while(it.is_valid()){
        Movie* tempMovie = it.get_value();
        tempVec.push_back(tempMovie);
        it.advance();
    }
    return tempVec;
}

vector<Movie*> MovieDatabase::get_movies_with_actor(const string& actor) const
{
    //convert the actor to lowercase and return a vector of Movie pointers with that actor
    string actor2 = actor;
    for (int i=0; i<actor2.size(); i++)
        actor2[i] = tolower(actor2[i]);
    vector<Movie*> tempVec;
    TreeMultimap<string, Movie*>::Iterator it = actor2Movie.find(actor2);
    while(it.is_valid()){
        Movie* tempMovie = it.get_value();
        tempVec.push_back(tempMovie);
        it.advance();
    }
    return tempVec;
}

vector<Movie*> MovieDatabase::get_movies_with_genre(const string& genre) const
{
    //convert the genre to lowercase and return a vector of Movie pointers with that genre
    string genre2 = genre;
    for (int i=0; i<genre2.size(); i++)
        genre2[i] = tolower(genre2[i]);
    vector<Movie*> tempVec;
    TreeMultimap<string, Movie*>::Iterator it = genre2Movie.find(genre2);
    while(it.is_valid()){
        Movie* tempMovie = it.get_value();
        tempVec.push_back(tempMovie);
        it.advance();
    }
    return tempVec;
}

MovieDatabase::~MovieDatabase(){
    vector<Movie*>::iterator it = m_movies.begin();
    while ( it != m_movies.end() ){
        delete *it;
        m_movies.erase(it);
        it++;
    }
    m_movies.clear();
}

