#ifndef ExN02MaterialConstruction_h
#define ExN02MaterialConstruction_h 1

#include "globals.hh"

class G4Material;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class ExN02MaterialConstruction
{
public:
    
    ExN02MaterialConstruction();
    ~ExN02MaterialConstruction();
    
public:
    
    G4Material* ConstructAir();
    G4Material* ConstructLead();
    G4Material* ConstructAluminium();
    G4Material* ConstructBeamVacuum();
    G4Material* ConstructSmCo();
    G4Material* ConstructXenon();
    G4Material* ConstructPVC();
    G4Material* ConstructPbWO();
    G4Material* ConstructIron();
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
