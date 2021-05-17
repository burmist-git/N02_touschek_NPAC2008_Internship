//***************************
// 07.06.08  
//***************************
#include "ExN02MaterialConstruction.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"

 #include "G4ProductionCutsTable.hh"

ExN02MaterialConstruction::ExN02MaterialConstruction(){
}

ExN02MaterialConstruction::~ExN02MaterialConstruction(){
}

G4Material* ExN02MaterialConstruction::ConstructAir(){
    //Air

    /*  
	G4Element* N = new G4Element("Nitrogen", "N", 7., 14.01*g/mole);a 
	G4Element* O = new G4Element("Oxygen"  , "O", 8., 16.00*g/mole);
	G4Material* Air = new G4Material("Air", 1.25*mg/cm3, 2);
	Air->AddElement(N, 70*perCent);
	Air->AddElement(O, 30*perCent);
    */
    
    G4NistManager* man = G4NistManager::Instance();
    G4Material *Air = man->FindOrBuildMaterial("G4_AIR"); 

    return Air;
}

G4Material* ExN02MaterialConstruction::ConstructLead(){
    //Lead
    G4Material* Pb = 
 	new G4Material("Lead", 82., 207.19*g/mole, 11.35*g/cm3);

    return Pb;
}

G4Material* ExN02MaterialConstruction::ConstructAluminium(){
    //Aluminium
    G4Material* Alum = 
	new G4Material("Aluminium", 13., 26.98*g/mole, 2.700*g/cm3);

    return Alum;
}

G4Material* ExN02MaterialConstruction::ConstructBeamVacuum(){
    //Vacuum fo the beampipe
    //density     = 1.e-11*g/cm3
    //pressure    = 2.e-11*bar
    //temperature = STP_Temperature  //from PhysicalConstants.h
    G4Material* BeamVacuum = new G4Material("BeamVacuum ", 1.e-11*g/cm3, 1,
					     kStateGas,STP_Temperature,2.e-11*bar);
    BeamVacuum->AddMaterial(ConstructAir(), 1);
  
    return BeamVacuum;
}

G4Material* ExN02MaterialConstruction::ConstructSmCo(){
    //Sm2CO17

    G4Element* Sm = new G4Element("Samarium","Sm", 62., 150.36*g/mole);
    G4Element* Co =  new G4Element("Cobalt"  ,"Co" , 27., 58.933*g/mole);
    G4double density = 8.4*g/cm3;
 
     G4Material* SMCO = new G4Material("SMCO",density,2);
    SMCO->AddElement(Sm, 2);
    SMCO->AddElement(Co, 17);
    //G4cout<<SMCO<<G4endl;
    return SMCO;
}

G4Material* ExN02MaterialConstruction::ConstructXenon(){
    //Xenon gas
    G4Material* Xenon = 
	new G4Material("XenonGas", 54., 131.29*g/mole, 5.458*mg/cm3,
		       kStateGas, 293.15*kelvin, 1*atmosphere);
    return Xenon;
}

G4Material* ExN02MaterialConstruction::ConstructPVC(){
    //For the photon calorimeter
    G4Element* H = new G4Element("Hydrogen","H" , 1., 1.01*g/mole);
    G4Element* C = new G4Element("Carbon","C" , 6., 12.01*g/mole);
    G4Element* Cl = new G4Element("Chlotine","Cl" , 17., 35.453*g/mole);
    G4double density = 1.3*g/cm3;
    G4Material* PVC = new G4Material("PVC",density,3);
    // PVC->AddElement(el1, 4.838*perCent);
    // PVC->AddElement(el2, 38.436*perCent);
    // PVC->AddElement(el3, 56.726*perCent);
    PVC->AddElement(H, 3);
    PVC->AddElement(C, 2);
    PVC->AddElement(Cl,1);

    // G4ProductionCutsTable::GetProductionCutsTable()->SetEnergyRange(1.01*GeV, 10*GeV);

    return PVC;
}

G4Material* ExN02MaterialConstruction::ConstructPbWO(){
    //Photon detector scinlilator PbWO4
    G4Element* Pb = new G4Element("lead","Pb" , 82., 207.2*g/mole);
    G4Element* W = new G4Element("Wan","W" , 74., 183.85*g/mole);
    G4Element* O = new G4Element("Oxygen","O" , 8., 16.0*g/mole);
    G4double density = 8.28*g/cm3;
 
    G4Material* PbWO = new G4Material("PbWO",density,3);
    //PbWO->AddElement(Pb, 100./6*perCent);
    //PbWO->AddElement(W, 100./6*perCent);
    //PbWO->AddElement(O, 400./6*perCent);
    PbWO->AddElement(Pb, 1);
    PbWO->AddElement(W, 1);
    PbWO->AddElement(O, 4);
    
    return PbWO;
}

G4Material* ExN02MaterialConstruction::ConstructIron(){
    //Photon detector skin 
    G4Element* el1 = new G4Element("el1","el1" , 26., 55.845*g/mole);
    G4double density = 7.874*g/cm3;
    G4Material* Iron = new G4Material("Iron",density,1);
    Iron->AddElement(el1, 1);
    return Iron;
}
