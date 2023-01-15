# Tennis-Training-Robot

![image](https://user-images.githubusercontent.com/75193860/212554815-faf92921-23ce-4367-a0bc-0fbeeb7cf6cf.png)


## Initial Startup Procedure:
1. The user inputs the number of rounds on the LEGO EV3 brick interface
    - makes use of buttons on brick
2. The robot presents an option to train with high balls, low balls, or middle ball ranges

![image](https://user-images.githubusercontent.com/75193860/212554798-5172c977-205a-4c24-b744-369ad5a8c1c6.png)

3. Present the balls under the color sensor and wait for the conveyor to intake the balls
    - color sensor waits to detect yellow and any other colour will not move the conveyor belt
    - intaking is done via a large EV3 motor at very slow speed to prioritize input precision
![image](https://user-images.githubusercontent.com/75193860/212555743-ee1d9c84-a0dc-4323-ae6f-93a187ab773a.png)

4. Balls will be intaked a preset distance to store up to 3 balls within the conveyor belt
    - makes use of motor encoder value
![image](https://user-images.githubusercontent.com/75193860/212555701-ce10a221-3e5e-4bd0-9b87-af7fc72431d2.png)


End of User input
----

## During the Round
1. The robot makes it way around the field to either the high, low, or middle range position to begin shooting
    - makes use of two driving motors + pivot ball
    - makes use of motor encoder
![image](https://user-images.githubusercontent.com/75193860/212554903-1cb03352-de08-47b8-89b3-621f86287f1b.png)

2. Prior to shooting, the robot takes approximately 3 seconds to gain flywheel momentum
    - spins up to 1300 rpm by using two large EV3 motors attached to a 8:1 two level gear system 
    - large motors spin at approximately 170 rpm
![image](https://user-images.githubusercontent.com/75193860/212555020-782c4857-9470-475f-982a-52e4f754d575.png)

3. Once the flywheels are turned onto max speed, the robot rotates a random angle between -30 and 30 degrees
    - driving motors are turned at equal speeds in opposite directions
![image](https://user-images.githubusercontent.com/75193860/212554938-fea07455-9488-4bc5-8f57-08bc65f8d601.png)

4. The conveyor belt then moves the balls towards the flywheels a preset distance
    - makes use of same motor encoder value as when balls are intaked
5. Only one ball makes it's way to the flywheel and the ball is shot
6. After the ball is shot, the robot turns back to 0 degrees, facing the player directly
    - makes use of gyro sensor
7. Steps 4,5,6 are repeated 3 times in total (until all balls are shot)
8. The robot then makes it's way back to it's original position where balls were inputted
    - makes use of motor encoder values
9. Once the robot returns to the origin it checks if the numbers of rounds set by the user is completed
    - if more rounds are left to play, steps 1-8 are repeated after completing steps 3 and 4 from initial startup procedure
    - if the numbers of rounds is done, the program ends

### A detailed and visual representation of the above steps are presented below:
![image](https://user-images.githubusercontent.com/75193860/212554237-de349bd1-a4a1-44e4-92c1-4075974e2df6.png)
![image](https://user-images.githubusercontent.com/75193860/212554242-98ae1ad8-3230-44c6-859e-451e53532911.png)
![image](https://user-images.githubusercontent.com/75193860/212554248-8003fe1d-0b09-469e-b365-9206b846c6e9.png)
![image](https://user-images.githubusercontent.com/75193860/212554253-f1852c4c-3ccf-4947-bb2e-5bd8b51c94c3.png)
![image](https://user-images.githubusercontent.com/75193860/212554262-0ffc97aa-0d1d-43f3-9885-1c97d6343c1c.png)
![image](https://user-images.githubusercontent.com/75193860/212554273-13fea6d3-5f7f-49f5-b20f-5d2537b51eac.png)
