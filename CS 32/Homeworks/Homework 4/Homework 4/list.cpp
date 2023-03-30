void listAll(string path, const File* f)  // two-parameter overload
{
    cout << path;
    if (f->files() == nullptr) {cout << endl;}
    else {
        cout << "/" << endl;
        for (int i = 0; i < f->files()->size(); i++) {
            listAll(path + "/" + f->files()->at(i)->name(), f->files()->at(i));
        }
    }
    
}
