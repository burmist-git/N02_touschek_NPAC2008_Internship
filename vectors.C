#include <iostream>
//#include "vector.h"
#include <map>
using namespace std;

Int_t vectors(){

    map<char,int> mymap;
    char c;
    
    mymap ['a']=101;
    mymap ['c']=202;
    mymap ['f']=303;
    
    for (c='a'; c<'h'; c++){
	cout << c;
	if (mymap.count(c)>0)
	    cout << " is an element of mymap.\n";
	else 
	    cout << " is not an element of mymap.\n";
    }
    

/*
    map<Char_t,Int_t> mymap;

    map<Char_t,Int_t>::iterator it;

    mymap['b'] = 100;
    mymap['a'] = 200;
    mymap['c'] = 300;

    // show content:
    for ( it=mymap.begin() ; it != mymap.end(); it++ )
	cout << (*it).first << " => " << (*it).second << endl;
*/  


    // gROOT-reset();
    //vector<TH1F,Int_t> myvector;

    // TH1F *h1 = new TH1F("h1","spectrum1",100,P0.,100);
    // TH1F *h2 = new TH1F("h2","spectrum2",100,0.,100);

    // long int k = &h1; 

    // h2 = *k;
    // cout<<*k<<endl;

    // int myint;    
    // cout << "Please enter some integers (enter 0 to end):\n";
    // do
    // cin >> myint;
    // myvector.push_back (myint);
    // } while (myint);
    // cout << "myvector stores " << (int) myvector.size() << " numbers.\n";
    
    return 0;
}
