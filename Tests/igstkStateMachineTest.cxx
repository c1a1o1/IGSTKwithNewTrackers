
#include "igstkStateMachine.h"

#include <iostream>


class Tester
{
public:

  typedef igstk::StateMachine< Tester, 4, 3 >   StateMachineType;

  friend StateMachineType;

  Tester()
    {
      // Connect the state machine to 'this' class.
      m_StateMachine.SetClass( this );

      // Programming the machine
      m_StateMachine.SetTransition( 0, 0, 1, 0 );
      m_StateMachine.SetTransition( 1, 0, 2, 0 );
      m_StateMachine.SetTransition( 2, 0, 3, 0 );
      m_StateMachine.SetTransition( 3, 0, 0, & Tester::CancelAndReturnChange );

      m_StateMachine.SetTransition( 0, 1, 0, & Tester::NoEnoughChangeMessage );
      m_StateMachine.SetTransition( 1, 1, 1, & Tester::NoEnoughChangeMessage );
      m_StateMachine.SetTransition( 2, 1, 2, & Tester::NoEnoughChangeMessage );
      m_StateMachine.SetTransition( 3, 1, 0, & Tester::DeliverDrink );

      m_StateMachine.SetTransition( 0, 2, 0, & Tester::CancelAndReturnChange );
      m_StateMachine.SetTransition( 1, 2, 0, & Tester::CancelAndReturnChange );
      m_StateMachine.SetTransition( 2, 2, 0, & Tester::CancelAndReturnChange );
      m_StateMachine.SetTransition( 3, 2, 0, & Tester::CancelAndReturnChange );

      // Finish the programming and get ready to run
      m_StateMachine.SetReadyToRun();
    }



  
  // Methods that generate input signals
  void InsertChange() 
    {
      m_StateMachine.SetInput( 0 );
      std::cout << "Insert Change" << std::endl;
      m_StateMachine.StateTransition();
    }
 
 
  void SelectDrink() 
    {
      m_StateMachine.SetInput( 1 );
      std::cout << "Select Drink" << std::endl;
      m_StateMachine.StateTransition();
    }

  void CancelPurchase() 
    {
      m_StateMachine.SetInput( 2 );
      std::cout << "Cancelling Purchase" << std::endl;
      m_StateMachine.StateTransition();
    }


protected:

  // Reaction methods that will be invoked during the 
  // state machine transitions. Note that this methods
  // are protected because they should only be called
  // from the state machine.
  void CancelAndReturnChange() 
    {
    std::cout << "Cancelling and returning Change" << std::endl;
    }


  void DeliverDrink()
    {
    std::cout << "Deliver Drink" << std::endl;
    }


  void NoEnoughChangeMessage()
    {
    std::cout << "You have not inserted enough change" << std::endl;
    }


private:

  StateMachineType   m_StateMachine;

};







int igstkStateMachineTest(int argc, char * argv [])
{

  Tester tester;


  std::cout << std::endl << std::endl;
  std::cout << "FIRST test run " << std::endl;

  // This is the cannonical path for using the class. 
  tester.InsertChange();
  tester.InsertChange();
  tester.InsertChange();
  tester.SelectDrink();




  std::cout << std::endl << std::endl;
  std::cout << "Second test run " << std::endl;

  // Try to get drink ealy on purpose, to test error states.
  tester.InsertChange();
  tester.SelectDrink();
  tester.InsertChange();
  tester.SelectDrink();
  tester.InsertChange();
  tester.SelectDrink();


  return EXIT_SUCCESS;

}


