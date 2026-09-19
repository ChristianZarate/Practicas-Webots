
#include <webots/Robot.hpp>
#include <webots/Motor.hpp>

using namespace webots;

int main(int argc, char **argv) {

  Robot *robot = new Robot();

  // get the time step of the current world.
  int timeStep = (int)robot->getBasicTimeStep();

  // You should insert a getDevice-like function in order to get the
  // instance of a device of the robot. Something like:
  Motor *motor = robot->getMotor("MOTOR1");
  motor->setPosition(INFINITY);
  //  DistanceSensor *ds = robot->getDistanceSensor("dsname");
  //  ds->enable(timeStep);


  while (robot->step(timeStep) != -1) {

    // Read the sensors:
    // Enter here functions to read sensor data, like:
    //  double val = ds->getValue();

    motor->setVelocity(10.0);
  };

  // Enter here exit cleanup code.

  delete robot;
  return 0;
}
