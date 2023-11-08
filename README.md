# WRO_2023_AZE

Our robot uses 1 DC motor in front axle for mobility, and 1 servo motor in rear axle for steering. We used L298N motor driver, an arduino nano for obstacle detection, and raspberry pi for color detection. As sensors, object detection sensors and raspberry pi camera module(with light) are used. To charge the robot, we have 2 Litium rechargable battery(3S 11.1V).
In raspberry pi we used AI to detect green and red colours, and send necessary signals to arduino. Then, the car avoids traffic signs according to their color, and if there is no sign, the car continues to move forward until it reaches a turn. For turning the car, an TCS3200 color sensor is used to detect lines on the map.
