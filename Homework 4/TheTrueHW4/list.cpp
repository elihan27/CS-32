


void listAll(const MenuItem* m, string path)
{
    
    if (m->menuItems() == NULL) //(m==NULL||m->menuItems()->empty())
    {
        
        cout << path<< endl;
        return;
    }
    

    for (vector<MenuItem*>::const_iterator p = m->menuItems()->begin(); p!= m->menuItems()->end(); p++)
    {
        
        //list<int>::const_iterator it  vector<MenuItem*>::const_iterator p;
        
        string k;
        
        if ((m)->name()== "")
        {
            k = path+(*p)->name();
            //path += (*p)->name();
            // cout <<(*p)->name()<< endl;
        }
        
        else
        {
            k = path + "/" + (*p)->name();
            //path += "/" + (*p)->name();
            
        }
        
        if ((*p)->menuItems() != NULL)
            cout<< k<< endl;
        
        listAll(*p, k);
        
        
    }
    
    return;
}
