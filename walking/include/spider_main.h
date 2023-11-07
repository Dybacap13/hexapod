#include <ros/ros.h>

#include <string>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/JointState.h>
#include <std_msgs/Float64.h>

#include <iostream>
#include <map>
#include <typeinfo>
#include <vector>



class Spider {
public:
    Spider(ros::NodeHandle& nh_);
    ~Spider() = default;
    void standUpSpider();
private:
    ros::NodeHandle nh;
    ros::Subscriber sub_joints;
    ros::Publisher pub_in_controller;
    ros::Publisher pub_cmd_vel;


    std::string name__space = "/spider/";
    std::map<std::string, ros::Publisher> publisher_joints_to_controller;  // словарь ключ - контроллер, значение - паблишер
    sensor_msgs::JointState joints_angles; // хранятся позиции суставов
    std::vector<std::string> joints_state; // хранятся имена суставов

    std::vector<ros::Publisher> aaa; // хранятся имена суставов

    int i_jointsStatesCallback = 0;
    void jointsStatesCallback(sensor_msgs::JointState); // считывает состояние суставов

   // void setWalkVelocity(float64 x, float64 y, float64 z);


    void setWalkVelocity(float linear_x, float linear_y, float angular_z);











};



Spider::Spider(ros::NodeHandle &nh_) : nh(nh_) {
    ros::Rate loop_rate(1);
    ROS_INFO ("Spider is hear");
    sub_joints = nh_.subscribe(name__space + "joint_states", 10, &Spider::jointsStatesCallback, this);
    while (ros::ok()) {
        ROS_INFO ("Waiting for controllers to connect...");
        ros::spinOnce();
        if (i_jointsStatesCallback == 1) break;
        loop_rate.sleep();
    }
    ROS_INFO ("Joints to connect");
    for (int i = 0; i < 18; i++) {
        pub_in_controller = nh_.advertise<std_msgs::Float64>(name__space + joints_state[i] + "_position_controller/command", 1000);
        publisher_joints_to_controller[joints_state[i]] = pub_in_controller;
         ROS_INFO("aaa[i] = pub_in_controller;");
        //aaa[i] = pub_in_controller;
    }
    pub_cmd_vel = nh_.advertise<geometry_msgs::Twist>(name__space + "cmd_vel", 1000);
}

void Spider::jointsStatesCallback(sensor_msgs::JointState msg_joint_state){
    while (i_jointsStatesCallback == 0) {
        joints_state = msg_joint_state.name;
        for(std::string n : joints_state)
              std::cout << n << "\t";
         i_jointsStatesCallback = 1;
    }
    joints_angles.position = msg_joint_state.position;
}

void Spider::setWalkVelocity(float linear_x, float linear_y, float angular_z){
    geometry_msgs::Twist msg_twist;
    msg_twist.linear.x = linear_x;
    msg_twist.linear.y = linear_y;
    msg_twist.angular.z = angular_z;
    pub_cmd_vel.publish(msg_twist);
}

void Spider::standUpSpider(){
    //хз, не работает
     ROS_INFO("PUB");

    ros::Rate loop_rate(1);
    std_msgs::Float64 msg;

    msg.data = 2.5535969874396414;
    int i = 0;
    while (i <50) {
    for (int i = 0; i < 18; i++) {
        if (i < 6){
            msg.data = 0;
           publisher_joints_to_controller[joints_state[i]].publish(msg);
           loop_rate.sleep();
           ROS_INFO("CONTINUI 1");
        }
        if (i>= 6 and i<12){
             msg.data = -10;
            publisher_joints_to_controller[joints_state[i]].publish(msg);
            loop_rate.sleep();
            ROS_INFO("CONTINUI 2");
        }
        if (i >=12){
            msg.data = 10;
           publisher_joints_to_controller[joints_state[i]].publish(msg);
           loop_rate.sleep();
           ROS_INFO("CONTINUI 3");
        }

        ROS_INFO("CONTINUI");

    }
    i++;
}

}

