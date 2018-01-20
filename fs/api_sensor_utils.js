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


let SensorUtils = {

    // ## **`SensorUtils.fahrenheit(celsius)`**
    // Return value in degrees Fahrenheit of the supplied value degrees Celsius.
    fahrenheit: ffi('double fahrenheit(double)'),

    // ## **`SensorUtils.celsius(fahrenheit)`**
    // Return value in degrees Celsius of the supplied value degrees Fahrenheit.
    celsius: ffi('double celsius(double)'),

    // ## **`SensorUtils.inchesHg(Pascals)`**
    // Return value in inches of Mercury (Hg) of the supplied value for pressure in Pascals.
    inchesHg: ffi('double inches_hg(double)'),

    // ## **`SensorUtils.mmHg(Pascals)`**
    // Return value in millimeters of Mercury (Hg) of the supplied value for pressure in Pascals.
    mmHg: ffi('double mm_hg(double)'),

    // ## **`SensorUtils.atmospheresHg(inchesHg)`**
    // Return value in atmospheres of the supplied value for pressure in inches of Mercury (Hg).
    atmospheresHg: ffi('double atmospheres_hg(double)'),

    // ## **`SensorUtils.atmospheresP(Pascals)`**
    // Return value in atmospheres of the supplied value for pressure in Pascals.
    atmospheresP: ffi('double atmospheres_P(double)'),

    // ## **`SensorUtils.lengthF(meters)`**
    // Return value in feet of the supplied value for length in meters.
    lengthF: ffi('double length_F(double)'),

    // ## **`SensorUtils.computeDewpoint(temperature, relative_humidity)`**
    // Return value of dewpoint-temperature for the supplied values of temperature and relative humidity.
    computeDewpoint: ffi('double compute_dewpoint(double, double)'),

    // ## **`SensorUtils.computeAltitude(pressure, pressure_0)`**
    // Return value of altitude in meters for the supplied pressure and pressure at sea-level (pressure_0).
    computeAltitude: ffi('double compute_altitude(double, double)'),

    calc_stats: ffi('void calculate_statistics(void *)'),

    init_stats: ffi('void *init_d_statistics(int)'),

    add_data_val: ffi('void add_data_value(void *, double)'),

    stats_to_json: ffi('char *d_statistics_to_json(void *)'),

    // ## **`SensorUtils.initStatistics(samples)`**
    // Create and initialize a new statistics handle with an internal double array initialized for `samples` number
    // of values.  All other values set to zero in the struct.
    //
    // Return a statistics handle (retain this for additional statistics calculations).
    initStatistics: function (samples) {
        return this.init_stats(samples);
    },

    // ## **`SensorUtils.addDataValue(statistics, value)`**
    // Add a data value to a statistics handle.  Grows the internal array if necessary to hold the supplied value.
    addDataValue: function (statistics, value) {
        this.add_data_val(statistics, value);
    },

    // ## **`SensorUtils.calculateStatistics(statistics)`**
    // Compute simple statistics for the supplied statistics handle.
    //
    // Return a JSON-formatted string of the supplied statistics handle.
    calculateStatistics: function (StatsObj) {
        this.calc_stats(StatsObj);
        return this.stats_to_json(StatsObj);
    },

};