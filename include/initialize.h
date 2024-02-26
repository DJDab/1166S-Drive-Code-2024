#include "main.h"


//variables

    //pnuematic vars
        bool elevateInt = false;
        bool leftMatchInt = false;
        bool rightMatchInt = false;

    //auton vars
        int autoPick = 1;
        bool pidRun = false;

    //PID vars
        //PID vars drive
            int integral;
            int error;
            int setpoint;
            int power;
            double kP = 0.3;
            double kI = .0;
        
        //PID vars inert
            int integrali;
            int errori;
            int setpointi;
            int poweri;
            double kPi = 0.1;
            double kIi = .0;



//sensors

    pros::Imu inert(19);


//controllers
    pros::Controller master(pros::E_CONTROLLER_MASTER);
    pros::Controller partner(pros::E_CONTROLLER_PARTNER);

//drive motors
    pros::Motor leftDrive(5,1);
    pros::Motor leftDriveRear(9,1);
    pros::Motor rightDrive(7,0);
    pros::Motor rightDriveRear(8,0);

    pros::Motor_Group driveLeft({leftDrive,leftDriveRear});
    pros::Motor_Group driveRight({rightDrive,rightDriveRear});

    pros::Motor_Group driveMain({leftDrive,rightDrive,leftDriveRear,rightDriveRear});


//Pickup Motors

    pros::Motor pickup(12,0);

    pros::Motor_Group pickupMain({pickup});


//blocker Motors

    pros::Motor rightBlocker(15,1);
    pros::Motor leftBlocker(16,0);

    pros::Motor_Group blockerMain({rightBlocker,leftBlocker});


//launcher Motors

    pros::Motor leftLauncher(17,0);
    pros::Motor rightLauncher(18,1);

    pros::Motor_Group launcherMain({leftLauncher,rightLauncher});




    pros::Motor_Group all({leftDrive,rightDrive,leftDriveRear,rightDriveRear});


//extendo roberto

    pros::Motor extendoRobertoJRIII(11,0);


//PNHEMATCIC


//elevation

    pros::ADIDigitalOut elevationMain(1,0);



//matchload
    pros::ADIDigitalOut leftMatchload(3,0);
    pros::ADIDigitalOut rightMatchload(2,0);



