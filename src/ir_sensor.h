/**
 * @file ir_sensor.h
 * @version 01.06.2011
 * @authors Aydin Arik, Kevin Doran, Tim Grunshaw
 *
 * Contains functions related to the IR Sensor and automated lighting system in
 * the Home Automation System.
 */

#ifndef IR_SENSOR_H_
#define IR_SENSOR_H_

/**
 * Define the ports that the lights are connected to.
 */
#define LIGHT_1_SENSOR (1 << 16)
#define LIGHT_2_SENSOR (1 << 17)


/**
 * Turns on light 1.
 */
void turnOnLight1(void);


/**
 * Turns on light 2.
 */
void turnOnLight2(void);


/**
 * Turns off light 1.
 */
void turnOffLight1(void);


/**
 * Turns off light 2.
 */
void turnOffLight2(void);

#endif /* IR_SENSOR_H_ */
