#include "main.h"
#include  "autonomous.h"

//sheesh
//dogrpog
void leftBtn(){

}
void centerBtn(){

}
void rightBtn(){

}

void initialize() {
	pros::lcd::initialize();
	pros::lcd::register_btn0_cb(leftBtn);
	pros::lcd::register_btn1_cb(centerBtn);
	pros::lcd::register_btn2_cb(rightBtn);
	fBar.set_brake_mode(MOTOR_BRAKE_HOLD);
	fClamp.set_value(true);
	tilt.set_value(true);

  autonSelector();
	//autonSelector();
}


void disabled() {}

void competition_initialize() {}

void autonomous() {
  switch(selected){
    case 0:

		break;
    case 1:

		break;
	case 2:

		break;
	case 3:

		break;
	case 4:

		break;
	case 5:

		break;
	case 6:

		break;
	case 7:

		break;
	case 8:

		break;
	default:
		return;
   }
}

const int NUM_HEIGHTS = 3;
const int height1 = 0;
const int height2 = 700;
const int height3 = 1500;
double spd=-2;

const int heights[NUM_HEIGHTS] = {height1, height2,height3};
const int heights2[NUM_HEIGHTS] = {0, 700,1800};

int x = 0;


bool climb=0;
std::string cToggle = "cover";

double GetMaxTemperature() {
	std::vector<double> temps;
	std::vector<std::string> motor{"FL", "FR", "LM", "RM", "BL", "BR", "4B","IN"};
	temps.push_back(FrontLeft.get_temperature());
	temps.push_back(FrontRight.get_temperature());
	temps.push_back(MiddleLeft.get_temperature());
	temps.push_back(MiddleRight.get_temperature());
	temps.push_back(BackLeft.get_temperature());
	temps.push_back(BackRight.get_temperature());
	temps.push_back(fBar.get_temperature());
	temps.push_back(intake.get_temperature());


	double max_temp = temps[0];
	int idx = 0;
	for (int i = 1; i < temps.size(); i++) {
		if (temps[i] > max_temp) {
			max_temp = temps[i];
			idx = i;
		}
	}
	std::string s = "MaxTemp: " + std::to_string(max_temp);
	control.print(0, 1, "MaxTemp: %.1f, %s", max_temp, motor[idx]);

	pros::lcd::print(0, "MaxTemp: %.1f", max_temp);
  return max_temp;
}

double cTime = 0;
double tTime=0;
double itime=0;
double sTime=0;

void opcontrol() {
	master.clear();
	control.clear();
	fBar.set_brake_mode(MOTOR_BRAKE_HOLD);
 	int goalHeight = 0;
	int bGoalHeight = 0;
	double multiplier = 2;
	fBar.set_zero_position(0);

	bool cToggle = false;
	bool tToggle = false;
	bool iToggle=false;
	bool sToggle=false;


  while (true){
	GetMaxTemperature();
	auto power = control.get_analog(ANALOG_RIGHT_Y);
	auto turn= control.get_analog(ANALOG_LEFT_X);
	driverControl(0.95*multiplier*power+0.3*multiplier*turn, 0.95*multiplier*power-0.3*multiplier*turn);




		if (control.get_digital(E_CONTROLLER_DIGITAL_L2) && millis()-cTime > 300){
		if(!cToggle){
			fClamp.set_value(false);
			cToggle = true;
		} else {
			fClamp.set_value(true);
			cToggle = false;
		}
		cTime = millis();
		

	}

		if (control.get_digital(E_CONTROLLER_DIGITAL_L1) && millis()-tTime > 300){
		if(!cToggle){
			tilt.set_value(false);
			tToggle = true;
		} else {
			tilt.set_value(true);
			tToggle = false;
		}
		tTime = millis();
		

	}

		if (control.get_digital(E_CONTROLLER_DIGITAL_UP) && millis()-itime > 1000){
			if(!iToggle){
				intake.move(100);
				iToggle = true;
			} else {
				intake.move(-100);
				iToggle = -false;
			}
			itime = millis();
		}
		if (control.get_digital(E_CONTROLLER_DIGITAL_RIGHT) && millis()-sTime > 1000){
			if(!iToggle){
				multiplier=0.4;
				BackRight.set_brake_mode(MOTOR_BRAKE_HOLD);
				BackLeft.set_brake_mode(MOTOR_BRAKE_HOLD);
				FrontLeft.set_brake_mode(MOTOR_BRAKE_HOLD);
				FrontRight.set_brake_mode(MOTOR_BRAKE_HOLD);
				MiddleRight.set_brake_mode(MOTOR_BRAKE_HOLD);
				MiddleLeft.set_brake_mode(MOTOR_BRAKE_HOLD);
				sToggle = true;
			} else {
			multiplier=2;
				BackRight.set_brake_mode(MOTOR_BRAKE_COAST);
				BackLeft.set_brake_mode(MOTOR_BRAKE_COAST);
				FrontLeft.set_brake_mode(MOTOR_BRAKE_COAST);
				FrontRight.set_brake_mode(MOTOR_BRAKE_COAST);
				MiddleRight.set_brake_mode(MOTOR_BRAKE_COAST);
				MiddleLeft.set_brake_mode(MOTOR_BRAKE_COAST);
				iToggle = false;
			}
			sTime = millis();
		}		
//upd
		if (control.get_digital(E_CONTROLLER_DIGITAL_R1)) {
			intake.move_velocity(0);
		}
	if (control.get_digital(E_CONTROLLER_DIGITAL_R1)) {
		fBar.move_velocity(200);

	} else if (control.get_digital(E_CONTROLLER_DIGITAL_R2)) {
  		fBar.move_velocity(-200);
	} else {
  		fBar.move_velocity(0);
	}

	if(control.get_digital(E_CONTROLLER_DIGITAL_R1)){
		tilt.set_value(false);
	} else if (control.get_digital(E_CONTROLLER_DIGITAL_R2)){
		tilt.set_value(true);
	}



	pros:delay(5);

  }
}