/**
 * @file 
 * @brief Timer module
 * 
 */

#ifndef timer_h
#define timer_h

/**
 * @brief Start timer.
 */
void timer_start(void); 

/**
 * @brief Check if three seconds has past since timer was set
 * 
 * @return 1 if three seconds has past since timer was set. 0 otherwise. 
 */
int timer_timeout(void);

/**
 * @brief Stop timer.
 */
void timer_stop(void);

#endif /* timer_h */
