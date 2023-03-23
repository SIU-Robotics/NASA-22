<a name="readme-top"></a>
<!-- TABLE OF CONTENTS -->
# SIU NASA Robotics 2022-2023
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li><a href="#about-the-project">About The Project</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#website">Website</a></li>
    <li><a href="#I2C">I2C</a></li>
    <li><a href="#rplidar">RPLIDAR</a></li>
  </ol>
</details>



## About The Project

The SIU Robotics team competes in the NASA Lunabotics challenge every year. For more information on the competition, see <a href="https://www.nasa.gov/offices/education/centers/kennedy/technology/nasarmc.html">here</a>.

This year (2022-2023), we're set on implementing automation.

<p align="right">(<a href="#readme-top">back to top</a>)</p>



## Roadmap

- [x] Create website
- [x] Implement I2C
- [x] Working motors and driving
- [ ] Functional auger
- [ ] Automatic driving
- [ ] Automatic digging

<p align="right">(<a href="#readme-top">back to top</a>)</p>


## DEPENDENCIES

Python3: Django, smbus2, opencv_python

## Website

For our Lunabot, we're creating a website using the Django framework. This website acts like a control panel for our robot.

Some of the functionality currently includes:
* Send movement commands
* View live camera feed

<p align="right">(<a href="#readme-top">back to top</a>)</p>



## I2C

We're able to control motors from the website using a protocol called I2C. Read about it <a href="https://en.wikipedia.org/wiki/I%C2%B2C#:~:text=I2C%20(Inter%2DIntegrated,in%201982%20by%20Philips%20Semiconductors.">here</a>.

The website runs on a RaspberryPi 4b. The Django framework calls Python methods that use the smbus2 library. We use smbus2 methods to send arrays of bytes over the I2C protocol to the arduino which controls the motors. 

<p align="right">(<a href="#readme-top">back to top</a>)</p>



## RPLIDAR

For our movement automation, we're using an RPLIDAR A2M8. In order to collect informaiton from the LiDAR sensor, we use the RPLIDAR python library.

<p align="right">(<a href="#readme-top">back to top</a>)</p>
