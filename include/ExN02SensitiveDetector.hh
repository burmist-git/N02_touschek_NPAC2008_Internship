#ifndef SENSITIVEDETECTOR
#define SENSITIVEDETECTOR

#include <G4VSensitiveDetector.hh>
#include <G4RunManager.hh>

class G4Step;
class G4TouchableHistory;


class ExN02SensitiveDetector: public G4VSensitiveDetector
{
private:
    static const int NOBINS = 5000;
    const double HIST_MAX;
    const double HIST_MIN;
    int histogram[NOBINS];
    G4double Etot;
    G4RunManager *runManager;
public:
    G4int  evtID;
    void SetRunManager(G4RunManager *runMan) {runManager = runMan;};
    ExN02SensitiveDetector(G4String name);
    ~ExN02SensitiveDetector();
    G4bool ProcessHits(G4Step *step, G4TouchableHistory *hist);
    void EndOfEvent(G4HCofThisEvent*);
};

#endif /* SENSITIVEDETECTOR */
