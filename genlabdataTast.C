#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

Int_t genlabdataTest(){
    ofstream myfile;

    Float_t x,y,z px,py,pz;
    Int_t i = 0;

    myfile.open ("labdataTest.txt");
    if(myfile.is_open() && i<10){
	x = i;
	y = i*i;
	myfile<<setw(10)<<x<<setw<<y<<endl;
	i++;
    }
    else{
	cout<<"ERROR : labdataTest.txt is not opened"<<endl;
    }
    myfile.close();
    return 0;
}
