#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

Int_t anaXSpe(){
    
    Double_t Emin = 0.;
    Double_t Emax = 11.;
    Int_t Nbin = 500;

    string file1 = "05Mev_372959_0001mmg_0001mmeM_0001mmeP.txt";

    //vector<TH1F> myvector = fillHist(file1,Emin,Emax,Nbin,kRed);
    Int_t myvector = fillHist(file1,Emin,Emax,Nbin,kRed);

/*
    ifstream stream1;
    ifstream stream2;
    ifstream stream3;
    ifstream stream4;
    ifstream stream5;
    ifstream stream6;




    Float_t eDet1,eDet2,eDet3,eDet4;


   
    TH1F *h1 = new TH1F("h1","spectrum1",50,0.,11);
    TH1F *h2 = new TH1F("h2","spectrum2",50,0.,11);
    TH1F *h3 = new TH1F("h3","spectrum3",50,0.,11);
    TH1F *h4 = new TH1F("h4","spectrum4",50,0.,11);
    TH1F *h5 = new TH1F("h5","spectrum5",50,0.,11);

    TH1F *h12 = new TH1F("h12","spectrum12",50,0.,11);
    TH1F *h22 = new TH1F("h22","spectrum22",50,0.,11);
    TH1F *h32 = new TH1F("h32","spectrum32",50,0.,11);
    TH1F *h42 = new TH1F("h42","spectrum42",50,0.,11);
    TH1F *h52 = new TH1F("h52","spectrum52",50,0.,11);

    TH1F *h13 = new TH1F("h1","spectrum13",500,0.,0.6);
    TH1F *h23 = new TH1F("h2","spectrum23",500,0.,0.6);
    TH1F *h33 = new TH1F("h3","spectrum33",500,0.,0.6);
    TH1F *h43 = new TH1F("h4","spectrum43",500,0.,0.6);
    TH1F *h53 = new TH1F("h5","spectrum53",500,0.,0.6);

    TH1F *h14 = new TH1F("h1","spectrum14",500,0.,0.6);
    TH1F *h24 = new TH1F("h2","spectrum24",500,0.,0.6);
    TH1F *h34 = new TH1F("h3","spectrum34",500,0.,0.6);
    TH1F *h44 = new TH1F("h4","spectrum44",500,0.,0.6);
    TH1F *h54 = new TH1F("h5","spectrum54",500,0.,0.6);

    //stream1.open("05Mev_372959_0001mmg_0001mmeM_0001mmeP.txt");
    //stream2.open("05Mev_372959_01mmg_01mmeM_01mmeP.txt");
    //stream2.open("05Mev_372959_1cmg_1cmeM_1cmeP.txt");
    //stream2.open("05Mev_372959_10cmg_10cmeM_10cmeP.txt");
    //stream2.open("05Mev_372959_100cmg_100cmeM_100cmeP.txt");
    //stream2.open("05Mev_372959_1cmg_20cmeM_20cmeP.txt");

    //stream1.open("10Mev_372959_1cmg_20cmeM_20cmeP.txt");
    //stream1.open("10Mev_372959_01mmg_01mmeM_01mmeP.txt");
    stream1.open("10Mev_372959_2cmg_2cmeM_2cmeP.txt"); 
    //stream2.open("10Mev_372959_1mmg_1mmeM_1mmeP.txt");
    //stream2.open("10Mev_372959_01mmg_01mmeM_01mmeP.txt");
    //stream2.open("10Mev_372959_001mmg_001mmeM_001mmeP.txt");
    //stream2.open("10Mev_372959_001mmg_1mmeM_1mmeP.txt");
    stream2.open("10Mev_372959_1cmg_1cmeM_1cmeP.txt");


    TCanvas *c1 = new TCanvas("c1","spectrum",10,10,1000,1000);
    c1->Divide(3,2);


    Double_t eTot = 0.;

    if (stream1.is_open()){
	while(!stream1.eof()){
	    stream1>>eDet1>>eDet2>>eDet3>>eDet4;
	    //cout<<eDet2<<endl;
	    h1->Fill(eDet1);
	    h2->Fill(eDet2);
	    h3->Fill(eDet3);
	    h4->Fill(eDet4);
	    eTot = eDet1 + eDet2 + eDet3 + eDet4;
	    h5->Fill(eTot);
	    //cout<<eDet1<<endl;
	}
    }
    else{
	cout<<"file not open"<<endl;
    }

   if (stream2.is_open()){
	while(!stream2.eof()){
	    stream2>>eDet1>>eDet2>>eDet3>>eDet4;
	    //cout<<eDet2<<endl;
	    h12->Fill(eDet1);
	    h22->Fill(eDet2);
	    h32->Fill(eDet3);
	    h42->Fill(eDet4);
	    eTot = eDet1 + eDet2 + eDet3 + eDet4;
	    h52->Fill(eTot);
	    //cout<<eDet1<<endl;
	}
    }
    else{
	cout<<"file not open"<<endl;
    }

   Double_t err = culculDiff(h1,h12);
   cout<<"err = "<<err<<endl;

   h12->SetLineColor(3);//green
   h22->SetLineColor(3);//green
   h32->SetLineColor(3);//green
   h42->SetLineColor(3);//green
   h52->SetLineColor(3);//green

    c1->cd(1);
    h1->Draw("error");
    h12->Draw("same error");
    gPad->SetLogy(1);
    c1->cd(2);
    h2->Draw("error");
    h22->Draw("same error");
    gPad->SetLogy(1);
    c1->cd(3);
    h3->Draw("error");
    h32->Draw("same error");
    gPad->SetLogy(1);
    c1->cd(4);
    h4->Draw("error");
    h42->Draw("same error");
    gPad->SetLogy(1);
    c1->cd(5);
    h5->Draw("error");
    h52->Draw("same error");
    gPad->SetLogy(1);

    stream1.close();   
    stream2.close();   
*/
    return 0;
}

//vector<TH1F> fillHist(string file, Double_t Emin, Double_t Emax, Int_t Nbin, Int_t kRed){
Int_t fillHist(string file, Double_t Emin, Double_t Emax, Int_t Nbin, Int_t kRed){
//     TH1F h1 = new TH1F("h1","spectrum1", Nbin, Emin, Emax);
//     TH1F h2 = new TH1F("h2","spectrum2", Nbin, Emin, Emax);
//     TH1F h3 = new TH1F("h3","spectrum3", Nbin, Emin, Emax);
//     TH1F h4 = new TH1F("h4","spectrum4", Nbin, Emin, Emax);
//     TH1F h5 = new TH1F("h5","spectrum5", Nbin, Emin, Emax);

    TH1F h1 = TH1F("h1","spectrum1", Nbin, Emin, Emax);
    TH1F h2 = TH1F("h2","spectrum2", Nbin, Emin, Emax);
    TH1F h3 = TH1F("h3","spectrum3", Nbin, Emin, Emax);
    TH1F h4 = TH1F("h4","spectrum4", Nbin, Emin, Emax);
    TH1F h5 = TH1F("h5","spectrum5", Nbin, Emin, Emax);

    Double_t eDet1, eDet2, eDet3, eDet4, eTot;

    ifstream stream;
    stream.open(file.c_str()); 
    
    if (stream.is_open()){
	while(!stream.eof()){
	    stream>>eDet1>>eDet2>>eDet3>>eDet4;
	    h1.Fill(eDet1);
	    h2.Fill(eDet2);
	    h3.Fill(eDet3);
	    h4.Fill(eDet4);
	    eTot = eDet1 + eDet2 + eDet3 + eDet4;
	    h5.Fill(eTot);
	    //cout<<eDet1<<endl;
	}
    }
    else{
	cout<<"file "<<file<<" was not open"<<endl;
    }
    stream.close();
    
    vector<TH1F> myvector;
    myvector.push_back(h1);
    myvector.push_back(h2);
    myvector.push_back(h3);
    myvector.push_back(h4);
    myvector.push_back(h5);
    //return myvector;
    return 0;
}


Double_t culculDiff(TH1F *h1,TH1F *h12){
    Int_t Nbin = h1->GetSize();
    Double_t ChiSq = 0.;
    Double_t Error;
    for(Int_t i=1;i<Nbin+1;i++){
	Error = h12->GetBinError(i);
	if(Error == 0)Error = 1;
	ChiSq = ChiSq + sqr((h1->GetBinContent(i)-h12->GetBinContent(i))/Error);
    }
    return ChiSq;
}

Double_t sqr(Double_t a){
    return a*a;
}
