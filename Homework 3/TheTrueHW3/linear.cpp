

bool allTrue(const double a[], int n)
{
    if (n<1)
        return true;
    if (somePredicate(a[0]) == false)
        return false;
    return allTrue(a+1, n-1);
}

int countFalse(const double a[], int n)
{
    if (n<1)
        return 0;
    if (somePredicate(a[0]) == false)
        return 1 + countFalse(a+1, n-1);
    else
        return countFalse(a+1, n-1);
}


int firstFalse(const double a[], int n)
{
       if (n < 1)
        return -1;
    if (somePredicate(a[0]) == false)
        return 0;
    
    int x = firstFalse(a+1, n-1);
    if (x == -1)
        return x;
    else
        return 1 + x;

    
}

int indexOfMin(const double a[], int n)
{
    if (n < 1)
        return -1;
    if (n == 1)
        return 0;
  
    int x = indexOfMin(a, n-1);
    
    if (a[x] < a[n-1])
        return x;
    else
        return n-1;
    
}
// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not include
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
//    10 50 40 20 50 40 30
// then the function should return true if a2 is
//    50 20 30
// or
//    50 40 40
// and it should return false if a2 is
//    50 30 20
// or
//    10 20 20
bool includes(const double a1[], int n1, const double a2[], int n2)
{
   
    if (n1< n2)
        return false;
    if (n2<1)
        return true;
   
    if (a2[0] == a1[0]) //if equal
        return includes(a1+1, n1-1, a2+1, n2-1); //advance a2 (test different a2 value)
    else
        return includes(a1+1, n1-1, a2, n2); //advance a1 (test different a1 value)
        

}

