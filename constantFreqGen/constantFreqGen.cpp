/**
*
*  @class ConstantFreqGen: generates output at a fixed frequency. 
*  @author Laouen Mayal Louan Belloli
*  @email laouen.belloli@gmail.com
*  @date 02/09/2016
*  
*/

#include <string>
#include "constantFreqGen.hpp"
#include "message.h"
#include "parsimu.h"

using namespace std;

ConstantFreqGen::ConstantFreqGen(const string &name) : 
  Atomic(name),
  start(addInputPort("start")),
	stop(addInputPort("stop")), 
  out(addOutputPort("out")),
  frequency_time(0,0,1,0),
  on(true) {
    cout << "constructor" << endl;
  }

/**
* Initializes a valid ConstantFreqGen model instance
* for this little model nothing must be initialized
*/

Model &ConstantFreqGen::initFunction() { 

  cout << "init" << endl;
  holdIn( AtomicState::active, this->frequency_time );
  return *this; 
}


/**
 * modifies the model internal state, acording with the current state, 
 * the input message and the elapsed time from the last state transition.
 */

Model &ConstantFreqGen::externalFunction( const ExternalMessage &msg ) {

  cout << "external" << endl;
  if (msg.port() == start) {
    this->on = true;
    holdIn( AtomicState::active, this->frequency_time );
  } else if (msg.port() == stop) {
    this->on = false;
    passivate();
  }

  return *this;
}

/**
 * Modifies the model internal state according with the internal transition logic of the model.
 * If the ConstantFreqGen is on, then a new output must be schedulled in frequency_time amount of time.
 * If the ConstantFreqGen is not on, must passivate.
 */
Model &ConstantFreqGen::internalFunction( const InternalMessage & ) {

  cout << "internal" << endl;
  if (this->on) {
    holdIn(AtomicState::active, this->frequency_time);
  } else {
   passivate();
  }

  return *this ;
}


/**
 * Returns allways the same output
 */
Model &ConstantFreqGen::outputFunction( const CollectMessage &msg ) {

  cout << "output" << endl;
  sendOutput( msg.time(), out, 1);
	return *this ;
}