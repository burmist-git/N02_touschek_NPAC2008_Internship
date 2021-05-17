#include <iostream>
#include <fstream>
using namespace std;

Int_t anaSpeLong(){
    
    gROOT->Reset();

    Int_t stepFlag; //1--2
    stepFlag = 1;

    if (stepFlag==1){ 
	ifstream myfileread;
	Float_t dE1,dE2,dE3,dE4,Etot;    
	Int_t i;
	
	string file;
	string txtFileName;
	string rootFileName;

	file = "510MeV_G_100000";
	txtFileName = file + ".txt";
	rootFileName = file + ".root";

	TFile f(rootFileName.c_str(),"recreate");

	TTree t1("t1","a simple Tree with simple variables");	

	t1.Branch("dE1",&dE1,"dE1/F");
	t1.Branch("dE2",&dE2,"dE2/F");
	t1.Branch("dE3",&dE3,"dE3/F");
	t1.Branch("dE4",&dE4,"dE4/F");
	t1.Branch("Etot",&Etot,"Etot/F");
	
	myfileread.open(txtFileName.c_str());
	if(myfileread.is_open()){
	    while(!myfileread.eof()){
		//for(i=0;i<100;i++){
		myfileread >> dE1>> dE2>> dE3>> dE4;
		Etot = dE1+dE2+dE3+dE4;
		t1.Fill();
	    }
	    cout<<" file "<<rootFileName<<" was created"<<endl;
	}
	else{
	    cout<<"file not open"<<endl;
	}
	myfileread.close();   
	t1.Write();
    }

/*
    if (stepFlag==2){
	string file;
	string txtFileName;
	string rootFileName;

	//file = "510MeV_G_100000";
	//txtFileName = file + ".txt";
	//rootFileName = file + ".root";

	TFile f("510MeV_G_100000.root");

    //TFile f(rootFileName.c_str());
	f.ls();
	
	TTree *MyTree = t1;
    
	TCanvas *myCanvas01 = new TCanvas("myCanvas01","canvas",10,10,500,500);
	TH1F  *hzOld = new TH1F("hzOld","histo",100,0,500);
	MyTree->Draw("dE1>>hzOld");
	

//	TCanvas *myCanvas05 = new TCanvas("myCanvas05","canvas",50,50,500,500);
//	TH2F  *dE1vsdE2 = new TH2F("dE1vsdE2","histo",200,0,500,200,0,500);
//	MyTree->Draw("dE1:dE2>>dE1vsdE2");
	//cout<<"wewewedw"<<endl;

    } 
*/
/*
    ifstream stream;
    ifstream stream2;

    Float_t eDet1,eDet2,eDet3,eDet4;

    TCanvas *c1 = new TCanvas("c1","spectrum",10,10,1000,1000);
    
    c1->Divide(3,2);
   
    TH1F *h1 = new TH1F("h1","spectrum1",1000,0.,520);
    TH1F *h2 = new TH1F("h2","spectrum2",1000,0.,520);
    TH1F *h3 = new TH1F("h3","spectrum3",1000,0.,520);
    TH1F *h4 = new TH1F("h4","spectrum4",1000,0.,520);
    TH1F *h5 = new TH1F("h5","spectrum5",1000,0.,520);

    stream.open("50MeV_E_100000.txt");
    //stream.open("100MeV_E_100000.txt");
    //stream.open("200MeV_E_100000.txt");
    //stream.open("300MeV_E_100000.txt");
    //stream.open("400MeV_E_100000.txt");
    //stream.open("510MeV_E_100000.txt");

    //stream.open("50MeV_G_100000.txt");
    //stream.open("100MeV_G_100000.txt");
    //stream.open("200MeV_G_100000.txt");
    //stream.open("300MeV_G_100000.txt");
    //stream.open("400MeV_G_100000.txt");
    //stream.open("510MeV_G_100000.txt");

    //stream.open("p1_100000.txt");
    //stream.open("p2_100000.txt");
    //stream.open("p3_100000.txt");
    //stream.open("p4_100000.txt");
    //stream.open("p5_100000.txt");
    //stream.open("p6_100000.txt");


    if (stream.is_open()){
	while(!stream.eof()){
	    stream>>eDet1>>eDet2>>eDet3>>eDet4;
	    //cout<<eDet2<<endl;
	    h1->Fill(eDet1);
	    h2->Fill(eDet2);
	    h3->Fill(eDet3);
	    h4->Fill(eDet4);
	    h5->Fill(eDet1 + eDet2 + eDet3 + eDet4);
	    //cout<<eDet1<<endl;
	}
    }
    else{
	cout<<"file not open"<<endl;
    }

    c1->cd(1);
    gPad->SetLogy(1);
    h1->Draw();
    h2->Draw("same");

    c1->cd(2);
    gPad->SetLogy(1);
    h2->Draw();

    c1->cd(3);
    h3->Draw();
    c1->cd(4);
    h4->Draw();
    c1->cd(5);
    h5->Draw();

    stream.close();   
*/
    return 0;
}
