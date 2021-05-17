//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id: A01MagneticField.hh,v 1.4 2006/06/29 16:31:27 gunter Exp $
// --------------------------------------------------------------
//

#ifndef ExN02MagneticField_H
#define ExN02MagneticField_H 1

#include "globals.hh"
#include "G4MagneticField.hh"

//write to file
//#include "iostream.h"
//#include "fstream.h"


//class ExN02MagneticFieldMessenger;

class ExN02MagneticField : public G4MagneticField
{
public:
    ExN02MagneticField();
    ~ExN02MagneticField();
    
    virtual void GetFieldValue( const  double Point[4],
				double *Bfield ) const;

    //G4double RotationZ(G4double z, G4double x, G4int Ind);
    //G4double RotationX(G4double z, G4double x, G4int Ind);
        
    bool SetField( const double *Point, G4double & Bx, G4double & By, G4double & Bz) const;
 
    static G4double RotationZ(G4double z, G4double x, G4int Ind);
    static G4double RotationX(G4double z, G4double x, G4int Ind);
   
    //ofstream myfile; 
 
private:
   
    FILE *streamQD0_L;   
    FILE *streamQD0_R;  
 
    FILE *streamQD1_R_U;
    FILE *streamQD1_R_D;
    FILE *streamQD1_L_U;
    FILE *streamQD1_L_D;
      
    G4double gQD0;
    G4double gQD1;

};

#endif

