## 4. Nodes

**_hexapod_controller_**

This is the main node of the stack. It handles all control, gait, IK and servo communications with the legs. Minimal latency was required to keep the gait smooth and synced with odometry hence the reason they are all combined in this one node.

*Subscribed Topics*

     cmd_vel (geometry_msgs/Twist) Velocity command. 
     body_scalar (geometry_msgs::AccelStamped) Scalar to modifiy the orientation of the body.
     head_scalar (geometry_msgs::AccelStamped) Scalar to modifiy the pan and tilt of the optional turret.
     state (std_msgs::Bool) Bool array to record state of the hexapod. Standing up, sitting etc.
     imu/data (sensor_msgs::Imu) Used in optional auto body leveling on non level ground.
     
*Published Topics*

    sounds (hexapod_msgs::Sounds) Custom message to send sound cues to the optional sound package.
    joint_states (sensor_msgs::JointState) Joint states for rviz and such.
    odometry/calculated (nav_msgs::Odometry) Calculated odometry from the gait system in the package.
    twist (geometry_msgs::TwistWithCovarianceStamped) Twist message syncronized with the gait system. 
     

**_hexapod_bringup_**

This package has all the launch files. From simple locomotion only to full mapping and localization examples. 

**_hexapod_description_**

This package has all the param files. You will start with one of the param config files to describe your hexapod. It also has params for different telop controllers. The xacro and meshes also reside in this package.



<h1> Изменения на 14 ноября </h1>
<h1> Запуск, робот встанет и немного пройдёn</h1>
<h3>roslaunch spider_gazebo srider_real_gazebo.launch </h3>
<br>Как было организовано:</n>
<br>в файле spider_main.h написана функция </n>
<h3>void Spider::interpolationOfAngles(JointState current_angles,
                                   JointState target_angles, bool increase) </h3>


<li>текущее положение углов считывается с контроллеров само </li>
<li>желаемое нужно задать </li>
<li>третий аргумент пока бесполезен</li>

<br>С помощью умножения на коэфициент мы достигаем (плавно) желаемого положения. Происход не за один раз, чем больше коэфициент, тем быстрее достигается положение.
Эта же функция публикует итоговые и промежуточные углы в контроллеры газебо (всё в радианах)
Когда текущее положение = желаемому - функция выходит
Теперь в главном исполняемом файле src просто вызываем функцию, которой даёт желаемое положение</n>

<br>В начале - встаём, углы 0 30 120 градусов в радианах - отправили
Потом ходьба, делает цикл из 4 сообщений (комментарии в самом файле будут понятнее)</n>






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
<a href=https://github.com/HumaRobotics/phantomx_gazebo/tree/master>Модель в газебо взята отсюда</a

