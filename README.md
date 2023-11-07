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

