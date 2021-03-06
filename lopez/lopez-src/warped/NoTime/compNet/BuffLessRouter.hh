#ifndef BUFF_LESS_ROUTER_HH
#define BUFF_LESS_ROUTER_HH

#include "SimulationObj.hh"
#include "Types.hh"
#include "BuffLessRouteState.hh"
#include "ConfigNet.hh"

#ifdef __GNUG__
#include <MLCG.h>
#include <Random.h>
#include <Normal.h>
#include <Poisson.h>
#include <Binomial.h>
#include <Uniform.h>
#include <NegExp.h>
#else
#include "../rnd/Random.h"
#include "../rnd/MLCG.h"
#include "../rnd/Normal.h"
#include "../rnd/Poisson.h"
#include "../rnd/Binomial.h"
#include "../rnd/Uniform.h"
#include "../rnd/NegExp.h"
#endif

class BuffLessRouter : public SimulationObj {
private:
  int index;
  Random *numGen;
  ConfigNet *netConf;
  int statDest;

  int maxQLen;
  int propDelay(int delayType);
  int servDelay();
  int getRouterId(int );
public:
  void initialize();
  void finalize();
  void setDistr();
  BuffLessRouter(int , ConfigNet*, int );
  ~BuffLessRouter();
  BasicState *allocateState();
  void executeProcess();
};

#endif
