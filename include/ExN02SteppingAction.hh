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
// $Id: ExN02SteppingAction.hh,v 1.8 2006/06/29 17:47:48 gunter Exp $
// GEANT4 tag $Name: geant4-09-01-patch-01 $
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef ExN02SteppingAction_h
#define ExN02SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include <G4RunManager.hh>

#include "stdio.h"

class ExN02DetectorConstruction;
class ExN02EventAction;
class G4RunManager;
class ExN02PrimaryGeneratorAction;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class ExN02SteppingAction : public G4UserSteppingAction
{
public:
    ExN02SteppingAction(ExN02DetectorConstruction*, ExN02EventAction*, G4RunManager*, ExN02PrimaryGeneratorAction*);
    ~ExN02SteppingAction();
    
    void UserSteppingAction(const G4Step*);
    void SetRunManager(G4RunManager *runMan) {runManager = runMan;};
    //virtual void SetRunManager() {G4cout<<"OK"<<G4endl;};

private:
    FILE *streamStep;
    FILE *streamStep2;
    G4RunManager *runManager;
    G4int evtID;
    G4bool beginOfEvent;
    void writeEv(FILE*, const G4Step* );
    void writeMirrorEv(FILE*, const G4Step* );
    void printParticleInfo(const G4Step* step);
    ExN02DetectorConstruction*    detector;
    ExN02EventAction*             eventaction;
    ExN02PrimaryGeneratorAction*  primaryAction;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
