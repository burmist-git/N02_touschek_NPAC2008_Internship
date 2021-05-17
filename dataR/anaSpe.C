#include <iostream>
#include <fstream>
using namespace std;

Int_t anaSpe(){
    
    ifstream stream;
    ifstream stream2;

    Float_t eDet1,eDet2,eDet3,eDet4, eTot;

    //---------------------------------------------------------------------------
    Int_t Nev = 0;          //number of the events with Etot > 0.
    Int_t Nthreshold = 0;   //number of the events with E < E of the threshold
    //Int_t NtotEv = 10000; //total number of events
    Int_t NtotEv = 5990; //total number of events

    const Int_t Nth = 120;  //number of the different thresholds
    Double_t Emin = 0.;     //MeV for efficiently
    Double_t Emax = 600;    //MeV for efficiently

    Double_t ESmin = 0.;    //MeV for energy in crislals
    Double_t ESmax = 511;   //MeV for energy in crislals
    Int_t NbinS = 5000;     //MeV for energy in crislals

    string flagLog;
    flagLog = "flagLogON";
    //flagLog = "flagLogOFF";

    string file;

    file = "spectrum.txt";
    //file = "p4Sp_g4_E_5990_geom2_fieldON.txt";
    //file = "p4SpPhot_g4_E_5990_geom2_fieldON.txt";
    //file = "50MeV_E_100000.txt";
    //file = "100MeV_E_100000.txt";
    //file = "200MeV_E_100000.txt";
    //file = "300MeV_E_100000.txt";
    //file = "400MeV_E_100000.txt";
    //file = "510MeV_E_100000.txt";

    //file = "50MeV_G_100000.txt";
    //file = "100MeV_G_100000.txt";
    //file = "200MeV_G_100000.txt";
    //file = "300MeV_G_100000.txt";
    //file = "400MeV_G_100000.txt";
    //file = "510MeV_G_100000.txt";

    //file = "p1_100000.txt";
    //file = "p2_100000.txt";
    //file = "p3_100000.txt";
    //file = "p4_100000.txt";
    //file = "p5_100000.txt";
    //file = "p6_100000.txt";

    //----------------------------------------------------------------------------

    Int_t index;
    Double_t array[Nth];
    Double_t bin_width = (Emax - Emin)/Nth;
    for(i = 0;i<Nth;i++){
	array[i] = 0.;
    }

    TCanvas *c1 = new TCanvas("c1","spectrum",10,10,1000,1000);
    
    c1->Divide(3,2);
   
    TH1F *h1 = new TH1F("h1","spectrum1",NbinS,ESmin,ESmax);
    TH1F *h2 = new TH1F("h2","spectrum2",NbinS,ESmin,ESmax);
    TH1F *h3 = new TH1F("h3","spectrum3",NbinS,ESmin,ESmax);
    TH1F *h4 = new TH1F("h4","spectrum4",NbinS,ESmin,ESmax);
    TH1F *h5 = new TH1F("h5","spectrum5",NbinS,ESmin,ESmax);
    TH1F *h6 = new TH1F("h6","spectrum6",Nth,Emin,Emax);

    stream.open(file.c_str());

    if (stream.is_open()){
	while(!stream.eof()){
	    stream>>eDet1>>eDet2>>eDet3>>eDet4;
	    //cout<<eDet2<<endl;
	    eTot = eDet1 + eDet2 + eDet3 + eDet4;
	    h1->Fill(eDet1);
	    h2->Fill(eDet2);
	    h3->Fill(eDet3);
	    h4->Fill(eDet4);
	    h5->Fill(eTot);
	    if(eTot!=0){
		index = int(floor((eTot - Emin)/bin_width));
		array[index]++;
		Nev = Nev + 1;
	    }

	    //cout<<eDet1<<endl;
	}
    }
    else{
	cout<<"file not open"<<endl;
    }

    Nthreshold = 0;
    for( i = 0; i<Nth; i++){
	h6->SetBinContent(i+1,(Nev - Nthreshold)/(Float_t)NtotEv);
	//cout<<i+1<<"    "<<(Nev - Nthreshold)/((Float_t)NtotEv)<<endl;
	Nthreshold = Nthreshold + array[i];
    }


    c1->cd(1);
    h1->Draw();
    if(flagLog == "flagLogON")
	gPad->SetLogy(1);
    c1->cd(2);
    h2->Draw();
    if(flagLog == "flagLogON")
	gPad->SetLogy(1);
    c1->cd(3);
    h3->Draw();
    if(flagLog == "flagLogON")
	gPad->SetLogy(1);
    c1->cd(4);
    h4->Draw();
    if(flagLog == "flagLogON")
	gPad->SetLogy(1);
    c1->cd(5);
    h5->Draw();
    if(flagLog == "flagLogON")
	gPad->SetLogy(1);
    c1->cd(6);
    h6->Draw();
    gPad->SetLogy(1);

    stream.close();   

    return 0;
}
