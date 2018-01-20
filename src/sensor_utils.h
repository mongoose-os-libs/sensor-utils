/**
 * Copyright (c) 2018 Brad Smith,
 *               bradley.1.smith@gmail.com,
 *               https://github.com/pedalPusher68
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * sensor_utils
 *
 * Sensor Utilities - A collection of C-functions that make it convenient to calculate derived quantities (e.g. dew point temperature),
 * convert between different units of measure, and perform simple statistics on arrays of (double precision)
 * values.
 */
#ifndef SENSOR_UTILS_SENSOR_UTILS_H
#define SENSOR_UTILS_SENSOR_UTILS_H

/*! CPP guard */
#ifdef __cplusplus
extern "C" {
#endif

#include "mgos.h"
#include "common/mbuf.h"
#include <math.h>

/**
 * This struct is used to hold an array of double-precision values and statistics derived from the values.
 *
 * Fields:
 * =======
 * - samples - this is the current size of the array used to hold the double-precision values
 * - size - this is the current number of double-precision values stored in the array
 * - data - this is the array of double-precision values held by this struct
 * - mean - the average of the values held in the double-precision array
 * - std_deviation - the standard deviation about the mean of the values in the double-precision array
 */
struct d_statistics {

    int samples;
    int size;// end of array
    double *data;
    double mean;
    double std_deviation;

};

/**
 * Standard library initializer required by [Mongoose OS](https://mongoose-os.com/docs/book/build.html#how-to-create-a-new-library).
 *
 * @return true - library initializer
 */
bool mgos_sensor_utils_init(void);

/**
 * Convert Celsius temperature value to Fahrenheit.
 *
 * @param celsius
 * @return Fahrenheit temperature calculated from supplied Celsius temperature value
 */
double fahrenheit(double celsius);

/**
 * Convert Fahrenheit temperature value to Celsius.
 *
 * @param fahrenheit
 * @return Celsius temperature calculated from supplied Fahrenheit temperature value
 */
double celsius(double fahrenheit);

/**
 * Convert atmospheric pressure in Pascals to inches of mercury (Hg).
 *
 * @param pascals
 * @return Atmospheric pressure in inches of Hg calculated from supplied atm. press. in Pascals
 */
double inches_hg(double pascals);

/**
 * Convert atmospheric pressure in Pascals to millimeters of mercury (Hg).
 *
 * @param pascals
 * @return Atmospheric pressure in millimeters of Hg calculated from supplied atm. press. in Pascals
 */
double mm_hg(double pascals);

/**
 * Convert atmospheric pressure in inches of mercury (Hg) to [atmospheres](https://en.wikipedia.org/wiki/Atmosphere_(unit)).
 *
 * @param inchesHg
 * @return Atmospheric pressure in atmospheres calculated from supplied atm. press. in inches Hg.
 */
double atmospheres_hg(double inchesHg);

/**
 * Convert atmospheric pressure in Pascals to [atmospheres](https://en.wikipedia.org/wiki/Atmosphere_(unit)).
 *
 * @param inchesHg
 * @return Atmospheric pressure in atmospheres calculated from supplied atm. press. in Pascals.
 */
double atmospheres_P(double pascals);

/**
 * Convert meters to feet.
 *
 * @param m
 * @return length in feet calculated from supplied length in meters.
 */
double length_F(double m);

/**
 * Compute dewpoint temperature in Celsius from supplied temperature and relative humidity.
 *
 * @param temp - temperature in Celsius
 * @param rh - relative humidity (0.0 - 1.0) as a percentage
 * @return dewpoint calculated from supplied temperature and relative humidity
 */
double compute_dewpoint(double temp, double rh);

/**
 * Compute altitude (in meters (m)) based on a value of pressure and pressure at sea level (p0).  The
 * calculation uses a ratio of pressure/pressure0 so any units should be fine as long as they're the same.
 *
 * @param pressure
 * @param pressure0
 * @return altitude in meters (m) represented by the supplied pressure and pressure0 values.
 */
double compute_altitude(double pressure, double pressure0);

/**
 * Create and initialize a new d_statistics struct with internal double array initialized for samples number
 * of values.  All other values set to zero in the struct.
 *
 * @param samples
 * @return
 */
struct d_statistics *init_d_statistics(int samples);

/**
 * Add a data value to a d_statistics struct.  Grows the internal array if necessary to hold the supplied value.
 *
 * @param statistics
 * @param value
 */
void add_data_value(struct d_statistics *statistics, double value);

/**
 * Createa JSON-string representation of the supplied d_statistics struct.
 *
 * @param statistics
 * @return
 */
char *d_statistics_to_json(struct d_statistics *statistics);

/**
 * Calculate simple statistics on the supplied
 * @param statistics
 */
void calculate_statistics(struct d_statistics *statistics);


#ifdef __cplusplus
}
#endif /* End of CPP guard */

#endif //SENSOR_UTILS_SENSOR_UTILS_H
