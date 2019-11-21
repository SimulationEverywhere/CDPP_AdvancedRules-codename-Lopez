/**
*
*  @class ConstantFreqGen: generates output at a fixed frequency. 
*  @author Laouen Mayal Louan Belloli
*  @email laouen.belloli@gmail.com
*  @date 02/09/2016
*  
*/
#ifndef CONSTAN_FREQ_GEN
#define CONSTAN_FREQ_GEN

#include <list>
#include "atomic.h"
#include "VTime.hh"

using namespace std;

class ConstantFreqGen : public Atomic {
  public:
    
    ConstantFreqGen(const string &name = "ConstantFreqGen" );
    virtual string className() const {  return "ConstantFreqGen" ;}
  
  protected:
    Model &initFunction();
    Model &externalFunction( const ExternalMessage & );
    Model &internalFunction( const InternalMessage & );
    Model &outputFunction( const CollectMessage & );

  private:
    const Port &start;
    const Port &stop;
    Port &out;

    VTime frequency_time;
    bool on;
};

#endif   //CONSTAN_FREQ_GEN
