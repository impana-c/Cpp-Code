void removeBad(list<Movie*>& li)
{
    list<Movie*>::iterator it = li.begin();
    while ( it != li.end() ){
        if ((*it)->rating() < 50){
            Movie* temp = *it;
            it = li.erase(it);
            delete temp;
        } else it++;
    }
}
