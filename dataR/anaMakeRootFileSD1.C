#include <iostream>
#include <fstream>
using namespace std;

Int_t anaMakeRootFileSD1(){
    
    gROOT->Reset();

    ifstream myfileread;
    Float_t x,y,z,px,py,pz,Ekin;
    Int_t i, charge, evID;
   
 
    string file;
    string txtFileName;
    string rootFileName;
    
    file = "SteppingAction";
    txtFileName = file + ".txt";
    rootFileName = file + ".root";
    
    TFile f(rootFileName.c_str(),"recreate");
    
    TTree t1("t1","a simple Tree with simple variables");	
    
    t1.Branch("evID",&evID,"evID/I");
    t1.Branch("x",&x,"x/F");
    t1.Branch("y",&y,"y/F");
    t1.Branch("z",&z,"z/F");
    t1.Branch("px",&px,"px/F");
    t1.Branch("py",&py,"py/F");
    t1.Branch("pz",&pz,"pz/F");
    t1.Branch("Ekin",&Ekin,"Ekin/F");
    t1.Branch("charge",&charge,"charge/I");
    
    myfileread.open(txtFileName.c_str());
    if(myfileread.is_open()){
	while(!myfileread.eof()){
	    //for(i=0;i<100;i++){
	    myfileread >>evID>> x>> y>> z>> px>> py>>pz>>Ekin>>charge;
	    //Etot = dE1+dE2+dE3+dE4;
	    t1.Fill();
	}
	cout<<" file "<<rootFileName<<" was created"<<endl;
    }
    else{
	cout<<"ERROR : file"<<txtFileName<<"was not open"<<endl;
    }
    myfileread.close();
    t1.Write();
    
    return 0;
}
