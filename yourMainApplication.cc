#include <iostream>
#include "G4Types.hh"
#include "globals.hh"

#include "G4RunManager.hh"
#include "G4PhysListFactory.hh"

#include "YourDetectorConstruction.hh"
#include "YourPrimaryGeneratorAction.hh"
#include "YourActionInitialization.hh"

#include "G4UImanager.hh"
#include "G4UIExecutive.hh"

#include "G4VisManager.hh"
#include "G4VisExecutive.hh"

int main(int argc, char** argv) {
  
  // Detect interactive mode (if no arguments) and define UI: 
  G4UIExecutive* ui=0;
  if (argc ==1 ){
    ui = new G4UIExecutive(argc,argv, "qt");
  }

  //1. create the RunManager object 
  G4RunManager* runManager = new G4RunManager();
 
  //2. Create an object from YourDetectorConstruction and register in the Run-Manager
  YourDetectorConstruction* detector = new YourDetectorConstruction();
  runManager->SetUserInitialization( detector );
   
  //3. Create/obtain an Physics List and register it in the Run-Manager 
  G4PhysListFactory physListFactory;
  const G4String plName = "FTFP_BERT";
  G4VModularPhysicsList* pl = physListFactory.GetReferencePhysList( plName );
  runManager->SetUserInitialization( pl ); 
  
  //4. Create your action initizalizatio and register in the Run Manager:
  runManager->SetUserInitialization ( new YourActionInitialization( detector ) );
  
  // initialization of the run
  //  runManager->Initialize();  (comment if you use the UI manager)
 
  // add verbosity
  //  G4EventManager::GetEventManager()->GetTrackingManager()->SetVerboseLevel(1);
  //  G4UImanager* UI = G4UImanager::GetUIpointer();
  //  UI->ApplyCommand("/control/execute g4macro.mac");

  // visualization
  G4VisManager* visManager = new G4VisExecutive();
  visManager->Initialize();

  // Detect batch-mode: 
  G4UImanager* UImanager = G4UImanager::GetUIpointer();
  if (!ui) {
    G4String cmd = "/control/execute ";
    G4String scmd = argv[1];
    UImanager->ApplyCommand(cmd + scmd);
  } else {
    UImanager->ApplyCommand("/control/execute ../vis.mac");
    ui->SessionStart();
    delete ui;
  }
 
   
  // delete the Run-manager
  delete runManager; 
   
  return 0;
}
