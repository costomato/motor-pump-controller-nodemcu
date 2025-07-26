# Smart DOL Motor Pump Starter Controller

### [UPDATE] I have uploaded an optimized version of this project [here](https://github.com/costomato/motor-pump-controller-v2)

# Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Getting Started](#getting-started)
- [Using the MQTT Dash App](#using-the-mqtt-dash-app)
- [Next Steps: Full Automation](#next-steps-full-automation)
- [Project Files](#project-files)
- [Contributing](#contributing)
- [License](#license)
- [Acknowledgments](#acknowledgments)

## Overview

Welcome to the most straightforward and cost-effective way to convert your old Direct-On-Line (DOL) motor pump starter into a smart, Wi-Fi-controlled device. This project leverages a NodeMCU and a 2-channel relay to give you remote control over your motor pump via your smartphone. No more running downstairs to start or stop the pump—just sit back and tap a button on your phone!

## Features

- **Remote Control**: Start and stop your motor pump from anywhere with your smartphone.
- **Voice Control with Alexa**: Use Alexa commands to control your motor pump hands-free.
- **Cost-Effective**: Uses affordable components like NodeMCU and relay modules.
- **Easy to Implement**: Step-by-step instructions for both hardware setup and software configuration.
- **Manual Override**: Retain manual control of your motor pump alongside the smart controls.

## Getting Started

All the steps and detailed instructions for this project, including hardware setup and software configuration, are thoroughly explained in my Instructables article. You can find everything you need to get started right here:

### 🔗 [Read the full guide on Instructables](https://www.instructables.com/Easiest-and-Cheapest-Way-to-Convert-an-Old-DOL-Mot/)

## Using the MQTT Dash App

To make things even handier, you can control your motor pump using an MQTT dashboard app instead of visiting the Adafruit IO website every time. I’ve covered the configuration steps in the Instructables article, so be sure to check it out.

## Next Steps: Full Automation

If you're interested in taking this project a step further, consider automating your motor control even more. I've hinted at some ideas for manual ON and automatic OFF, as well as fully automated systems, in the Instructables article.

## Project Files

The project contains two files:

- **motor-pump-main.ino**: The main file with all core functionalities for controlling the motor pump.
- **motor-pump-with-alexa.ino**: This file is an extension of the main code and includes Alexa voice command integration. It contains everything from the main file along with additional code to support Alexa functionality, allowing you to control your motor pump through voice commands.

## Contributing

Found a bug or have a feature request? Feel free to open an issue or submit a pull request. Let's make this project even better together!

## License

This project is licensed under the MIT License—see the [LICENSE](LICENSE) file for details.

## Acknowledgments

Special thanks to all the DIY enthusiasts out there who inspired this project.
