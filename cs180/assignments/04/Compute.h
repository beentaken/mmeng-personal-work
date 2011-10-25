// Compute.h
// -- interface for dot position updater
// cs180 2/08

#ifndef CS180_COMPUTE
#define CS180_COMPUTE


class Compute {
  public:
    Compute(void);
    ~Compute(void);
    void operator()(double& x, double& y);
  private:
    int current_time;
    double offset;
    double position_x, position_y;
    double velocity_x, velocity_y;
};


#endif
