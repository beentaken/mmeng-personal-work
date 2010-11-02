#ifndef COMMAND_H
#define COMMAND_H

class TimedCommand {
	double when;
	public:
	virtual void Execute() = 0;
	virtual void SetWhen( double _when ) { when=_when; }
	virtual double When() const          { return when; }
	bool operator < (const TimedCommand& rhs ) const {
		return when>rhs.when; //reversed, so earlier time is at the top
	}
	virtual ~TimedCommand() {}
};

#endif

