// File:          pendulo_pid.cpp
// Practica 4:    Pendulo - control PID hecho a mano (sin usar setControlPID)
// Author:        Christian
//
// Idea: el pendulo cuelga de un HingeJoint. Queremos que se quede quieto
// en un angulo objetivo (setpoint) aplicando TORQUE calculado con un PID
// clasico:  u(t) = Kp*e + Ki*integral(e) + Kd*d(e)/dt
//
// El motor se pone en modo "torque control": setPosition(INFINITY) y luego
// en cada paso se manda setTorque(u).

#include <webots/Robot.hpp>
#include <webots/Motor.hpp>
#include <webots/PositionSensor.hpp>
#include <cmath>
#include <iostream>

using namespace webots;

int main(int argc, char **argv) {
  Robot *robot = new Robot();
  int timeStep = (int)robot->getBasicTimeStep();

  Motor *motor = robot->getMotor("pendulum_motor");
  PositionSensor *sensor = robot->getPositionSensor("pendulum_sensor");
  sensor->enable(timeStep);

  // Modo torque: se libera la posicion y controlamos con setTorque()
  motor->setPosition(INFINITY);
  motor->setVelocity(0.0);

  // ---- Ganancias del PID (ajustalas si oscila mucho o se queda corto) ----
  const double Kp = 25.0;
  const double Ki = 0.5;
  const double Kd = 4.0;

  // Angulo objetivo en radianes. 0 = colgando hacia abajo (reposo natural).
  // Se pide que se sostenga a -1.0 rad (~57 grados) para que se note el PID.
  const double setpoint = -1.0;

  double integral = 0.0;
  double previousError = 0.0;
  double dt = timeStep / 1000.0; // segundos

  while (robot->step(timeStep) != -1) {
    double currentAngle = sensor->getValue();

    double error = setpoint - currentAngle;

    integral += error * dt;
    // anti-windup simple: limitar la integral
    if (integral > 10.0) integral = 10.0;
    if (integral < -10.0) integral = -10.0;

    double derivative = (error - previousError) / dt;

    double output = Kp * error + Ki * integral + Kd * derivative;

    // limitar el torque para no pasarnos del maxTorque del motor (100)
    if (output > 90.0) output = 90.0;
    if (output < -90.0) output = -90.0;

    motor->setTorque(output);

    previousError = error;

    // debug opcional
    // std::cout << "angulo=" << currentAngle << " error=" << error
    //           << " torque=" << output << std::endl;
  }

  delete robot;
  return 0;
}
