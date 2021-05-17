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

void mainTest(){
   gROOT->Reset();

   ifstream myfileread;
   ofstream mufilewrite;
   
   Float_t x, x_, y, y_, s, dE_E, weit;
   Float_t x_tmp, y_tmp, s_tmp;
   Float_t x_lab, y_lab, z_lab;
   Float_t xP, yP, zP;
   Float_t xPP, yPP, zPP, X_th;
   Float_t alpha;
   Int_t nt, i;

   Float_t E_nom,M_elec,E,P_coef,pxm,pym,pzm;
   Float_t Px_lab,Py_lab,Pz_lab;
   E_nom = 0.510;          //GeV
   M_elec = 0.510999e-03;  //GeV

   //TFile f("C:/root/macros/tree1.root","recreate");
   TFile f("tree1.root","recreate");

   TTree t1("t1","a simple Tree with simple variables");
   Double_t random;
   Int_t ev;

   t1.Branch("x",&x,"x/F");
   t1.Branch("x_",&x_,"x_/F");

   t1.Branch("y",&y,"y/F");
   t1.Branch("y_",&y_,"y_/F");

   t1.Branch("s",&s,"s/F");
   t1.Branch("dE_E",&dE_E,"dE_E/F");

   t1.Branch("weit",&weit,"weit/F");
   t1.Branch("x_lab",&x_lab,"x_lab/F");
   t1.Branch("y_lab",&y_lab,"y_lab/F");
   t1.Branch("z_lab",&z_lab,"z_lab/F");
   t1.Branch("Px_lab",&Px_lab,"Px_lab/F");
   t1.Branch("Py_lab",&Py_lab,"Py_lab/F");
   t1.Branch("Pz_lab",&Pz_lab,"Pz_lab/F");


   t1.Branch("nt",&nt,"nt/F");

   alpha = 3.97566*(TMath::Pi())/180.;
   i=0;
   X_th = 1.9;                                           //cm
   mufilewrite.open("labdata.txt");
   //myfileread.open("C:/root/macros/testMntp.txt");
   myfileread.open("testMntp.txt");
   if(myfileread.is_open()){
      while(!myfileread.eof()){
      //for(i=0;i<100;i++){
         myfileread >> x_tmp>> x_>> y_tmp>> y_>> s_tmp>> dE_E>> weit>>nt;
         x = -x_tmp*100.;                                // (e+) -> (e-) cm
         y =  y_tmp*100.;                                // (e+) -> (e-) cm
         s =  s_tmp*100.;                                // (e+) -> (e-) cm

         E = E_nom*(dE_E+1.0);
         P_coef = (TMath::Sqrt( (-M_elec*M_elec+E*E)/(x_*x_+y_*y_+1.0) ));

         pxm = x_*P_coef;
         pym = y_*P_coef;
         pzm = P_coef;

         Pz_lab=(TMath::Cos((TMath::Pi())-alpha))*pzm+(TMath::Sin((TMath::Pi())-alpha))*pxm;
         Py_lab=pym;
         Px_lab=-(TMath::Sin((TMath::Pi())-alpha))*pzm+(TMath::Cos((TMath::Pi())-alpha))*pxm;

         if ( s>0) {
            xP    =    (TMath::Cos((TMath::Pi())-alpha))*x;
            zP    =    (TMath::Sin((TMath::Pi())-alpha))*x;
            xPP   = -s*(TMath::Sin(alpha))+xP;
            zPP   = -s*(TMath::Cos(alpha))+zP;

            x_lab = xPP+X_th;                               //cm
            y_lab = y;                                      //cm
            z_lab = zPP;                                    //cm
         }
         else{
            xP    =     (TMath::Cos((TMath::Pi())-alpha))*x;
            zP    =     (TMath::Sin((TMath::Pi())-alpha))*x;
            xPP   = -s*(TMath::Sin(alpha))+xP;
            zPP   = -s*(TMath::Cos(alpha))+zP;

            x_lab = xPP-X_th;                               //cm
            y_lab = y;                                      //cm
            z_lab = zPP;                                    //cm
         }
	 if(i%100 == 0){
	     cout<<i<<endl;
	 }
	 mufilewrite<<setw(15)<<x_lab<<setw(15)<<y_lab<<setw(15)<<z_lab<<setw(15)<<-Px_lab<<setw(15)<<-Py_lab<<setw(15)<<-Pz_lab<<setw(15)<<weit<<endl;
         //cout<<" Sin(alpha) : "<<TMath::Sin(alpha)<<" Cos(alpha) : "<<TMath::Cos(alpha)<<endl;
         //cout<< "   s : "<<s<<"   x : "<<x<< "   xP: "<<xP<< "   xPP : "<<xPP<< " x_lab : "<< x_lab<<endl;
         //cout<< "   s : "<<s<<"   y : "<<y<< "   yP: "<< y<< "   yPP : "<< y << " y_lab : "<< y_lab<<endl;
         //cout<< "   s : "<<s<<"   z : "<<s<< "   zP: "<<zP<< "   zPP : "<<zPP<< " z_lab : "<< z_lab<<endl;
	 i++;
         t1.Fill();
      }
   }
   else{
      cout<<"ERRR file not open!!!"<<endl;
   }

   t1.Write();
   myfileread.close();
       mufilewrite.close();
 }
