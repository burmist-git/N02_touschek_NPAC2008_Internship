#include <iostream>
#include <fstream>
using namespace std;

Int_t ana(){
    
    ifstream stream;
    Float_t eDet, eTarget;

    TCanvas *c1 = new TCanvas("c1","spectrum",10,10,800,800);
    
    c1->Divide(1,2);
   
    TH1F *h1 = new TH1F("h1","spectrum",1000,0.,1.3);
    TH1F *h2 = new TH1F("h2","spectrum",1000,0.,1.3);

    stream.open("spectrum.txt");

    if (stream.is_open()){
	while(!stream.eof()){
	    stream>>eTarget>>eDet;
	    h1->Fill(eTarget);
	    h2->Fill(eDet);
	    //cout<<eTarget<<endl;
	}
    }
    else{
	cout<<"file not open"<<endl;
    }

    c1->cd(1);
    h1->Draw();
    c1->cd(2);
    h2->Draw();
    stream.close();   

    return 0;
}
