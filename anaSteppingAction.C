#include <iostream>
#include <fstream>
#include <string>
using namespace std;

Int_t anaSteppingAction(){
    // reading a text file

    Double_t x,y,z;
    Double_t xP[1000],yP[1000],zP[1000];
    string vol, mat;

    Int_t i, n;

    i = 0;

    TCanvas *c1 = new TCanvas("c1","spectrum",10,10,800,400);
    c1->SetFillColor(10);



    ifstream myfile("SteppingAction.txt");
    if (myfile.is_open()){
	while (!myfile.eof() ){
	    //while (i<100){
	    myfile >>xP[i] >>yP[i]>>zP[i]>>vol>>mat;
	    
	    //cout<<xP[i]<<"  " << yP[i]<< endl;
	    i++;
	}
	myfile.close();
    }
    else cout << "Unable to open file"; 
    
    n = i-2;
    TGraph *gr1 = new TGraph(n,xP,yP);
    gr1->Draw("APL");
    
    return 0;
}
