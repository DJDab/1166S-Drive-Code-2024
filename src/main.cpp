#include "main.h"
#include "initialize.h"
#include "string"


/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "if you are reading this and your name is");
	pros::lcd::set_text(2, "not gavin look away");
	pros::lcd::set_text(5, "gavin is bezdziewczyna");

	pros::lcd::register_btn1_cb(on_center_button);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
elevationMain.set_value(false);
rightMatchload.set_value(false);
leftMatchload.set_value(false);
driveMain.set_brake_modes(MOTOR_BRAKE_COAST);
blockerMain.set_brake_modes(MOTOR_BRAKE_HOLD);
blockerMain.brake();

}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {

	inert.reset();
	rightDriveRear.tare_position();

	while(true){

		//using buttons on screen to select auton
		if (pros::lcd::read_buttons() == 2){
			//near auton
			autoPick = 1;
			inert.reset();
			pros::lcd::set_text(1,"near auton");
		}else if(pros::lcd::read_buttons() == 4){
			//far auton
			autoPick = 2;
			inert.reset();
			pros::lcd::set_text(1,"far auton");
		}else if(pros::lcd::read_buttons() == 1){
			//auton skills
			autoPick = 3;
			inert.reset();
			pros::lcd::set_text(1,"auton skills");
		}

		pros::delay(100);


	}

	
}


/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {


	autoPick = 3;

	//close side auton
	if (autoPick == 1){	

		inert.tare();
		

		driveRight.move(-110);
		driveLeft.move(-40);
		pros::delay(2000);
		driveLeft.move(-100);
		driveMain.brake();

		//getting matchload
		driveRight.move(120);
		driveLeft.move(40);
		pros::delay(700);
		
		driveRight.move(50);
		driveLeft.move(30);
		pros::delay(100);
		rightMatchload.set_value(true);
		pros::delay(400);
		driveRight.move(90);
		driveLeft.move(20);
		pros::delay(600);
		driveMain.brake();

		//YAHOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO moment
		driveMain.set_brake_modes(MOTOR_BRAKE_BRAKE);

		driveMain.move(120);
		pros::delay(400);
		driveMain.brake();

		driveMain.move(-40);
		pros::delay(500);
		driveMain.brake();

		

		rightMatchload.set_value(false);
		driveRight.move(40);
		pros::delay(100);
		driveMain.brake();

		

		driveRight.move(127);
		driveLeft.move(-127);
		pros::delay(750);
		driveMain.brake();
		driveRight.move(127);
		driveLeft.move(-127);
		pros::delay(250);
		pros::delay(250);
		driveMain.brake();
		pros::delay(200);

		master.print(0,0,"touchy");
		rightMatchload.set_value(false);

		

		//touchy touchy eleveation pole
		
		driveRight.move(50);
		driveLeft.move(-50);
		waitUntil((inert.get_heading() >= 310) && (inert.get_heading() <= 320));
		driveMain.brake();
		pros::delay(50);
		driveMain.move(-127);
		pros::delay(450);
		driveMain.brake();
		driveLeft.move(50);
		driveRight.move(-50);
		waitUntil((inert.get_heading() >= 230) && (inert.get_heading() <= 240));
		driveMain.brake();

		pros::delay(100);
		
		driveMain.move(-100);
		pros::delay(500);
		driveMain.brake();
		driveMain.move(-75);
		pros::delay(500);
		driveMain.brake();
		driveMain.move(-30);
		pros::delay(150);
		driveMain.brake();
		leftMatchload.set_value(true);

		driveMain.set_brake_modes(MOTOR_BRAKE_BRAKE);

		driveMain.move(-25);
		pros::delay(400);
		driveMain.brake();
		driveMain.move(-25);
		pros::delay(400);
		driveMain.brake();
		
		

		

		
		


	//far side auton
	}else if (autoPick == 2){

		inert.tare();
		

		pros::delay(50);

		//moving backward and forwards to release intake and grab triball
		blockerMain.move(100);
		pickupMain.move(-127);
		pros::delay(400);
		blockerMain.brake();
		driveMain.move_relative(90,100);
		pros::delay(200);
		driveMain.move(-50);
		pros::delay(150);
		driveMain.move(-127);
		pros::delay(600);
		driveMain.brake();
		pros::delay(50);
		driveLeft.move(-60);
		driveRight.move(5);
		pros::delay(500);
		driveMain.brake();

		//reteaving the triball in the matchload zone
		leftMatchload.set_value(true);
		driveMain.move(-127);
		pros::delay(50);
		driveMain.brake();
			// pushes triball out of match loader and turns
		driveRight.move(-19);
		driveLeft.move(-127);
		pros::delay(300);
		driveMain.brake();
			//turns tword goal
		leftMatchload.set_value(false);
		driveRight.move(-20);
		driveLeft.move(-100);
		pros::delay(600);
		driveMain.brake();
		pros::delay(100);
		
			//moves to goal with triballs
		
		
		driveMain.move(-127);
		pros::delay(600);
		driveMain.brake();
		pros::delay(50);
		// moves away from goal
		driveMain.move(127);
		pros::delay(300);
		leftMatchload.set_value(false);
		driveMain.brake();
		pros::delay(50);
		driveRight.move(50);
		driveLeft.move(-50);
		waitUntil((inert.get_heading() >= 115) && (inert.get_heading() <= 125));
		driveMain.brake();
		
/*
		//pushing both tirballs into the goal
		driveMain.move(-127);
		pros::delay(500);
		driveMain.brake();
		driveMain.move(60);
		pros::delay(500);
		driveMain.brake();
		leftMatchload.set_value(false);
		driveRight.move(50);
		driveLeft.move(-50);

		//turing twords the center bar
		waitUntil((inert.get_heading() >= 135) && (inert.get_heading() <= 145));
		driveMain.brake();*/
		/*
		leftMatchload.set_value(false);
		rightMatchload.set_value(false);
		pros::delay(50);
*/
		driveMain.move(-80);
		pros::delay(800 );
		driveMain.brake();

		//turing in circle and releasing triball at certain angle
		driveRight.move(55);
		driveLeft.move(-55);
		waitUntil((inert.get_heading() >= 190) && (inert.get_heading() <= 200));
		pros::delay(250);
		pickup.move(127);
		pros::delay(500);
		pickup.move(-127);
		
		//pointing twords triball at left of centerbar and picking it up
		driveRight.move(50);
		driveLeft.move(-50);
		waitUntil((inert.get_heading() >= 350) && (inert.get_heading() <= 359));
		driveMain.brake();
		pros::delay(50);
		driveMain.move(70);
		pros::delay(600);
		driveMain.brake();
		pros::delay(50);
		driveMain.move_relative(-360,-127);
		pros::delay(200);
		driveRight.move(-50);
		driveLeft.move(50);

		//turning and releasing triball
		waitUntil((inert.get_heading() >= 225) && (inert.get_heading() <= 235));
		driveMain.brake();
		pros::delay(250);
		pickup.move(127);
		pros::delay(300);
		pickup.brake();
		pros::delay(50);
		driveRight.move(60);
		driveLeft.move(-60);

		//pointing and driving to center line
		waitUntil((inert.get_heading() >= 70) && (inert.get_heading() <= 80));
		driveMain.brake();
		leftMatchload.set_value(true);
		rightMatchload.set_value(true);
		pros::delay(50);
		driveMain.move(-120);
		pros::delay(300);
		driveMain.brake();
		pros::delay(50);
		rightMatchload.set_value(true);
		driveLeft.move(40);
		driveRight.move(-70);

		//turning twords goal and driving triballs into goal
		waitUntil((inert.get_heading() >= 5) && (inert.get_heading() <= 15))
		driveMain.brake();
		pros::delay(50);
		driveMain.move(-127);
		pros::delay(600);
		driveMain.brake();
		pros::delay(50);
		leftMatchload.set_value(false);
		rightMatchload.set_value(false);

		//driving to elevation bar (might cut out because of the nto having enought time to get to bar)
		blockerMain.set_brake_modes(MOTOR_BRAKE_HOLD);
		blockerMain.move(127);
		driveRight.move(127);
		driveLeft.move(42);
		pros::delay(1100);
		blockerMain.brake();
		driveMain.move(127);
		pros::delay(300);
		driveMain.brake();
		driveRight.move(-127);
		driveLeft.move(127);
		pros::delay(250);
		driveMain.brake();


		

		

		




		/*
		driveMain.move(-60);
		pros::delay(200);
		driveMain.brake();	
		pros::delay(50);
		driveMain.move(60);
		pros::delay(200);
		driveMain.brake();
		pros::delay(50);

		driveMain.move_relative(320*2,100);
		pros::delay(100);
		rightMatchload.set_value(true);
		pros::delay(1000);
		driveRight.move_relative(360*4,50);
		driveLeft.move_relative(-360*2.5,-10);
		pros::delay(1000);
		driveMain.move_relative(360,100);
		rightDrive.move_relative(360*3,100);
		leftDrive.move_relative(-360*3,-100);
		rightMatchload.set_value(false);
		pros::delay(1000);
		
		driveMain.move(-127);
		
		pros::delay(150);
		driveMain.brake();
		driveMain.move(127);
		pros::delay(90);
		driveMain.brake();

		
		/*pros::delay(500);
		rightDrive.move_relative(360*6,100);
		leftDrive.move_relative(-360*6,100);
		pickup.move_relative(360*50,100);
		leftMatchload.set_value(1);
		
		pros::delay(300);

		driveMain.set_brake_modes(MOTOR_BRAKE_BRAKE);

		driveRight.move(100);
		driveLeft.move(-100);
		
		
		pros::delay(250);
		driveMain.brake();

		leftMatchload.set_value(true);
		pros::delay(500);
		driveMain.move(-127);
		pros::delay(500);
		driveMain.brake();



		//touchy touchy with elevation stick

		

		driveMain.move(30);
		pros::delay(250);
		driveMain.brake();

		leftMatchload.set_value(false);

		pros::delay(100);

		driveLeft.move(-40);
		driveRight.move(40);

		waitUntil((inert.get_heading() >= 58) && (inert.get_heading() <= 68))

		driveMain.brake();
		
		driveMain.move(-40);
		pros::delay(2000);
		
		pros::delay(1500);
		driveMain.brake();
		rightMatchload.set_value(true);

		//driveLeft.move_relative(180,50);

		*/








	//auton skills
	}else if(autoPick == 3){

		inert.tare();
		
		
		launcherMain.set_brake_modes(MOTOR_BRAKE_COAST);
		blockerMain.set_brake_modes(MOTOR_BRAKE_COAST);

		//freeing the intake
		blockerMain.move(100);
		pros::delay(200);
		blockerMain.brake();

		//catapult
		driveLeft.move(-80);
		driveRight.move(-40);
		pros::delay(525);
		driveMain.brake();
		pros::delay(50);
		driveMain.set_brake_modes(MOTOR_BRAKE_HOLD);
		launcherMain.move(127);
		//pros::delay(28000);
		pros::delay(2500);
		launcherMain.brake();
		pros::delay(100);
		driveMain.set_brake_modes(MOTOR_BRAKE_BRAKE);
		pros::delay(200);
		inert.set_heading(20.5);

		

		//drive to otherside of field
		driveMain.move(127);
		pros::delay(200);
		driveMain.brake();
		pros::delay(50);
		driveLeft.move(-50);
		driveRight.move(50);
		waitUntil((inert.get_heading() >= 140) && (inert.get_heading() <= 150))
		driveMain.brake();
		pros::delay(100);

		launcherMain.set_brake_modes(MOTOR_BRAKE_HOLD);
		launcherMain.move(127);
		pros::delay(300);
		launcherMain.brake();

		driveLeft.move(-110);
		driveRight.move(-82.5);
		pros::delay(500);
		driveRight.move(-100);
		pros::delay(1650);
		driveMain.brake();
		rightMatchload.set_value(1);

		launcherMain.set_brake_modes(MOTOR_BRAKE_COAST);
		pros::delay(100);

		driveLeft.move(-105);
		driveRight.move(-25);
		pros::delay(500);
		driveRight.move(-30);
		pros::delay(450);	
		driveRight.move(-100);
		pros::delay(500);

		//right side of goal double
		driveMain.move(60);
		pros::delay(500);
		driveRight.move(-60);
		driveLeft.move(-127);
		pros::delay(1000);
		driveMain.brake();

		//right side of goal triple
		rightMatchload.set_value(false);
		leftMatchload.set_value(false);
		driveMain.move(60);
		pros::delay(500);
		driveRight.move(-127);
		driveLeft.move(-60);
		pros::delay(700);
		driveMain.brake();

		//right side of goal quadrouple
		driveMain.move(60);
		pros::delay(500);
		driveRight.move(-60);
		driveLeft.move(-127);
		pros::delay(700);
		driveMain.brake();

		

		//right side of goal quintuple
		driveMain.move(60);
		pros::delay(500);
		driveRight.move(-127);
		driveLeft.move(-127);
		pros::delay(700);
		driveMain.brake();
		leftMatchload.set_value(true); 


		//80 230 to face goal

		//moving to front of goal
		driveMain.move(100);
		pros::delay(195);
		driveMain.brake();
		pros::delay(100);
		rightMatchload.set_value(0);
		pros::delay(100);
		driveRight.move(50);
		driveLeft.move(-50);
		waitUntil(inert.get_heading() >= 325 && inert.get_heading() <= 335);
		rightMatchload.set_value(1);
		driveMain.brake();
		pros::delay(50);
		driveLeft.move(-65);
		driveRight.move(-90);
		pros::delay(1400);
		driveMain.brake();
		pros::delay(50);
		driveRight.move(-55);
		driveLeft.move(55);
		waitUntil(inert.get_heading() >= 205 && inert.get_heading() <=215);
		driveMain.brake();

		//pushing into goal
		rightMatchload.set_value(true);
		leftMatchload.set_value(true);
		driveMain.move(-127);
		pros::delay(1500);
		driveMain.brake();
		pros::delay(100);

		//pushing into goal 2

		rightMatchload.set_value(false);

		driveRight.move(127);
		driveLeft.move(127);
		pros::delay(500);
		driveMain.brake();
		pros::delay(100);
		driveRight.move(50);
		driveLeft.move(-50);

		//reverses out of goal and turns 90 degrees and drives forewards and turns twrods goal and pushes in.
		waitUntil(inert.get_heading() >= 265 && inert.get_heading() <= 275);
		rightMatchload.set_value(true);
		driveMain.brake();
		pros::delay(50);
		driveMain.move(-80);
		pros::delay(500);
		driveMain.brake();
		pros::delay(50);
		driveRight.move(-60);
		driveLeft.move(50);
		waitUntil(inert.get_heading() >= 185 && inert.get_heading() <=195);
		driveMain.brake();

		rightMatchload.set_value(true);

		driveMain.move(-127);
		pros::delay(1500);
		driveMain.brake();
		pros::delay(100);

		//backing from goal
		driveMain.move(127);
		pros::delay(500);
		driveMain.brake();

		//driving to left goal
		leftMatchload.set_value(false);
		rightMatchload.set_value(false);
		driveRight.move(40);
		driveLeft.move(-40);
		waitUntil(inert.get_heading() >= 220 && inert.get_heading() <= 230);
		driveMain.brake();
		rightMatchload.set_value(false);
		pros::delay(50);





		









	}else if(autoPick = 4){
		//turns tword long barrier 
		myPIDinert(300, inert.get_heading(), 0);
		pros::delay(500);
		waitUntil(pidRun==false);

		//moves tword triball on long barrier
		myPID(-1360, rightDriveRear.get_position());
		pros::delay(500); 
		waitUntil(pidRun==false);
        
		pros::lcd::set_text(1,"balls");
		myPIDinert(270, inert.get_heading(), 0);
		pros::lcd::set_text(2,"balls 2.0");
		pros::delay(500);
		waitUntil(pidRun==false);
		pros::lcd::set_text(3,"balls 3.0");
/*
		myPIDinert(230, inert.get_heading(), 0);
		pros::delay(500);
		waitUntil(pidRun==false);
		
		myPID(230, rightDriveRear.get_position());
		pros::delay(500);
		waitUntil(pidRun == false);

		myPIDinert(265, inert.get_heading(), 0);
		pros::delay(500);
		waitUntil(pidRun==false);

		myPID(-950, rightDriveRear.get_position());
		pros::delay(500);
		waitUntil(pidRun == false);
		
		myPIDinert(85, inert.get_heading(), 0);
		pros::delay(500);
		waitUntil(pidRun == false);

		myPID(-1000, rightDriveRear.get_position());
		pros::delay(500);
		waitUntil(pidRun == false);
*/
	}
	

	
	



}// end of auton

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	
	all.move_velocity(100);

	blockerMain.set_brake_modes(pros::E_MOTOR_BRAKE_HOLD);
	launcherMain.set_brake_modes(pros::E_MOTOR_BRAKE_HOLD);

	while(true){	

		//drive code

		driveMain.move_velocity(200);
		driveMain.set_brake_modes(MOTOR_BRAKE_COAST);


		
		driveRight.move(master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y ) - master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X));
		driveLeft.move(master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y ) + master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X));

		

		/*
		if ((master.get_digital(pros::E_CONTROLLER_DIGITAL_R2) == true)){
			driveMain.move(127);

		}else if((master.get_digital(pros::E_CONTROLLER_DIGITAL_L2) == true)){
			driveMain.move(-127);

		}else if((master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X) >= 30)){
			driveRight.move(-90);
			driveLeft.move(90);
		
		}else if((master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X) <= -30)){
			driveRight.move(90);
			driveLeft.move(-90);

		}else{
			driveMain.brake();
		}
		*/

		
		//pickup code

		if ((master.get_digital(pros::E_CONTROLLER_DIGITAL_L1) == true)){
			pickupMain.move(-127);

		}else if((master.get_digital(pros::E_CONTROLLER_DIGITAL_R1) == true)){
			pickupMain.move(127);

		}else{
			pickupMain.brake();
		}


		//blocker code

		if ((partner.get_digital(pros::E_CONTROLLER_DIGITAL_UP) == true)){
			blockerMain.set_brake_modes(MOTOR_BRAKE_HOLD);
			blockerMain.move(127);

		}else if((partner.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN) == true)){
			blockerMain.set_brake_modes(MOTOR_BRAKE_COAST);

		}else{
			blockerMain.brake();

		}





		//elevation code

		if ((partner.get_digital(pros::E_CONTROLLER_DIGITAL_A) == true) && (elevateInt == false)){
			elevationMain.set_value(1);
			waitUntil((partner.get_digital(pros::E_CONTROLLER_DIGITAL_A) == false))
				elevateInt = true;

		}

		if ((partner.get_digital(pros::E_CONTROLLER_DIGITAL_A) == true) && (elevateInt == true)){
			elevationMain.set_value(0);
			waitUntil((partner.get_digital(pros::E_CONTROLLER_DIGITAL_A) == false))
				elevateInt = false;

		}


		//matchlaod code

		//left match load code

		if ((master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT) == true) && ((leftMatchInt == false))){
			leftMatchload.set_value(1);
			waitUntil((master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT) == false))
			leftMatchInt = true;

		} 

		if ((master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT) == true) && ((leftMatchInt == true))){
			leftMatchload.set_value(0);
			waitUntil((master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT) == false))
			leftMatchInt = false;

		} 


		//right match laod code
		
		if ((master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT) == true) && ((rightMatchInt == false))){
			rightMatchload.set_value(1);
			waitUntil((master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT) == false))
			rightMatchInt = true;

		} 

		if ((master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT) == true) && ((rightMatchInt == true))){
			rightMatchload.set_value(0);
			waitUntil((master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT) == false))
			rightMatchInt = false;

		} 



		//catapult code

		if ((master.get_digital(pros::E_CONTROLLER_DIGITAL_A) == true)){
			launcherMain.move(127);

		

		}else{
			launcherMain.brake();

		}



		//launcher allignment

		if ((master.get_digital(pros::E_CONTROLLER_DIGITAL_Y) == true)){
			driveLeft.move(-60);
			driveRight.move(-40);
			pros::delay(525);
			driveMain.brake();
			pros::delay(50);

		}

		

			//RIP EXTENDO ROBERTO JR THE 3RD
		//EXTENDO ROBERTO JR THE 3RD (the side extension for the robot)

		/*if ((master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN) == true)){
			extendoRobertoJRIII.move(127);

		}else if((master.get_digital(pros::E_CONTROLLER_DIGITAL_X) == true)){
			extendoRobertoJRIII.move(-127);

		}else{
			extendoRobertoJRIII.brake();

		}*/
		
		


		

		pros::delay(50);

	}//end of driver forever loop	

}// end of op controll



	void myPID(int setpoint, int curRead){
		rightDriveRear.set_zero_position(0);
		rightDriveRear.tare_position();
		rightDriveRear.set_encoder_units(MOTOR_ENCODER_DEGREES);
		master.clear();
		
		pros::delay(250);

		pidRun = true;
		while(pidRun == true){
			curRead = rightDriveRear.get_position();
			error = setpoint - curRead;
			master.print(0, 0,"error: %d" ,  error);
			integral = integral + error;
			if (error == 0 or error > setpoint){
				integral = 0;
			}
			if (error > 5000 or error < -5000){
				integral = 0;
			}
			power = error*kP  + integral*kI;
			int motorP = rightDriveRear.get_position();

			if (power > 0 ){
				power = power + 30;
			}else if (power < 0){
				power = power - 27;
			}
			master.print(1,0,"motor POS: %d", motorP);
			master.print(2,0,"power: %d",power);
			driveMain.move(power);
			if (rightDriveRear.get_position() > setpoint - 5 and rightDriveRear.get_position() < setpoint + 5){
				pidRun = false;
				driveMain.brake();
			}
			
		}
	}// end of my pid

// 0 = left/counter clockwise, 1 = right/clockwise for direction
	void myPIDinert(int setpoint, int curRead, int dir){
		inert.tare();
		pros::delay(250);

		pidRun = true;
		while(pidRun == true){
			curRead = inert.get_heading();
			errori = setpoint - curRead;
			master.print(0, 0,"inertError: %d" ,  errori);
			integrali = integrali + errori;
			if (errori == 0 or errori > setpoint){
				integrali = 0;
			}
			if (errori > 400 or errori < -400){
				integrali = 0;
			}
			poweri = errori*kPi + integrali*kIi;
			poweri = poweri + 25;
			if ((inert.get_heading() > setpoint + 3) and (dir == 0)){
				driveLeft.move(poweri);
				driveRight.move(poweri* -1);
			}else if ((inert.get_heading() < setpoint - 3) and (dir == 1)){
				driveLeft.move(poweri * -1);
				driveRight.move(poweri);
			}
			int head = inert.get_heading();

			master.print(1,0,"heading: %d", head);
			master.print(2,0,"power: %d",poweri);
			if (curRead <= setpoint + 3 and curRead >= setpoint - 3){
				pidRun = false;
				driveMain.brake();
			}
			
			pros::delay(15);
		}
	}//end of mypid inert


	// dir decides dirction of rotation 0=left and 1=right
	void turnTo(int setpoint, int dir){
		
		while(!((inert.get_heading() >= setpoint - 5) and (inert.get_heading() <= setpoint + 5))){

			if (dir == 0){
				driveRight.move(50);
				driveLeft.move(-50);

			}else if (dir == 1){
				driveRight.move(-50);
				driveLeft.move(50);
				
			}

		}

	}//end of turn to 
	
