#include <iostream>
#include <fstream>
using namespace std;

Int_t anaMakeRootFile02(){
    
    gROOT->Reset();
    string nameFile[8][8]; 

    const Int_t Nth = 120;
    Double_t Emin = 0.0;
    Double_t Emax = 600;
    Int_t NtotEv = 4000;

    nameFile[1][1] = "p4Sp1_g4_511MeV_E_10e4_geom_fieldON_cutsN11.txt";
    nameFile[1][7] = "p4Sp1_g4_511MeV_E_10e4_geom_fieldON_cutsN17.txt";
    nameFile[2][2] = "p4Sp1_g4_511MeV_E_10e4_geom_fieldON_cutsN22.txt";
    nameFile[4][1] = "p4Sp1_g4_511MeV_E_10e4_geom_fieldON_cutsN41.txt";
    nameFile[7][1] = "p4Sp1_g4_511MeV_E_10e4_geom_fieldON_cutsN71.txt";
    nameFile[1][2] = "p4Sp1_g4_511MeV_E_4000_geom_fieldON_cutsN12.txt";
    nameFile[1][3] = "p4Sp1_g4_511MeV_E_4000_geom_fieldON_cutsN13.txt";
    nameFile[1][4] = "p4Sp1_g4_511MeV_E_4000_geom_fieldON_cutsN14.txt";
    nameFile[1][5] = "p4Sp1_g4_511MeV_E_4000_geom_fieldON_cutsN15.txt";
    nameFile[1][6] = "p4Sp1_g4_511MeV_E_4000_geom_fieldON_cutsN16.txt";
    nameFile[2][1] = "p4Sp1_g4_511MeV_E_4000_geom_fieldON_cutsN21.txt";

    fillHistoL("./Sp1/" + nameFile[1][1], Nth, Emin, Emax, 10000,"");
    fillHistoL("./Sp1/" + nameFile[1][7], Nth, Emin, Emax, 10000,"same");
    fillHistoL("./Sp1/" + nameFile[2][2], Nth, Emin, Emax, 10000,"same");
    fillHistoL("./Sp1/" + nameFile[4][1], Nth, Emin, Emax, 10000,"same");
    fillHistoL("./Sp1/" + nameFile[7][1], Nth, Emin, Emax, 10000,"same");
    fillHistoL("./Sp1/" + nameFile[1][2], Nth, Emin, Emax, NtotEv,"same");
    fillHistoL("./Sp1/" + nameFile[1][3], Nth, Emin, Emax, NtotEv,"same");
    fillHistoL("./Sp1/" + nameFile[1][4], Nth, Emin, Emax, NtotEv,"same");
    fillHistoL("./Sp1/" + nameFile[1][5], Nth, Emin, Emax, NtotEv,"same");
    fillHistoL("./Sp1/" + nameFile[1][6], Nth, Emin, Emax, NtotEv,"same");
    fillHistoL("./Sp1/" + nameFile[2][1], Nth, Emin, Emax, NtotEv,"same");

/*
    nameFile[2][3] = "p4SpPhot_g4_511MeV_E_4000_geom_fieldON_cutsN23.txt";
    nameFile[2][4] = "p4SpPhot_g4_511MeV_E_4000_geom_fieldON_cutsN24.txt";
    nameFile[2][5] = "p4SpPhot_g4_511MeV_E_4000_geom_fieldON_cutsN25.txt";
    nameFile[3][1] = "p4SpPhot_g4_511MeV_E_4000_geom_fieldON_cutsN31.txt";
    nameFile[3][2] = "p4SpPhot_g4_511MeV_E_4000_geom_fieldON_cutsN32.txt";
    nameFile[3][3] = "p4SpPhot_g4_511MeV_E_4000_geom_fieldON_cutsN33.txt";
    nameFile[3][4] = "p4SpPhot_g4_511MeV_E_4000_geom_fieldON_cutsN34.txt";
    nameFile[3][5] = "p4SpPhot_g4_511MeV_E_4000_geom_fieldON_cutsN35.txt";
    nameFile[4][2] = "p4SpPhot_g4_511MeV_E_4000_geom_fieldON_cutsN42.txt";
    nameFile[4][3] = "p4SpPhot_g4_511MeV_E_4000_geom_fieldON_cutsN43.txt";
    nameFile[4][4] = "p4SpPhot_g4_511MeV_E_4000_geom_fieldON_cutsN44.txt";

    fillHistoL("./Phot/" + nameFile[2][3], Nth, Emin, Emax, NtotEv,"same");
    fillHistoL("./Phot/" + nameFile[2][4], Nth, Emin, Emax, NtotEv,"same");
    fillHistoL("./Phot/" + nameFile[2][5], Nth, Emin, Emax, NtotEv,"same");
    fillHistoL("./Phot/" + nameFile[3][1], Nth, Emin, Emax, NtotEv,"same");
    fillHistoL("./Phot/" + nameFile[3][2], Nth, Emin, Emax, NtotEv,"same");
    fillHistoL("./Phot/" + nameFile[3][3], Nth, Emin, Emax, NtotEv,"same");
    fillHistoL("./Phot/" + nameFile[3][4], Nth, Emin, Emax, NtotEv,"same");
    fillHistoL("./Phot/" + nameFile[3][5], Nth, Emin, Emax, NtotEv,"same");
    fillHistoL("./Phot/" + nameFile[4][2], Nth, Emin, Emax, NtotEv,"same");
    fillHistoL("./Phot/" + nameFile[4][3], Nth, Emin, Emax, NtotEv,"same");
    fillHistoL("./Phot/" + nameFile[4][4], Nth, Emin, Emax, NtotEv,"same");

    nameFile[4][5] = "p4SpPhot_g4_511MeV_E_4000_geom_fieldON_cutsN45.txt";
    nameFile[5][1] = "p4SpPhot_g4_511MeV_E_4000_geom_fieldON_cutsN51.txt";
    nameFile[5][2] = "p4SpPhot_g4_511MeV_E_4000_geom_fieldON_cutsN52.txt";
    nameFile[5][4] = "p4SpPhot_g4_511MeV_E_4000_geom_fieldON_cutsN54.txt";
    nameFile[5][5] = "p4SpPhot_g4_511MeV_E_4000_geom_fieldON_cutsN55.txt";
    nameFile[5][7] = "p4SpPhot_g4_511MeV_E_4000_geom_fieldON_cutsN57.txt";
    nameFile[6][1] = "p4SpPhot_g4_511MeV_E_4000_geom_fieldON_cutsN61.txt";
    nameFile[6][2] = "p4SpPhot_g4_511MeV_E_4000_geom_fieldON_cutsN62.txt";
    nameFile[6][6] = "p4SpPhot_g4_511MeV_E_4000_geom_fieldON_cutsN66.txt";
    nameFile[6][7] = "p4SpPhot_g4_511MeV_E_4000_geom_fieldON_cutsN67.txt";
    nameFile[7][5] = "p4SpPhot_g4_511MeV_E_4000_geom_fieldON_cutsN75.txt";
    nameFile[7][6] = "p4SpPhot_g4_511MeV_E_4000_geom_fieldON_cutsN76.txt";
    nameFile[7][7] = "p4SpPhot_g4_511MeV_E_4000_geom_fieldON_cutsN77.txt";
 
    fillHistoL("./Phot/" + nameFile[4][5], Nth, Emin, Emax, NtotEv,"same");
    fillHistoL("./Phot/" + nameFile[5][1], Nth, Emin, Emax, NtotEv,"same");
    fillHistoL("./Phot/" + nameFile[5][2], Nth, Emin, Emax, NtotEv,"same");
    fillHistoL("./Phot/" + nameFile[5][4], Nth, Emin, Emax, NtotEv,"same");
    fillHistoL("./Phot/" + nameFile[5][5], Nth, Emin, Emax, NtotEv,"same");
    fillHistoL("./Phot/" + nameFile[5][7], Nth, Emin, Emax, NtotEv,"same");
    fillHistoL("./Phot/" + nameFile[6][1], Nth, Emin, Emax, NtotEv,"same");
    fillHistoL("./Phot/" + nameFile[6][2], Nth, Emin, Emax, NtotEv,"same");
    fillHistoL("./Phot/" + nameFile[6][6], Nth, Emin, Emax, NtotEv,"same");
    fillHistoL("./Phot/" + nameFile[6][7], Nth, Emin, Emax, NtotEv,"same");
    fillHistoL("./Phot/" + nameFile[7][5], Nth, Emin, Emax, NtotEv,"same");
    fillHistoL("./Phot/" + nameFile[7][6], Nth, Emin, Emax, NtotEv,"same");
    fillHistoL("./Phot/" + nameFile[7][7], Nth, Emin, Emax, NtotEv,"same");
*/

    return 0;
}


TH1F *fillHistoL(string file, const Int_t Nth, Double_t Emin,Double_t Emax, Int_t NtotEv, string flag_f){

    ifstream stream;

    Float_t x,y,z,px,py,pz,E;
    Int_t evID, q;

    Int_t Nev = 0;        //number of the events with Etot > 0.
    Int_t Nthreshold = 0; //number of the events with E < E of the threshold

    Int_t i = 0;

    Int_t index;
    Double_t array[Nth];
    Double_t bin_width = (Emax - Emin)/Nth;
    for(i = 0;i<Nth;i++){
	array[i] = 0.;
    }

    TH1F *h6 = new TH1F("h6","spectrum6",Nth,Emin,Emax);

    stream.open(file.c_str());

    if (stream.is_open()){
	while(!stream.eof()){
	    stream>>evID>>x>>y>>z>>px>>py>>pz>>E>>q;
	    cout<<evID<<endl;
	    h6->Fill(E);
	    //eTot = eDet1 + eDet2 + eDet3 + eDet4;
	    //h1->Fill(eDet1);
	    //h2->Fill(eDet2);
	    //h3->Fill(eDet3);
	    //h4->Fill(eDet4);
	    //h5->Fill(eTot);
	    //if(eTot!=0){
	    //index = int(floor((eTot - Emin)/bin_width));
	    //array[index]++;
	    //Nev = Nev + 1;
	    //}
	    //cout<<eDet1<<endl;
	}
    }
    else{
	cout<<"file not open"<<endl;
    }

/*
    Float_t eff;
    Float_t effErr;

    Nthreshold = 0;
    for( i = 0; i<Nth; i++){
	eff = (Float_t)(Nev - 1 - Nthreshold)/(Float_t)NtotEv;
	if(eff>0)
	    effErr = sqrt(eff*(1-eff)/NtotEv);
	else
	    effErr = 0;
	h6->SetBinContent(i+1,eff);
	h6->SetBinError(i+1,effErr);
	Nthreshold = Nthreshold + array[i];
    }
*/

    stream.close();   

   

    if(flag_f.c_str()=="")
	h6->SetLineColor(3);

    h6->Draw(flag_f.c_str());
    gPad->SetLogy(1);

    return h6;
}

void fillFile(string name,string tr){


    ifstream myfileread;
    Float_t eDet1, eDet2, eDet3, eDet4, eTot;
    Int_t i;

    string file;
    string rootFileName;
    file = "p4SpPhot";
    rootFileName = file + ".root";
    TFile f(rootFileName.c_str(),"recreate");
       
    string txtFileName;
    
    txtFileName = name;

    TTree t1(tr.c_str(),"four crystal");	
    
    t1.Branch("eDet1",&eDet1,"eDet1/F");
    t1.Branch("eDet2",&eDet2,"eDet2/F");
    t1.Branch("eDet3",&eDet3,"eDet3/F");
    t1.Branch("eDet4",&eDet4,"eDet4/F");
    t1.Branch("eTot",&eTot,"eTot/F");
    
    myfileread.open(txtFileName.c_str());
    if(myfileread.is_open()){
	while(!myfileread.eof()){
	    //for(i=0;i<100;i++){
	    myfileread >>eDet1>> eDet2>> eDet3>> eDet4;
	    eTot = eDet1 + eDet2 + eDet3 + eDet4;
	    //Etot = dE1+dE2+dE3+dE4;
	    t1.Fill();
	}
	cout<<" file "<<rootFileName<<" was created"<<endl;
    }
    else{
	cout<<"ERROR : file"<<txtFileName<<" was not open"<<endl;
    }
    myfileread.close();
    t1.Write();


}
