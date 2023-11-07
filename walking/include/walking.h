#include <ros/ros.h>
#include "../include/spider_main.h"
#include <string>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/JointState.h>
#include <std_msgs/Float64.h>

#include"../include/spider_joints.h"

#include <iostream>
#include <map>
#include <typeinfo>
#include <vector>

#include <math.h>

const double PI = 3.141592653589793;
/*
std::vector<std::string> spider_joints{"j_c1_lf", "j_c1_rf", "j_c1_lm", "j_c1_rm", "j_c1_lr", "j_c1_rr",
                                       "j_thigh_lf", "j_thigh_rf", "j_thigh_lm", "j_thigh_rm", "j_thigh_lr", "j_thigh_rr",
                                       "j_tibia_lf", "j_tibia_rf", "j_tibia_lm", "j_tibia_rm", "j_tibia_lr", "j_tibia_rr"};


std::vector<std::string> movement_of_the_left_half{"lf", "rm", "lr"};
std::vector<std::string> movement_of_the_right_half{"rf", "lm", "rr"};
*/

class WalkJointFunction {
public:
    WalkJointFunction();

    float offset = 0.0;
    float scale = 1.0;
    float in_offset = 0.0;
    float in_scale = 1.0;
    float get_angle_in_radians(float x); //хз что даёт
    WalkJointFunction clone ();
    WalkJointFunction mirror();

};

WalkJointFunction::WalkJointFunction(){
    ROS_INFO ("SpiderWalking is ready");

}


float WalkJointFunction::get_angle_in_radians(float x){ // x between 0 and 1
    if ((x < 0) or (x > 1))
        ROS_ERROR ("Error in function get_angle_in_radians-- x = %f  ", x);
    float f = sin(in_offset + in_scale * x);
    return offset + scale * f;
}

WalkJointFunction WalkJointFunction::clone (){
    WalkJointFunction z;;
    z.offset = offset;
    z.scale = scale;
    z.in_offset =in_offset;
    z.in_scale = in_scale;
    return z;
}

WalkJointFunction WalkJointFunction:: mirror(){
    WalkJointFunction z = clone();
    z.offset *= -1;
    z.scale *= -1;
    return z;
}


struct Node {
    std::string name;
    WalkJointFunction a;
};


class WFunc{
public:

    WFunc();
    std::map<std::string, float> parameters;

    std::map<std::string, WalkJointFunction> phase_joint_functions;
    std::map<std::string, WalkJointFunction> anti_phase_joint_functions;
    std::map<std::string, float> angles;
    void generate();
    void set_func(std::string, WalkJointFunction, WalkJointFunction );
    std::map<std::string, float> det_dist_angles(bool phase, float x, std::vector<float> velocity);
    std::map<std::string, float> appely_velocity (std::map<std::string, float> angles,std::vector<float> velocity, bool phase,float x );

};

WFunc::WFunc(){
    parameters["swing_scale"] = 1;
    parameters["vx_scale"] = 0.5;
    parameters["vy_scale"] = 0.5;
    parameters["vt_scale"] = 0.4;
    generate();
    ROS_INFO ("WFunc::WFunc(){");





}
void WFunc::generate(){
     WalkJointFunction f1;
      f1.in_scale = PI;
      f1.scale = -parameters["swing_scale"];

      WalkJointFunction f2 = f1.clone();
      f2.scale = 0;

      WalkJointFunction f3 = f1.clone();
      f3.scale *= -1;

      WalkJointFunction f4 = f2.clone();
      f3.scale *= -1;

      WalkJointFunction zero;
      zero.scale = 0;

      set_func("j_thigh", f1, f2);
      set_func("j_tibia", f3, f4);
      set_func("j_c1", zero, zero);


}

void WFunc::set_func(std::string joint, WalkJointFunction phase, WalkJointFunction phase_anti){ // генерирует два словаря
    std::string j_name = "";
    // левые ноги ['lf', 'rm', 'lr']:
    for (int i = 0; i < 3; i ++){ //3  потому что 6 ног делим на 2
         j_name = joint + '_' + movement_of_the_left_half[i];
        phase_joint_functions[j_name] = phase;
        anti_phase_joint_functions[j_name] =  phase_anti;
    }

    // правые ноги ['rf', 'lm', 'rr']:
    for (int i = 0; i < 3; i ++){ //3  потому что 6 ног делим на 2
        j_name = joint + '_' + movement_of_the_right_half[i];
        phase_joint_functions[j_name] = phase;
        anti_phase_joint_functions[j_name] =  phase_anti;
    }
}

std::map<std::string, float> WFunc::det_dist_angles(bool phase, float x, std::vector<float> velocity){
    for (auto count = phase_joint_functions.begin(); count != phase_joint_functions.end(); ++count) {
      if (phase){
          float angles_rad = phase_joint_functions[count->first].get_angle_in_radians(x);
          angles[count->first] = angles_rad;
      }
      else {
          angles[count->first] = anti_phase_joint_functions[count->first].get_angle_in_radians(x);
      }

      return appely_velocity(angles,velocity, phase, x );

    }
}

std::map<std::string, float> WFunc::appely_velocity (std::map<std::string, float> angles,std::vector<float> velocity, bool phase,float x ){
    float v = velocity[0] * parameters["vx_scale"];
    float d = (x * 2 - 1) * v;
    //VX
    if (phase){
        angles['j_c1_lf'] -= d;
        angles['j_c1_rm'] += d;
        angles['j_c1_lr'] -= d;
        angles['j_c1_rf'] -= d;
        angles['j_c1_lm'] += d;
        angles['j_c1_rr'] -= d;
    }
    else{
        angles['j_c1_lf'] += d;
        angles['j_c1_rm'] -= d;
        angles['j_c1_lr'] += d;
        angles['j_c1_rf'] += d;
        angles['j_c1_lm'] -= d;
        angles['j_c1_rr'] += d;
    }

    v = velocity[2] * self.parameters["vt_scale"];
    d = (x * 2 - 1) * v;
    if (phase){
        angles['j_c1_lf'] += d;
        angles['j_c1_rm'] += d;
        angles['j_c1_lr'] += d;
        angles['j_c1_rf'] -= d;
        angles['j_c1_lm'] -= d;
        angles['j_c1_rr'] -= d;
    }
    else{
        angles['j_c1_lf'] -= d;
        angles['j_c1_rm'] -= d;
        angles['j_c1_lr'] -= d;
        angles['j_c1_rf'] += d;
        angles['j_c1_lm'] += d;
        angles['j_c1_rr'] += d;
    }
    return angles;

}





class Walking {
    Walking(ros::NodeHandle &nh_, Spider a);
    Spider class_spider = Spider();
     bool running;
    std::vector<float> velocity{0.0, 0.0, 0.0};
    bool walking;
    WFunc w_func = WFunc();
     std::map<std::string, float> ready_pos;
     bool _th_walk;
     ros::NodeHandle nh;
     ros::Subscriber sub_joints;
     void jointsStatesCallback(geometry_msgs::Twist msg_twist);
      void start();
      void init_walk();


};


Walking::Walking(ros::NodeHandle &nh_, Spider a) : nh(nh_){
    class_spider = a;
    running = false;
    walking = false;
    ready_pos = w_func.get(true, 0, {0.0, 0.0, 0.0});
    _th_walk = false;
    sub_joints = nh_.subscribe(a.name__space + "cmd_vel", 10, &Walking::jointsStatesCallback, this);


}


Walking::jointsStatesCallback(geometry_msgs::Twist msg_twist){
     start();

}

void Walking::start(){
    running = true;
    class_spider.set_angles_slow(ready_pos);



    walking = false;
}



























