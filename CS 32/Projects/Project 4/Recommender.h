#ifndef RECOMMENDER_INCLUDED
#define RECOMMENDER_INCLUDED

#include <string>
#include <vector>
#include <map>

class UserDatabase;
class MovieDatabase;
class Movie;

struct MovieAndRank
{
    MovieAndRank(const std::string& id, int score) : movie_id(id), compatibility_score(score){}
    std::string movie_id;
    int compatibility_score;
};
class Recommender
{
    private:
      const UserDatabase* m_userDB;
      const MovieDatabase* m_movieDB;
    //creating a private struct like MovieAndRank that holds a Movie pointer rather than the ID
      struct MRPtr{
          MRPtr(Movie* pMovie, int pScore) : m_movie(pMovie), compatibility_score(pScore){}
          Movie* m_movie;
          int compatibility_score;
      };
    public:
        Recommender(const UserDatabase& user_database, const MovieDatabase& movie_database);
        std::vector<MovieAndRank> recommend_movies(const std::string& user_email,int movie_count) const;
        static bool comp(const MRPtr& movie1, const MRPtr& movie2);
        ~Recommender();
};

#endif // RECOMMENDER_INCLUDED
