#include "UserDatabase.h"
#include "User.h"
#include "MovieDatabase.h"
#include "Movie.h"
#include <iostream>
#include <string>
#include <vector>
#include "Recommender.h"
using namespace std;


//////////////////////////i/////////////////////////////////////////////////////
//
// You are free to do whatever you want with this file, since you won't
// be turning it in.  Presumably, you will make changes to help you test
// your classes.  For example, you might try to implement only some User
// member functions to start out with, and so replace our main routine with
// one that simply creates a User and verifies that the member functions you
// implemented work correctly.
//
//////////////////////////i/////////////////////////////////////////////////////


  // If your program is having trouble finding these files. replace the
  // string literals with full path names to the files.  Also, for test
  // purposes, you may want to create some small, simple user and movie
  // data files to makde debuggiing easier, so you can replace the string
  // literals with the names of those smaller files.

//const string USER_DATAFILE  = "/Users/impana/Desktop/CS 32/Project 4/Project 4/users.txt";
//const string MOVIE_DATAFILE = "/Users/impana/Desktop/CS 32/Project 4/Project 4/movies.txt";
const string USER_DATAFILE  = "users.txt";
const string MOVIE_DATAFILE = "movies.txt";

void findMatches(const Recommender& r, const MovieDatabase& md, const string& user_email, int num_recommendations){
 // get up to ten movie recommendations for the user
    vector<MovieAndRank> recommendations =r.recommend_movies(user_email, num_recommendations);
    if (recommendations.empty())
        cout << "We found no movies to recommend :(.\n";
    else {
        for (int i = 0; i < recommendations.size(); i++) {
            const MovieAndRank& mr = recommendations[i];
            Movie* m = md.get_movie_from_id(mr.movie_id);
            cout << i+1 << ". " << m->get_title() << " ("
            << m->get_release_year() << ")\n Rating: "
            << m->get_rating() << "\n Compatibility Score: "
            << mr.compatibility_score << "\n";
            cout <<  endl;
        }
    }
}

int main()
{
	UserDatabase udb;
	if (!udb.load(USER_DATAFILE))  // In skeleton, load always return false
	{
		cout << "Failed to load user data file " << USER_DATAFILE << "!" << endl;
		return 1;
	}
    MovieDatabase mdb;
    if (!mdb.load(MOVIE_DATAFILE))  // In skeleton, load always return false
    {
        cout << "Failed to load movie data file " << MOVIE_DATAFILE << "!" << endl;
        return 1;
    }
//    //TODO: delete later
//    mdb.printMovies();
    
//    vector<Movie*> tempVec = mdb.get_movies_with_director("adam pinney");
//    for (int i=0; i<tempVec.size(); i++){
//        Movie* tempMovie = tempVec.at(i);
//        cout << tempMovie->get_title()<< endl;
//    }
//    cout << tempVec.size()<< endl;
    
	for (;;)
	{
		cout << "Enter user email address (or quit): ";
//        cout << "Enter a user's email for recommendations: ";
		string email;
		getline(cin, email);
		if (email == "quit")
			return 0;
		User* u = udb.get_user_from_email(email);
		if (u == nullptr)
			cout << "No user in the database has that email address." << endl;
        else{
			cout << "Found " << u->get_full_name() << endl;
            
            cout << "Enter number of recommendations to provide: ";
            int numRecs;
            cin >> numRecs;
            cin.ignore(10000, '\n');
            cout << "----------------------------" << endl;
            
            //Print out watch history
//            cout << "User " << u->get_full_name() << " has watched the following movies: "<< endl;
//            for (int i=0; i<u->get_watch_history().size(); i++){
//                string tempID = (u->get_watch_history().at(i));
//                Movie* tempMovie = mdb.get_movie_from_id(tempID);
//                cout << tempMovie->get_title()<< endl;
//            }
//            cout << endl;
            
            Recommender r(udb, mdb);
            findMatches(r, mdb, email, numRecs);
        }
	}
}
