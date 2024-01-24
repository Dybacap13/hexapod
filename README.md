## Вдохновители
<a href=https://github.com/HumaRobotics/phantomx_gazebo/tree/master>  Phantom X </a
<br> </n>
<a href=https://github.com/KevinOchs/hexapod_ros>  Golem </a


##  Nodes

**_hexapod_controller_**

Главная нода, отвечает за расчёт обратной кинематики, генерирование походки .Пока используются следующие топики:

*Subscribed Topics*

     cmd_vel (geometry_msgs/Twist)  - задание скорости движения гексапода
     state (std_msgs::Bool)  - true -робот встанет
     
*Published Topics*

    joint_states_to_gazebo (sensor_msgs::JointState) - публикует рассчитанное положение суставов.
    
**_hexapod_controller_gazebo**
Отвечает за контроль в Gazebo

*Subscribed Topics*
joint_states_to_gazebo (sensor_msgs::JointState) - считывает рассчитанное положение суставов и публикует в Gazebo

*Published Topics*
<br>/spider/j_c1_lf_position_controller/command</n>
<br>/spider/j_c1_lm_position_controller/command</n>
<br>/spider/j_c1_lr_position_controller/command</n>
<br>/spider/j_c1_rf_position_controller/command</n>
<br>/spider/j_c1_rm_position_controller/command</n>
<br>/spider/j_c1_rr_position_controller/command</n>
<br>/spider/j_thigh_lf_position_controller/command</n>
<br>/spider/j_thigh_lm_position_controller/command</n>
<br>/spider/j_thigh_lr_position_controller/command</n>
<br>/spider/j_thigh_rf_position_controller/command</n>
<br>/spider/j_thigh_rm_position_controller/command</n>
<br>/spider/j_thigh_rr_position_controller/command</n>
<br>/spider/j_tibia_lf_position_controller/command</n>
<br>/spider/j_tibia_lm_position_controller/command</n>
<br>/spider/j_tibia_lr_position_controller/command</n>
<br>/spider/j_tibia_rf_position_controller/command</n>
<br>/spider/j_tibia_rm_position_controller/command</n>
<br>/spider/j_tibia_rr_position_controller/command</n>

**_hexapod_bringup_**

This package has all the launch files. From simple locomotion only to full mapping and localization examples. 

**_hexapod_description_**

This package has all the param files. You will start with one of the param config files to describe your hexapod. It also has params for different telop controllers. The xacro and meshes also reside in this package.



<h1> Суставы </h1>
<p/> j_spider_attachment -  тело ( фиксированный ) </p>
<h2>---->Относительно головы -->  суффиксы  </h2>
<li>lf   rf   --передняя левая/правая</li>
<li>lm   rm   --средняя левая/правая </li>
<li>lr   rr   --задняя левая/правая </li>
<h2>  Привод у туловища </h2>
<br> j_c1_lf </n>
<br>j_c1_rf </n>
<br>j_c1_lm </n>
<br>j_c1_rm </n>
<br>j_c1_lr </n>
<br>j_c1_rr </n>
 <h2> Привод колена</h2>
<br>j_thigh_lf</n>
<br>j_thigh_rf</n>
<br>j_thigh_lm</n>
<br>j_thigh_rm</n>
<br>j_thigh_lr</n>
<br>j_thigh_rr</n>
 <h2> Привод у стопы</h2>
<br>j_tibia_lf_</n>
<br>j_tibia_rf</n>
<br>j_tibia_lm</n>
<br>j_tibia_rm</n>
<br>j_tibia_lr</n>
<br>j_tibia_rr</n>
<h1>Запуск</h1>
<h3>roslaunch spider_gazebo srider_gazebo.launch </h3>
<h1> Расшифровка топиков <h1> 
<h2>Контроллеры ( отвечают за движение суставами)</h2>
<br>/spider/j_c1_lf_position_controller/command</n>
<br>/spider/j_c1_lm_position_controller/command</n>
<br>/spider/j_c1_lr_position_controller/command</n>
<br>/spider/j_c1_rf_position_controller/command</n>
<br>/spider/j_c1_rm_position_controller/command</n>
<br>/spider/j_c1_rr_position_controller/command</n>
<br>/spider/j_thigh_lf_position_controller/command</n>
<br>/spider/j_thigh_lm_position_controller/command</n>
<br>/spider/j_thigh_lr_position_controller/command</n>
<br>/spider/j_thigh_rf_position_controller/command</n>
<br>/spider/j_thigh_rm_position_controller/command</n>
<br>/spider/j_thigh_rr_position_controller/command</n>
<br>/spider/j_tibia_lf_position_controller/command</n>
<br>/spider/j_tibia_lm_position_controller/command</n>
<br>/spider/j_tibia_lr_position_controller/command</n>
<br>/spider/j_tibia_rf_position_controller/command</n>
<br>/spider/j_tibia_rm_position_controller/command</n>
<br>/spider/j_tibia_rr_position_controller/command</n>
<h1>Пакеты</h1>
<h2>walking </h2>
Моя неудавшаяся попытка заставить робота ходить. Что написано:
<li> считывает состояние робота из топика /spider/joint_states </li>
<li> подписывается на все топики, чтобы публиковать команды о смене позиции сустава</li>
<li>даже двигает суставы в газебо (но оочень медленно)</li>
<li>не понимаю код, и математику, и смысл, и вообще не хочу его больше видеть</li>
<h1>Источник модели</h1>


