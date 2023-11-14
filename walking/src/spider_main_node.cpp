#include "../include/spider_main.h"
//#include "../include/walking.h"

int main(int argc, char **argv) {
  ros::init(argc, argv, "spider_main_node");
  ros::NodeHandle nh;
  Spider srider_main(nh);
  // srider_main.standUpSpider();
  JointState aaa;
  aaa.joints = srider_main.joints_state_node.joints;

  // Это положения углов в радианах, чтобы встать 0 30 120
  std::vector<double> starting_position = {
      0.0, 0.0, 0.0, 0.0,    0.0,    0.0,    0.5,    0.5,    0.5,
      0.5, 0.5, 0.5, -2.094, -2.094, -2.094, -2.094, -2.094, -2.094};

  aaa.angles = starting_position;

  ROS_INFO("BEGIN");
  srider_main.interpolationOfAngles(srider_main.joints_state_node, aaa, true);


  // Тут начинается ходьба
  float coxa = 0.8;
  float thihg = 0.6;

  // поднять левые + передвинуть левую + в ноль правую
  std::vector<double> one = {-coxa,  0.0,    -coxa,  0.0,    coxa,   0.0,
                             thihg,  0.5,    thihg,  0.5,    thihg,  0.5,
                             -2.094, -2.094, -2.094, -2.094, -2.094, -2.094};

  // опустить левые
  std::vector<double> lower_left = {
      -coxa, 0.0, -coxa, 0.0,    coxa,   0.0,    0.5,    0.5,    0.5,
      0.5,   0.5, 0.5,   -2.094, -2.094, -2.094, -2.094, -2.094, -2.094};

  // поднять правую + шагнуть правой + поставить в ноль левую
  std::vector<double> two = {0.0,    -coxa,  0.0,    coxa,   0.0,    coxa,
                             0.5,    thihg,  0.5,    thihg,  0.5,    thihg,
                             -2.094, -2.094, -2.094, -2.094, -2.094, -2.094};

  //опустил правую
  std::vector<double> lower_right = {
      0.0, -coxa, 0.0, coxa,   0.0,    coxa,   0.5,    0.5,    0.5,
      0.5, 0.5,   0.5, -2.094, -2.094, -2.094, -2.094, -2.094, -2.094};

  for (int i = 0; i < 10; i++) {

    aaa.angles = one;
    srider_main.interpolationOfAngles(srider_main.joints_state_node, aaa, true);

    aaa.angles = lower_left;
    srider_main.interpolationOfAngles(srider_main.joints_state_node, aaa, true);

    aaa.angles = two;
    srider_main.interpolationOfAngles(srider_main.joints_state_node, aaa, true);

    aaa.angles = lower_right;
    srider_main.interpolationOfAngles(srider_main.joints_state_node, aaa, true);
  }

  ros::spin();
  return 0;
}
