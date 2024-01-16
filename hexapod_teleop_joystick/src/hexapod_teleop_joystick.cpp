
// ROS Hexapod Teleop Joystick Node
// Copyright (c) 2016, Kevin M. Ochs
// All rights reserved.

// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//   * Redistributions of source code must retain the above copyright
//     notice, this list of conditions and the following disclaimer.
//   * Redistributions in binary form must reproduce the above copyright
//     notice, this list of conditions and the following disclaimer in the
//     documentation and/or other materials provided with the distribution.
//   * Neither the name of the Kevin Ochs nor the
//     names of its contributors may be used to endorse or promote products
//     derived from this software without specific prior written permission.

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL KEVIN OCHS BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// Author: Kevin M. Ochs


#include <hexapod_teleop_joystick.h>


//==============================================================================
// Constructor
//==============================================================================

HexapodTeleopJoystick::HexapodTeleopJoystick( void )
{
    state_.data = false;
    imu_override_.data = false;
    NON_TELEOP = false; // Static but here for a safety precaution
    ros::param::get( "STANDUP_BUTTON", STANDUP_BUTTON );
    ros::param::get( "SITDOWN_BUTTON", SITDOWN_BUTTON );
    ros::param::get( "BODY_ROTATION_BUTTON", BODY_ROTATION_BUTTON );
    ros::param::get( "FORWARD_BACKWARD_AXES", FORWARD_BACKWARD_AXES );
    ros::param::get( "LEFT_RIGHT_AXES", LEFT_RIGHT_AXES );
    ros::param::get( "YAW_ROTATION_AXES", YAW_ROTATION_AXES );
    ros::param::get( "PITCH_ROTATION_AXES", PITCH_ROTATION_AXES );
    ros::param::get( "MAX_METERS_PER_SEC", MAX_METERS_PER_SEC );
    ros::param::get( "MAX_RADIANS_PER_SEC", MAX_RADIANS_PER_SEC );
    ros::param::get( "NON_TELEOP", NON_TELEOP );

    body_scalar_pub_ = nh_.advertise<geometry_msgs::AccelStamped>("/body_scalar", 100);
    head_scalar_pub_ = nh_.advertise<geometry_msgs::AccelStamped>("/head_scalar", 100);
    cmd_vel_pub_ = nh_.advertise<geometry_msgs::Twist>("cmd_vel", 100);
    state_pub_ = nh_.advertise<std_msgs::Bool>("/state", 100);
    imu_override_pub_ = nh_.advertise<std_msgs::Bool>("/imu/imu_override", 100);


    joy_sub_ = nh_.subscribe<sensor_msgs::Joy>("/joy", 5, &HexapodTeleopJoystick::joyCallback, this);
        joy_pub = nh_.advertise<sensor_msgs::Joy>("/joy",100);
        keyboard_sub = nh_.subscribe<geometry_msgs::Twist>("/key_", 10, &HexapodTeleopJoystick::keyCallback, this);
        joy_my.buttons.assign(12,0);
        joy_my.axes.assign(4,0);
}

//==============================================================================
// Joystick call reading joystick topics
//==============================================================================

void HexapodTeleopJoystick::keyCallback( const geometry_msgs::Twist key ){
    if (key.linear.x == 1 ){
        joy_my.buttons[STANDUP_BUTTON] = 1;
        joy_pub.publish(joy_my);
        joy_my.buttons[STANDUP_BUTTON] = 0;
    }

    if (key.linear.y == 1 ){

        joy_my.buttons[SITDOWN_BUTTON] = 1;
        joy_pub.publish(joy_my);
        joy_my.buttons[SITDOWN_BUTTON] = 0;

    }

    if (key.linear.z == 1) // key 2 is_rotation
    {
       // body_command.cmd = body_command.STAND_UP_CMD;
       // body_cmd_pub.publish(body_command);
        joy_my.buttons[BODY_ROTATION_BUTTON] = !joy_my.buttons[BODY_ROTATION_BUTTON];

        joy_pub.publish(joy_my);
    }

    if (key.angular.x == 1) // w, left up
    {
       // body_command.cmd = body_command.STAND_UP_CMD;
       // body_cmd_pub.publish(body_command);
        joy_my.axes[FORWARD_BACKWARD_AXES] = joy_my.axes[FORWARD_BACKWARD_AXES] + 0.01;
        //locomde_pub.publish(locomode);
        joy_pub.publish(joy_my);
    }


    // Travelling
    if( key.angular.y == 1  )
    {
        cmd_vel_.linear.x = joy_my.axes[FORWARD_BACKWARD_AXES] * MAX_METERS_PER_SEC;
        cmd_vel_.linear.y = -joy_my.axes[LEFT_RIGHT_AXES] * MAX_METERS_PER_SEC;
        cmd_vel_.angular.z = joy_my.axes[YAW_ROTATION_AXES] * MAX_RADIANS_PER_SEC;
        joy_pub.publish(joy_my);
    }
    // if (key->code ==120) // x, left down
    // {
    //    // body_command.cmd = body_command.STAND_UP_CMD;
    //    // body_cmd_pub.publish(body_command);
    //     joy.axes[FORWARD_BACKWARD_AXES] = joy.axes[FORWARD_BACKWARD_AXES] - 0.01;

    //     joy_pub.publish(joy);
    // }

    // if (key->code == 97) // a, left left
    // {
    //     joy.axes[LEFT_RIGHT_AXES] = joy.axes[LEFT_RIGHT_AXES] - 0.01;
    //     joy_pub.publish(joy);
    // }

    // if (key->code == 100) // d, left right
    // {
    //     joy.axes[LEFT_RIGHT_AXES] = joy.axes[LEFT_RIGHT_AXES] + 0.01;
    //     joy_pub.publish(joy);
    // }

    // if (key->code == 115) // s, left center
    // {
    //     joy.axes[LEFT_RIGHT_AXES] = 0;
    //     joy.axes[FORWARD_BACKWARD_AXES] = 0;
    //     joy_pub.publish(joy);
    // }


    // if (key->code ==105) // i, right up
    // {
    //    // body_command.cmd = body_command.STAND_UP_CMD;
    //    // body_cmd_pub.publish(body_command);
    //     joy.axes[YAW_ROTATION_AXES] = joy.axes[YAW_ROTATION_AXES] + 0.01;

    //     joy_pub.publish(joy);
    // }

    // if (key->code == 44) // , , right down
    // {
    //    // body_command.cmd = body_command.STAND_UP_CMD;
    //    // body_cmd_pub.publish(body_command);
    //      joy.axes[YAW_ROTATION_AXES] = joy.axes[YAW_ROTATION_AXES] - 0.01;

    //     joy_pub.publish(joy);
    // }

    // if (key->code == 106) // j, r left
    // {
    //     joy.axes[PITCH_ROTATION_AXES] = joy.axes[PITCH_ROTATION_AXES] - 0.01;
    //     joy_pub.publish(joy);
    // }

    // if (key->code == 108) // l, r right
    // {
    //     joy.axes[PITCH_ROTATION_AXES] = joy.axes[PITCH_ROTATION_AXES] + 0.01;
    //     joy_pub.publish(joy);
    // }

    // if (key->code == 107) // k, r center
    // {
    //     joy.axes[YAW_ROTATION_AXES] = 0;
    //     joy.axes[PITCH_ROTATION_AXES] = 0;
    //     joy_pub.publish(joy);
    // }




}


void HexapodTeleopJoystick::joyCallback( const sensor_msgs::Joy::ConstPtr &joy  )
{


    ros::Time current_time = ros::Time::now();
      if( joy->buttons[STANDUP_BUTTON] == 1 )
      {
          if ( state_.data == false)
          {
              state_.data = true;
          }
      }

      if ( joy->buttons[SITDOWN_BUTTON] == 1 )
      {
          if ( state_.data == true)
          {
              state_.data = false;
          }
      }

      // Body rotation L1 Button for testing
      if( joy->buttons[BODY_ROTATION_BUTTON] == 1 )
      {
          imu_override_.data = true;
          body_scalar_.header.stamp = current_time;
          body_scalar_.accel.angular.x = -joy->axes[LEFT_RIGHT_AXES];
          body_scalar_.accel.angular.y = -joy->axes[FORWARD_BACKWARD_AXES];
          head_scalar_.header.stamp = current_time;
          head_scalar_.accel.angular.z = joy->axes[YAW_ROTATION_AXES];
          head_scalar_.accel.angular.y = joy->axes[PITCH_ROTATION_AXES];
      }
      else
      {
          imu_override_.data = false;
      }

      // Travelling
// joy->axes[FORWARD_BACKWARD_AXES] = 0.01;
//  joy->axes[LEFT_RIGHT_AXES] = -0.01;
// joy->axes[YAW_ROTATION_AXES] = 0.01;
//           cmd_vel_.linear.x = joy->axes[FORWARD_BACKWARD_AXES] * MAX_METERS_PER_SEC;
//           cmd_vel_.linear.y = -joy->axes[LEFT_RIGHT_AXES] * MAX_METERS_PER_SEC;
//           cmd_vel_.angular.z = joy->axes[YAW_ROTATION_AXES] * MAX_RADIANS_PER_SEC;
      // cmd_vel_.linear.x = 0.01* MAX_METERS_PER_SEC;
      //          cmd_vel_.linear.y = -0.01 * MAX_METERS_PER_SEC;
      //          cmd_vel_.angular.z = 0.01 * MAX_RADIANS_PER_SEC;
      // cmd_vel_.linear.x = q* MAX_METERS_PER_SEC;
      //          cmd_vel_.linear.y = -w * MAX_METERS_PER_SEC;
      //          cmd_vel_.angular.z = c* MAX_RADIANS_PER_SEC;
      //          q = q +0.1;
      //                  w = w +0.1;
      //                  c = c +0.1;
      //                   cmd_vel_pub_.publish(cmd_vel_ );

}






int main(int argc, char** argv)
{
    ros::init(argc, argv, "hexapod_teleop_joystick");
    HexapodTeleopJoystick hexapodTeleopJoystick;

    ros::AsyncSpinner spinner(1); // Using 1 threads
    spinner.start();

    ros::Rate loop_rate( 100 ); // 100 hz
    //hexapodTeleopJoystick.state_pub_.publish( hexapodTeleopJoystick.state_ );
    while ( ros::ok() )
    {
        // if( hexapodTeleopJoystick.NON_TELEOP == false ) // If True, assumes you are sending these from other packages
        // {

         //   hexapodTeleopJoystick.body_scalar_pub_.publish( hexapodTeleopJoystick.body_scalar_ );
          //  hexapodTeleopJoystick.head_scalar_pub_.publish( hexapodTeleopJoystick.head_scalar_ );
        // }
       // hexapodTeleopJoystick.state_pub_.publish( hexapodTeleopJoystick.state_ ); // Always publish for means of an emergency shutdown type situation
        //hexapodTeleopJoystick.imu_override_pub_.publish( hexapodTeleopJoystick.imu_override_ );
        loop_rate.sleep();

}
}
