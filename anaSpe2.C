#include <iostream>
#include <fstream>
using namespace std;

Int_t anaSpe2(){
    
    ifstream stream1;
    ifstream stream2;

    Float_t eDet1,eDet2,eDet3,eDet4, eTot;

    //---------------------------------------------------------------------------
    Int_t Nev1 = 0;          //number of the events with Etot > 0.
    Int_t Nthreshold1 = 0;   //number of the events with E < E of the threshold
    Int_t NtotEv1 = 10000;    //total number of events

    Int_t Nev2 = 0;          //number of the events with Etot > 0.
    Int_t Nthreshold2 = 0;   //number of the events with E < E of the threshold
    Int_t NtotEv2 = 10000;    //total number of events

    const Int_t Nth = 120;  //number of the different thresholds
    Double_t Emin = 0.;     //MeV for efficiently
    Double_t Emax = 600;    //MeV for efficiently

    Double_t ESmin = 0.;    //MeV for energy in crislals
    Double_t ESmax = 511;   //MeV for energy in crislals
    Int_t NbinS = 100;     //MeV for energy in crislals

    string flagLog;
    flagLog = "flagLogON";
    //flagLog = "flagLogOFF";

    string file1;
    string file2;

    file1 = "spectrum.txt";
    //file = "p4Sp_g4_E_5990_geom2_fieldON.txt";
    //file1 = "p4SpPhot_g4_E_10e3_geom2_fieldON_cuts22.txt";
    //file1 = "p4SpPhot_g4_E_5990_geom2_fieldON.txt";
    //file1 = "p4SpPhot_g4_E_10e4_geom2_fieldOFF.txt";
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

    //file2 = "p4SpPhot_g4_E_10e4_geom2_fieldOFF.txt";
    file2 = "/home/leonid/g4work/N02/dataALL/Phot/p4Phot_g4_511MeV_E_10e4_geom21_fieldOFF_cuts22.txt";

    //----------------------------------------------------------------------------

    Int_t index;
    Double_t array1[Nth];
    Double_t array2[Nth];
    Double_t bin_width = (Emax - Emin)/Nth;
    for(Int_t i = 0;i<Nth;i++){
	array1[i] = 0.;
	array2[i] = 0.;
    }

    TCanvas *c1 = new TCanvas("c1","spectrum",10,10,1000,1000);
    
    c1->Divide(3,2);
   
    TH1F *h11 = new TH1F("h11","spectrum11",NbinS,ESmin,ESmax);
    TH1F *h21 = new TH1F("h21","spectrum21",NbinS,ESmin,ESmax);
    TH1F *h31 = new TH1F("h31","spectrum31",NbinS,ESmin,ESmax);
    TH1F *h41 = new TH1F("h41","spectrum41",NbinS,ESmin,ESmax);
    TH1F *h51 = new TH1F("h51","spectrum51",NbinS,ESmin,ESmax);
    TH1F *h61 = new TH1F("h61","spectrum61",Nth,Emin,Emax);

    TH1F *h12 = new TH1F("h12","spectrum12",NbinS,ESmin,ESmax);
    TH1F *h22 = new TH1F("h22","spectrum22",NbinS,ESmin,ESmax);
    TH1F *h32 = new TH1F("h32","spectrum32",NbinS,ESmin,ESmax);
    TH1F *h42 = new TH1F("h42","spectrum42",NbinS,ESmin,ESmax);
    TH1F *h52 = new TH1F("h52","spectrum52",NbinS,ESmin,ESmax);
    TH1F *h62 = new TH1F("h62","spectrum62",Nth,Emin,Emax);

    stream1.open(file1.c_str());

    if (stream1.is_open()){
	while(!stream1.eof()){
	    stream1>>eDet1>>eDet2>>eDet3>>eDet4;
	    //cout<<eDet2<<endl;
	    eTot = eDet1 + eDet2 + eDet3 + eDet4;
	    h11->Fill(eDet1);
	    h21->Fill(eDet2);
	    h31->Fill(eDet3);
	    h41->Fill(eDet4);
	    h51->Fill(eTot);
	    if(eTot!=0){
		index = int(floor((eTot - Emin)/bin_width));
		array1[index]++;
		Nev1 = Nev1 + 1;
	    }
	    //cout<<eDet1<<endl;
	}
    }
    else{
	cout<<"ERROR : file "<<file1<<" was not open"<<endl;
    }

    Float_t eff = 0;
    Float_t effErr = 0;

    Nthreshold1 = 0;
    for( i = 0; i<Nth; i++){
	eff = (Float_t)(Nev1 - Nthreshold1)/(Float_t)NtotEv1;
	effErr = sqrt(eff*(1-eff)/NtotEv1);
	h61->SetBinContent(i+1,eff);
	//cout<<i<<" "<<eff<<endl;
	h61->SetBinError(i+1,effErr);
	Nthreshold1 = Nthreshold1 + array1[i];
    }

    stream2.open(file2.c_str());

    if (stream2.is_open()){
	while(!stream2.eof()){
	    stream2>>eDet1>>eDet2>>eDet3>>eDet4;
	    //cout<<eDet2<<endl;
	    eTot = eDet1 + eDet2 + eDet3 + eDet4;
	    h12->Fill(eDet1);
	    h22->Fill(eDet2);
	    h32->Fill(eDet3);
	    h42->Fill(eDet4);
	    h52->Fill(eTot);
	    if(eTot!=0){
		index = int(floor((eTot - Emin)/bin_width));
		array2[index]++;
		Nev2 = Nev2 + 1;
	    }
	    //cout<<eDet1<<endl;
	}
    }
    else{
	cout<<"ERROR : file "<<file2<<" was not open"<<endl;
    }

    Nthreshold2 = 0;
    for( i = 0; i<Nth; i++){
	eff = (Float_t)(Nev2 - Nthreshold2)/(Float_t)NtotEv2;
	effErr = sqrt(eff*(1-eff)/NtotEv2);
	h62->SetBinContent(i+1,eff);
	h62->SetBinError(i+1,effErr);
	Nthreshold2 = Nthreshold2 + array2[i];
    }

    h12->SetLineColor(3);
    h22->SetLineColor(3);
    h32->SetLineColor(3);
    h42->SetLineColor(3);
    h52->SetLineColor(3);
    h62->SetLineColor(3);


    c1->cd(1);
    h11->Draw();
    h12->Draw("same");
    if(flagLog == "flagLogON")
	gPad->SetLogy(1);
    c1->cd(2);
    h21->Draw();
    h22->Draw("same");
    if(flagLog == "flagLogON")
	gPad->SetLogy(1);
    c1->cd(3);
    h31->Draw();
    h32->Draw("same");
    if(flagLog == "flagLogON")
	gPad->SetLogy(1);
    c1->cd(4);
    h41->Draw();
    h42->Draw("same");
    if(flagLog == "flagLogON")
	gPad->SetLogy(1);
    c1->cd(5);
    h51->Draw();
    h52->Draw("same");
    if(flagLog == "flagLogON")
	gPad->SetLogy(1);
    c1->cd(6);
    h61->Draw();
    h62->Draw("same");
    gPad->SetLogy(1);

    stream1.close();
    stream2.close();

    return 0;
}
