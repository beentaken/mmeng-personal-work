#include "simulator.h"
#include "announcer-repeater-example.h"

//compile make example

int main() {
	Simulator sim;
	Announce ann("HEAR HEAR -- ");
  sim.AddEvent( new AnnounceEvent(3.0,&ann,&Announce::DoWork) );
  sim.AddEvent( new AnnounceEvent(2.0,&ann,&Announce::DoWork) );
  sim.AddEvent( new AnnounceEvent(5.0,&ann,&Announce::DoWork) );
  sim.AddEvent( new AnnounceEvent(1.0,&ann,&Announce::DoWork) );
	sim.Start();

	//slightly more interesting 
	Simulator sim2;
	Repeater rep(&sim2,"I repeat");
  sim2.AddEvent( 
			new RepeatingEvent(6.0,&rep,&Repeater::ContinueRepeating,10,0.3) );
  sim2.AddEvent( 
			new RepeatingEvent(5.0,&rep,&Repeater::ContinueRepeating,5,0.8) );
	sim2.Start();
}
