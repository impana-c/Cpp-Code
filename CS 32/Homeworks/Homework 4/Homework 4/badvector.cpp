void removeBad(vector<Movie*>& v)
{
    vector<Movie*>::iterator it = v.begin();
    while ( it != v.end() ){
        if ((*it)->rating() < 50){
            Movie* temp = *it;
            it = v.erase(it);
            delete temp;
        } else it++;
    }
}
