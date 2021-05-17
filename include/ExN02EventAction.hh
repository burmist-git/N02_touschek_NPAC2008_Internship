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
// $Id: ExN02EventAction.hh,v 1.8 2006/06/29 17:47:35 gunter Exp $
// GEANT4 tag $Name: geant4-09-01-patch-01 $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
#ifndef ExN02EventAction_h
#define ExN02EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"
#include <stdio.h>
#include <time.h>


class G4Event;
class ExN02RunAction;
class ExN02PrimaryGeneratorAction;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class ExN02EventAction : public G4UserEventAction
{
  public:
    ExN02EventAction(ExN02RunAction*, ExN02PrimaryGeneratorAction*);
   ~ExN02EventAction();

  public:
    void BeginOfEventAction(const G4Event*);
    void EndOfEventAction(const G4Event*);

    void AddDet(G4double de1, G4double de2,G4double de3, G4double de4 ,G4double dl) {EnergyDet1R += de1; EnergyDet2R += de2;
	EnergyDet3R += de3; EnergyDet4R += de4; TrackLDet += dl;};

private:
    ExN02RunAction*  runAct;
    ExN02PrimaryGeneratorAction* primaryGenerator;
    G4double  EnergyDet1R, EnergyDet2R, EnergyDet3R, EnergyDet4R, EnergyTarget;
    G4double  TrackLDet, TrackLTarget;
    FILE* pFile;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
