//****************************************************************************************//
//                          interaction point                             /|x             //
//                                 s=0                                     |              //
//           case: e^{+}   s<0      |         s>0                          | LAB-frame    //
//           -----------------------|-----------------------              c|---------->z  //
//           case: e^{-}   s>0      |         s<0                                         //
//           e^{+}                  |                          e^{-}       E=0.510GeV     //
//         \\ _\| \\                |                     //  |/_  //                     //
//          \\  \  \\               |                   //   /   //                       //
//           \\ _\| \\     e^{+}    |    e^{+}        //  |/_  //                         //
//            \\  \  \\    ---->Z   |    ---->Z     //   /   //                           //
//             \\ _\| \\____________|_____________//  |/_  //                             //
//                  \_ _ _ _ _ _ _ _|_ _ _ _ _ _ _ _ /_ _ _ _ _ _ _ _ _                   //
//                  /   ____________|c____________   \ alpha                              //
//           //  |/_  //            |             \\ _\| \\                               //
//         //   /   //     e^{-}    |   e^{-}      \\  \  \\                              //
//       //  |/_  //      Z<-----   |  Z<----       \\ _\| \\                             //
//     //   /   //                  |                \\  \  \\                            //
//   //  |/_  //                    |                 \\ _\| \\                           //
//     e^{-}                                             e^{+}                            //
//****************************************************************************************//
//  x | x'=Px/Pz |  y | y'=Py/Pz | s | (E-E_nom)/E_nom | wei | nt

#include <iostream>
#include <iomanip>

using namespace std;

void touschekDistribution(){
   gROOT->Reset();

   ifstream myFileLab;
   ifstream myFileStep;
   ifstream myFileBeam;

   myFileLab.open("labdatamy.txt");
   myFileBeam.open("beampipe.txt");
   myFileStep.open("SteppingAction.txt");
  
   Float_t x, y, z, Ek;
   Float_t Px,Py,Pz, weit;
   string vol, mat, particle;
   Int_t evID;


   Double_t z_max,z_min;
   Double_t x_max,x_min;
   Int_t n, i;

  
 
   z_max = 100;
   z_min = -100;
   x_max = 0.;
   x_min = 0.;
 
   TH2F *hzxBp = new TH2F("hzxBp","zx plane",1000,-300,300,1000,-32,32);  
   TH2F *hzxLab = new TH2F("hzxLab","zx plane",1000,-300,300,1000,-32,32);  
   TH2F *hzxStep = new TH2F("hzxStep","zx plane",1000,-300,300,1000,-32,32);  

//   TH2F *hzx2 = new TH2F("hzx2","zx plane",1000,-300,300,1000,-25,32);
//   TH2F *hzx3 = new TH2F("hzx3","zx plane",1000,-300,300,1000,-25,32);
//   TH2F *hzx4 = new TH2F("hzx4","zx plane",1000,-300,300,1000,-25,32);
//   TH2F *hzx5 = new TH2F("hzx5","zx plane",1000,-300,300,1000,-25,32);

//   TH2F *hzy1= new TH2F("hzy1","zy plane",10000,-220,300,1000,-0.1,0.1);
//   TH2F *hzy1= new TH2F("hzy1","zy plane",10000,-79,-76,1000,-0.1,0.1);


   i = 0;
   if(myFileBeam.is_open()){
       while(!myFileBeam.eof()){
	   myFileBeam >> x>> y>> z;
	   hzxBp->Fill(z/10,x/10);
	   if(i%100 == 0){
	       cout<< i <<endl;
	   }
	   i++;
       }
   }
   else{
       cout<<" ERRR : file beampipe.txt not oppened "<<endl;
   }

   i = 0;
   if(myFileLab.is_open()){
       while(!myFileLab.eof()){
	   myFileLab >> x>> y>> z>>Px>>Py>>Pz>>weit;
	   hzxLab->Fill(z,x);
	   if(i%100 == 0){
	       cout<< i <<endl;
	   }
	   i++;
       }
   }
   else{
       cout<<" ERRR : file labdatamy.txt not oppened "<<endl;
   }


   i = 0;
   if(myFileStep.is_open()){
       while(!myFileStep.eof()){
	   //myFileStep >> x>> y>> z>>Px>>Py>>Pz>>Ek>>vol>>mat>>particle>>evID;
	   myFileStep >> x>> y>> z>>Px>>Py>>Pz;
	   hzxStep->Fill(z/10,x/10);
	   if(i%100 == 0){
	       cout<< i <<endl;
	   }
	   i++;
       }
   }
   else{
       cout<<" ERRR : file SteppingAction.txt not oppened "<<endl;
   }

   TCanvas *c1 = new TCanvas("c1","tuoschek particle",10,10,1000,900);
   //c1->Divide(1,3);
   //c1->cd(1);

   hzxBp->SetMarkerColor(1);//blakc
   hzxBp->Draw();
   
   hzxLab->SetMarkerColor(3);//green
   hzxLab->Draw("same");

   hzxStep->SetMarkerColor(6);//green
   hzxStep->Draw("same");

   //--------------FLAGS------------------------
   std::string flag_labadatamyON;
   flag_labadatamyON = "labadatamyON";
   //flag_labadatamyON = "labadatamyOFF";
   //-------------------------------------------
   

   // if(flag_labadatamyON == "labadatamyON"){
      	       
       /*
	 if(z_max < z_lab - Pz_lab*10){
	 z_max = z_lab - Pz_lab*10;
	 }
	 if(z_min > z_lab - Pz_lab*10){
	 z_min = z_lab - Pz_lab*10;
	 }
	 if(x_max < x_lab - Px_lab*10){
	 x_max = x_lab - Px_lab*10;
	 }
	 if(x_min > x_lab - Px_lab*10){
	 x_min = x_lab - Px_lab*10;
	 }
       */

       //hzx2->Fill(z_lab - Pz_lab*50,x_lab - Px_lab*50);
       //hzx3->Fill(z_lab - Pz_lab*100,x_lab - Px_lab*100);
       //hzx4->Fill(z_lab + Pz_lab*40,x_lab + Px_lab*40);
       //hzx5->Fill(z_lab + Pz_lab*60,x_lab + Px_lab*60);
       // hzx6->Fill(z_lab - Pz_lab*200,x_lab - Px_lab*200);
   //}
     
   //n = i-1;
   //cout<< " n = "<< n <<endl;
   //cout<< " z_max = "<< z_max <<endl;
   //cout<< " z_min = "<< z_min <<endl;
   //cout<< " x_max = "<< x_max <<endl;
   //cout<< " x_min = "<< x_min <<endl;
 
  
/*   

   hzx1->SetMarkerColor(3);//green
   hzx2->SetMarkerColor(5);//
   hzx3->SetMarkerColor(6);//pinck
   hzx4->SetMarkerColor(2);//
   hzx5->SetMarkerColor(4);//
   hzxBp->SetMarkerColor(1);//
   hzx1->Draw();
   //hzx2->Draw("same");
   hzx3->Draw("same");
   //hzx4->Draw("same");
   //hzx5->Draw("same");
   hzxBp->Draw("same");
   //hzxBp->Draw();
   //c1->cd(2);
   //hzy1->Draw();
   //c1->cd(3);
   //hzxBp->Draw();
   //c1 = new TCanvas("c1","Exclusion graphs examples",200,10,700,500);   c1->SetGrid();
   TMultiGraph *mg = new TMultiGraph();
   mg->SetTitle("Exclusion graphs");
   const Int_t n = 35;
   Double_t x1[n], x2[n], x3[n], y1[n], y2[n], y3[n];
   for (Int_t i=0;i<n;i++) {
       x1[i] = i*0.1;        y1[i] = 10*sin(x1[i]);
       x2[i] = x1[i];        y2[i] = 10*cos(x1[i]);
       x3[i] = x1[i]+.5;     y3[i] = 10*sin(x1[i])-2;
   }
   gr1 = new TGraph(n,x1,y1);
   gr1->SetLineColor(2);
   gr1->SetLineWidth(1504);
   gr1->SetFillStyle(3005);
   gr2 = new TGraph(n,x2,y2);
   gr2->SetLineColor(4);
   gr2->SetLineWidth(-2002);
   gr2->SetFillStyle(3004);
   gr2->SetFillColor(9);
   gr3 = new TGraph(n,x3,y3);
   gr3->SetLineColor(5);
   gr3->SetLineWidth(-802);
   gr3->SetFillStyle(3002);
   gr3->SetFillColor(2);
   mg->Add(gr1);
   mg->Add(gr2);
   mg->Add(gr3);
   mg->Draw("AC");
*/ 
   
 
   /*
  TMultiGraph *mg = new TMultiGraph();
  mg->SetTitle("touschek propagation");
  
  TGraph *gr1 = new TGraph(n,z,x);
  gr1->SetMarkerColor(3);
  TGraph *gr2 = new TGraph(n,z2,x2);
  gr2->SetMarkerColor(5);
  
  gr1->Draw("AP*");
  gr2->Draw("AP*");
  mg->Add(gr1);
  mg->Add(gr2);
  mg->Draw("AC*");
   */

  myFileBeam.close();
  myFileLab.close();
  myFileStep.close();
 }
