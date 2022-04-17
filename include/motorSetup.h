#include "main.h"
#include "pid.h"
#include "driveTrain.h"

using namespace pros;

const double ticksPerDeg = 900/360;
const double robotSpeed = 200;
const double rotationSpeed = 200;

extern pros::Motor FrontLeft;
extern pros::Motor FrontRight;
extern pros::Motor BackLeft;
extern pros::Motor BackRight;
extern pros::Motor MiddleRight;
extern pros::Motor MiddleLeft;



const int FLPort = 15;
const int FRPort = 9;

const int MLPort = 17;
const int MRPort = 18;

const int BLPort = 19;
const int BRPort = 12;

const int FBPort = 7;
const int IP = 16;
//sensors
//const int IMUPort = 17;
//const int DistPort = 5;


pros::Controller control (pros::E_CONTROLLER_MASTER);

ControllerButton RUp(ControllerDigital::R1);
ControllerButton RDown(ControllerDigital::R2);
ControllerButton LUp(ControllerDigital::L1);
ControllerButton LDown(ControllerDigital::L2);
ControllerButton A(ControllerDigital::A);
ControllerButton B(ControllerDigital::B);
ControllerButton X(ControllerDigital::X);
ControllerButton Y(ControllerDigital::Y);
ControllerButton left(ControllerDigital::left);
ControllerButton right(ControllerDigital::right);
ControllerButton up(ControllerDigital::up);
ControllerButton down(ControllerDigital::down);


pros::Motor FrontLeft(FLPort, false);
pros::Motor FrontRight(FRPort, true);
pros::Motor MiddleLeft(MLPort, false);
pros::Motor MiddleRight(MRPort, true);
pros::Motor BackLeft(BLPort, false);
pros::Motor BackRight(BRPort, true);
pros::Motor fBar(FBPort, true);
pros::Motor intake(IP, true);

pros::ADIDigitalOut tilt ('A');
//pros::ADIDigitalOut bClamp ('B');
pros::ADIDigitalOut fClamp ('H');

driveTrain drive = driveTrain(3.25, 11.5);

pidController autonlinear = pidController(0, 0.002, 0, 0.0001);
//pros::Imu inertial(IMUPort);
//pros::Distance distance(DistPort);
/*
pros::Motor LeftIntake(LIPort, false);
pros::Motor RightIntake(RIPort, true);
pros::Motor BackRoller(LRPort, true);
pros::Motor MainRoller(RRPort, true);
pros::Imu inertial(IMUPort);

ADIEncoder yWheel('C', 'D', true);
ADIEncoder xWheel('A', 'B', false);
//Calibrate the sensors
void calibrateSensors(){
  xWheel.reset();
  yWheel.reset();
  inertial.reset();
  int timeInit = pros::millis();
  inertial.reset();
  while(inertial.is_calibrating()){
    lcd::print(1, "Calibrating");
    delay(10);
  }
  delay(2000);
  lcd::print(1, "Calibration took %f", millis() - timeInit);
}*/