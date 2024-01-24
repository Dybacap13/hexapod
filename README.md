## Вдохновители
<a href=https://github.com/HumaRobotics/phantomx_gazebo/tree/master>PhantomX</a>
<br> </n>
<a href=https://github.com/KevinOchs/hexapod_ros>Golem</a>



##  Nodes

**_hexapod_controller_**

Главная нода, отвечает за расчёт обратной кинематики, генерирование походки .Пока используются следующие топики:

*Subscribed Topics*

     cmd_vel (geometry_msgs/Twist)  - задание скорости движения гексапода
     state (std_msgs::Bool)  - true -робот встанет
     
*Published Topics*

    joint_states_to_gazebo (sensor_msgs::JointState) - публикует рассчитанное положение суставов.
    
**_hexapod_controller_gazebo_**

Отвечает за контроль в Gazebo

*Subscribed Topics*

     joint_states_to_gazebo (sensor_msgs::JointState) - считывает рассчитанное положение суставов и публикует в Gazebo

*Published Topics*

     /spider/j_c1_lf_position_controller/command
     /spider/j_c1_lm_position_controller/command
     /spider/j_c1_lr_position_controller/command
     /spider/j_c1_rf_position_controller/command
     /spider/j_c1_rm_position_controller/command
     /spider/j_c1_rr_position_controller/command
     /spider/j_thigh_lf_position_controller/command
     /spider/j_thigh_lm_position_controller/command
     /spider/j_thigh_lr_position_controller/command
     /spider/j_thigh_rf_position_controller/command
     /spider/j_thigh_rm_position_controller/command
     /spider/j_thigh_rr_position_controller/command
     /spider/j_tibia_lf_position_controller/command
     /spider/j_tibia_lm_position_controller/command
     /spider/j_tibia_lr_position_controller/command
     /spider/j_tibia_rf_position_controller/command
     /spider/j_tibia_rm_position_controller/command
     /spider/j_tibia_rr_position_controller/command


**_spider_description_**

Хранит параметры гексапода, его URDF-описание


**_spider_gazebo_**

     roslaunch spider_gazebo srider_gazebo.launch 
     
## Инструкция 

     roslaunch spider_gazebo srider_gazebo.launch 
     rosrun hexapod_controller hexapod_controller_gazebo 
     rosrun hexapod_controller hexapod_controller 


## Суставы 

Относительно головы -->  суффиксы  
     <li>lf   rf   --передняя левая/правая</li>
     <li>lm   rm   --средняя левая/правая </li>
     <li>lr   rr   --задняя левая/правая </li>

**_Привод у туловища_**
     <br> j_c1_lf </n>
     <br>j_c1_rf </n>
     <br>j_c1_lm </n>
     <br>j_c1_rm </n>
     <br>j_c1_lr </n>
     <br>j_c1_rr </n>

 **_Привод колена_**
     <br>j_thigh_lf</n>
     <br>j_thigh_rf</n>
     <br>j_thigh_lm</n>
     <br>j_thigh_rm</n>
     <br>j_thigh_lr</n>
     <br>j_thigh_rr</n>

 **_Привод у стопы_**
     <br>j_tibia_lf_</n>
     <br>j_tibia_rf</n>
     <br>j_tibia_lm</n>
     <br>j_tibia_rm</n>
     <br>j_tibia_lr</n>
     <br>j_tibia_rr</n>


