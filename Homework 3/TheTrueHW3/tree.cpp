

int countIncludes(const double a1[], int n1, const double a2[], int n2)
{
    
    if (n1< n2) //base cases
        return 0;
    if (n2<1)
        return 1;
    
    if (a2[n2-1]==a1[n1-1])
        return countIncludes(a1, n1-1, a2, n2-1) + countIncludes(a1, n1-1, a2, n2);
    else
        return countIncludes(a1, n1-1, a2, n2);
}





// Exchange two doubles
void exchange(double& x, double& y)
{
    double t = x;
    x = y;
    y = t;
}

void separate(double a[], int n, double separator,
              int& firstNotGreater, int& firstLess)
{
    if (n < 0)
        n = 0;
    
    firstNotGreater = 0;
    firstLess = n;
    int firstUnknown = 0;
    while (firstUnknown < firstLess)
    {
        if (a[firstUnknown] < separator)
        {
            firstLess--;
            exchange(a[firstUnknown], a[firstLess]);
        }
        else
        {
            if (a[firstUnknown] > separator)
            {
                exchange(a[firstNotGreater], a[firstUnknown]);
                firstNotGreater++;
            }
            firstUnknown++;
        }
    }
}


void order(double a[], int n)
{
   
    if (n<=1)
        return;
    int firstNotGreater, firstLess;
    if (n>=2)
    {
        int mid = n/2;
        separate(a, n, a[mid], firstNotGreater, firstLess);
        order(a,firstNotGreater);
        order(a+firstLess, n-firstLess);
        
        
    }
    return;
    
    
}


