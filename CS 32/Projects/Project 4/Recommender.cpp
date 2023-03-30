#include "Recommender.h"
#include "UserDatabase.h"
#include "MovieDatabase.h"
#include "Movie.h"
#include "User.h"
#include <algorithm>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

Recommender::Recommender(const UserDatabase& user_database,
                         const MovieDatabase& movie_database)
{
    m_userDB = &user_database;
    m_movieDB = &movie_database;
}

bool Recommender::comp(const MRPtr& one, const MRPtr& two){
    //compare the two Movie pointers based on compatibility score, rating, and alphabetical order
    if (one.compatibility_score > two.compatibility_score)
        return true;
    else if (one.compatibility_score < two.compatibility_score)
        return false;
    else{
        if (one.m_movie->get_rating() > two.m_movie->get_rating())
            return true;
        else if (one.m_movie->get_rating() < two.m_movie->get_rating())
            return false;
        else{
            if (one.m_movie->get_title() < two.m_movie->get_title())
                return true;
            else
                return false;
        }
    }
}

vector<MovieAndRank> Recommender::recommend_movies(const string& user_email, int movie_count) const {
    if (movie_count <=0 ) return vector<MovieAndRank>();
    unordered_map<Movie*, int> movie2Score;
    vector<MovieAndRank> resultVec;
    vector<string> watchHistory = m_userDB->get_user_from_email(user_email)->get_watch_history();
    for (int i=0; i<watchHistory.size(); i++){
        //get a Movie pointer and increment its score in the map based on its directors, actors, and genres
        Movie* watchedMovie = m_movieDB->get_movie_from_id(watchHistory.at(i));
        for (int j=0; j<watchedMovie->get_directors().size(); j++){
            string tempDirector = watchedMovie->get_directors().at(j);
            vector<Movie*> tempVec = m_movieDB->get_movies_with_director(tempDirector);
            for (int k=0; k<tempVec.size(); k++){
                movie2Score[tempVec.at(k)] += 20;
            }
        }
        for (int j=0; j<watchedMovie->get_actors().size(); j++){
            string tempActor = watchedMovie->get_actors().at(j);
            vector<Movie*> tempVec = m_movieDB->get_movies_with_actor(tempActor);
            for (int k=0; k<tempVec.size(); k++){
                movie2Score[tempVec.at(k)] += 30;
            }
        }
        for (int j=0; j<watchedMovie->get_genres().size(); j++){
            string tempGenre = watchedMovie->get_genres().at(j);
            vector<Movie*> tempVec = m_movieDB->get_movies_with_genre(tempGenre);
            for (int k=0; k<tempVec.size(); k++){
                movie2Score[tempVec.at(k)] += 1;
            }
        }
    }
    //remove any movies already in the user's watch history
    for (int i=0; i<watchHistory.size(); i++){
        Movie* watchedMovie = m_movieDB->get_movie_from_id(watchHistory.at(i));
        movie2Score.erase(watchedMovie);
    }
    
    //create a vector of struct objects that contain Movie pointers and scores
    vector<MRPtr> pVec;
    for (auto it = movie2Score.begin(); it != movie2Score.end(); it++){
        if(it->second >1){
            MRPtr tempMRP = MRPtr(it->first, it->second);
            pVec.push_back(tempMRP);
        }
    }
    //order the vector
    sort(pVec.begin(), pVec.end(), comp);
    
    for (int i=0; i<min(movie_count, int(pVec.size())); i++){
        //convert each of the MRPtr objects back to MovieAndRank objects
        MovieAndRank tempMR = MovieAndRank(pVec.at(i).m_movie->get_id(), pVec.at(i).compatibility_score);
        resultVec.push_back(tempMR);
    }
    
    return resultVec;
}

Recommender::~Recommender(){}
