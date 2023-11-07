//#include "../include/spider_main.h"
#include "../include/walking.h"


int main(int argc, char **argv) {
  ros::init(argc, argv, "spider_main_node");
  ros::NodeHandle nh;
  Spider srider_main (nh);
  srider_main.standUpSpider();
  //WalkJointFunction a = WalkJointFunction();
  //WFunc d= WFunc();


  ros::spin();
  return 0;
}
