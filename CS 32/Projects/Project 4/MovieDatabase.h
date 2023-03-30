#ifndef MOVIEDATABASE_INCLUDED
#define MOVIEDATABASE_INCLUDED

#include <string>
#include <vector>
#include "treemm.h"
#include <iostream>

class Movie;

class MovieDatabase
{
  public:
    MovieDatabase();
    bool load(const std::string& filename);
    Movie* get_movie_from_id(const std::string& id) const;
    std::vector<Movie*> get_movies_with_director(const std::string& director) const;
    std::vector<Movie*> get_movies_with_actor(const std::string& actor) const;
    std::vector<Movie*> get_movies_with_genre(const std::string& genre) const;
    ~MovieDatabase();

  private:
    bool m_loaded;
    std::vector<Movie*> m_movies;
    TreeMultimap<std::string, Movie*> id2Movie;
    TreeMultimap<std::string, Movie*> director2Movie;
    TreeMultimap<std::string, Movie*> actor2Movie;
    TreeMultimap<std::string, Movie*> genre2Movie;
    
    void string2Vector(std::string input, std::vector<std::string> &vec){
        if (input == "" || input == "," ) return;
        int count = 0;
        int i = 0;
        for (i=0; i<input.size(); i++){
            if (input[i] == ','){
                vec.push_back(input.substr(i-count, count));
                count = 0;
            } else
                count++;
        }
        if (count == input.size())
            vec.push_back(input);
        else
            vec.push_back(input.substr(i-count, count));
    }
};

#endif // MOVIEDATABASE_INCLUDED
