include <ros/ros.h>

#include <geometry_msgs/Twist.h>
#include <sensor_msgs/JointState.h>
#include <std_msgs/Float64.h>
#include <string>

#include <ctime>
#include <iostream>
#include <map>
#include <typeinfo>
#include <vector>

float DELTA = 0.01;

struct JointState {
  std::vector<std::string> joints;
  std::vector<double> angles;
};

class Spider {
public:
  Spider(ros::NodeHandle &nh_);
  ~Spider() = default;
  void standUpSpider();

  void interpolationOfAngles(JointState current_angles,
                             JointState target_angles, bool a);
  JointState joints_state_node;

private:
  ros::NodeHandle nh;
  ros::Subscriber sub_joints;
  ros::Publisher pub_in_controller;
  ros::Publisher pub_cmd_vel;

  std::string name__space = "/phantomX/";
  std::map<std::string, ros::Publisher>
      publisher_joints_to_controller; // словарь ключ - контроллер, значение -
                                      // паблишер
  sensor_msgs::JointState joints_angles; // хранятся позиции суставов
  std::vector<std::string> joints_state; // хранятся имена суставов

  std::vector<ros::Publisher> aaa; // хранятся имена суставов

  int i_jointsStatesCallback = 0;
  void jointsStatesCallback(
      sensor_msgs::JointState); // считывает состояние суставов



  void setWalkVelocity(float linear_x, float linear_y, float angular_z);

  bool ravno(const JointState X, const JointState Y);
};
bool Spider::ravno(const JointState X, const JointState Y) {
  for (unsigned int number = 0; number < 18; number++) {
    if (abs(X.angles[number] - Y.angles[number]) > DELTA)
      return false;
  }
  return true;
}

Spider::Spider(ros::NodeHandle &nh_) : nh(nh_) {
  ros::Rate loop_rate(1);
  ROS_INFO("Spider is hear");
  sub_joints = nh_.subscribe(name__space + "joint_states", 10,
                             &Spider::jointsStatesCallback, this);
  while (ros::ok()) {
    ROS_INFO("Waiting for controllers to connect...");
    ros::spinOnce();
    if (i_jointsStatesCallback == 1)
      break;
    loop_rate.sleep();
  }
  ROS_INFO("Joints to connect");
  for (int i = 0; i < 18; i++) {
    pub_in_controller = nh_.advertise<std_msgs::Float64>(
        name__space + joints_state[i] + "_position_controller/command", 1000);
    publisher_joints_to_controller[joints_state[i]] = pub_in_controller;

  }
  pub_cmd_vel =
      nh_.advertise<geometry_msgs::Twist>(name__space + "cmd_vel", 1000);
}

void Spider::jointsStatesCallback(sensor_msgs::JointState msg_joint_state) {
  while (i_jointsStatesCallback == 0) {
    joints_state = msg_joint_state.name;
    joints_state_node.joints = msg_joint_state.name;
    for (std::string n : joints_state)
      std::cout << n << "\t";
    i_jointsStatesCallback = 1;
  }
  joints_angles.position = msg_joint_state.position;
  joints_state_node.angles = msg_joint_state.position;
}

void Spider::setWalkVelocity(float linear_x, float linear_y, float angular_z) {
  geometry_msgs::Twist msg_twist;
  msg_twist.linear.x = linear_x;
  msg_twist.linear.y = linear_y;
  msg_twist.angular.z = angular_z;
  pub_cmd_vel.publish(msg_twist);
}

//Палённая функция, просьба не смотреть

//void Spider::standUpSpider() {
//  for (int i = 0; i < 18; i++) {
//    std::cout << joints_angles.position[i];
//    std::cout << "\n";
//  }


//  time_t start = time(NULL);
//  time_t delay = 2;
//  time_t stop = start + delay;
//  std_msgs::Float64 msg;
//  std::vector<float> angles;
//  ros::Rate loop_rate(100);
//  while (ros::ok()) {
//    ros::spinOnce();
//    time_t t = time(NULL);
//    if (t > stop)
//      break;
//    float ratio = (t - start) / delay;
//    for (int j = 0; j < 18; j++) {
//      msg.data = 0.0 * ratio + joints_angles.position[j] * (1 - ratio);
//      float t = 0.0 * ratio + joints_angles.position[j] * (1 - ratio);
//      publisher_joints_to_controller[joints_state[j]].publish(msg);
//      std::cout << joints_state[j], ";", t;
//      std::cout << "  ;  ";
//      std::cout << t;
//      std::cout << "\n";
//    }
//    std::cout << "MSG END*//*/*//*/*//*/*/*";
//    std::cout << "\n";
//    loop_rate.sleep();
//  }
//}


// Главная функция
// Делает плавный переход от стартового значения к желаемому путём умножения на коэфициент
void Spider::interpolationOfAngles(JointState current_angles,
                                   JointState target_angles, bool increase) {

  float interpolation_coefficient;

  interpolation_coefficient = 0.99999; // чем он больше, тем желаемое положение быстрее достигается


  JointState interpolation_angles;
  interpolation_angles.joints = current_angles.joints;

  bool a;
  ros::Rate loop_rate(100);
  a = ravno(current_angles, target_angles);

  std_msgs::Float64 msg;
  while (ros::ok()) {

    a = ravno(current_angles, target_angles);

    if (ravno(current_angles, target_angles) == true) // цикл прекратится, когда старт. значение = желаемому
      break;
    ros::spinOnce();

    // короче, это нужно, чтобы сначала передавалась команда в контроллеры колена (thingh), а потом уже в бедро (с1)
    for (int j = 6; j < 18; j++) {

      msg.data = target_angles.angles[j] * interpolation_coefficient +
                 current_angles.angles[j] * (1 - interpolation_coefficient);
      float t = target_angles.angles[j] * interpolation_coefficient +
                current_angles.angles[j] * (1 - interpolation_coefficient);

      publisher_joints_to_controller[joints_state[j]].publish(msg);
      std::cout << joints_state[j], ";", t;
      std::cout << "  ;  ";
      std::cout << t;
      std::cout << "\n";
      current_angles.angles = joints_state_node.angles;
    }
    // вот здесь передаем только в с1
    //это нужно чтобы получая сообщение "// поднять левые + передвинуть левую + в ноль правую"
    // он сначала поднимал, потом шагал

    for (int j = 0; j < 6; j++) {

      msg.data = target_angles.angles[j] * interpolation_coefficient +
                 current_angles.angles[j] * (1 - interpolation_coefficient);
      float t = target_angles.angles[j] * interpolation_coefficient +
                current_angles.angles[j] * (1 - interpolation_coefficient);

      publisher_joints_to_controller[joints_state[j]].publish(msg);
      std::cout << joints_state[j], ";", t;
      std::cout << "  ;  ";
      std::cout << t;
      std::cout << "\n";
      current_angles.angles = joints_state_node.angles;
    }
    std::cout << "MSG END*//*/*//*/*//*/*/*";
    std::cout << "\n";
    loop_rate.sleep();
  }
  ROS_INFO("I YES!!!!!!!!!!");
}
