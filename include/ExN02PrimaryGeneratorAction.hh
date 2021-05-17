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
//
// $Id: ExN02PrimaryGeneratorAction.hh,v 1.7 2006/06/29 17:47:43 gunter Exp $
// GEANT4 tag $Name: geant4-09-01-patch-01 $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
#ifndef ExN02PrimaryGeneratorAction_h
#define ExN02PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"

#include "iostream.h"
#include "fstream.h"

class ExN02DetectorConstruction;
class G4ParticleGun;
class G4Event;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
class ExN02PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
    ExN02PrimaryGeneratorAction(ExN02DetectorConstruction*);    
    ~ExN02PrimaryGeneratorAction();
    
public:

    ifstream myfile;
    ifstream myTestfile;
    
    void GeneratePrimaries(G4Event*);
    double GetEkin(){return Ekinet;};
    double GetFr(){return fraction;};
    inline double RotationZ(double z, double x, int Ind);
    inline double RotationX(double z, double x, int Ind);

    //G4String command;// = "/control/execute ";
private:
    G4ParticleGun* particleGun;
    ExN02DetectorConstruction* myDetector;
    void SetEkin(double E){Ekinet = E;};
    void SetFr(double wight){fraction = wight;};
    double Ekinet;
    double fraction;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif


