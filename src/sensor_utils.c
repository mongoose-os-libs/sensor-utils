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

#include "sensor_utils.h"

bool mgos_sensor_utils_init(void) {
    // If there were other initialization code that needed to be performed, it could be done here.  If initialization
    // failed, could return false.
    return true;
}

double fahrenheit(double celsius) {
    return 1.8 * celsius + 32.0;
}

double celsius(double fahrenheit) {
    return (fahrenheit - 32.0) / 1.8;
}

double inches_hg(double pascals) {
    return pascals / 3386.389;
}

double mm_hg(double pascals) {
    return (pascals / 3386.389) / 25.4;
}

double atmospheres_hg(double inchesHg) {
    return inchesHg / 29.92;
}

double atmospheres_P(double pascals) {
    return pascals / 101325;
}

double length_F(double m) {
    return m * 3.28084;
}

const double A = 8.1332;
const double B = 1763.39;
const double C = 235.66;

double compute_dewpoint(double temp, double rh) {

    double exponent = A - (B / (temp + C));
    double pp = pow(10, exponent);
    double denom = log10(rh * (pp / 100.0)) - A;
    double TDP = -1 * ((B / denom) + C);
    return TDP; // in Celsius

}

double compute_altitude(double pressure, double pressure0) {
    double altitude;
    if (pressure0 <= 0.0) {
        pressure0 = 101325;
    }
    altitude = 44330.0 * (1.0 - pow(pressure / pressure0, 0.190294957));
    return altitude;
}


//// statistics computed from an array of doubles
//struct d_statistics {
//
//    int samples;
//    int len;
//    double *data;
//    double mean;
//    double std_deviation;
//
//};

struct d_statistics *init_d_statistics(int samples) {
    struct d_statistics *out;
    out = (struct d_statistics *) malloc(sizeof(struct d_statistics));
    out->samples = samples;
    out->data = (double *) malloc(samples * sizeof(double));
    out->size = 0;
    return out;
}

void add_data_value(struct d_statistics *statistics, double value) {
    // TODO - error checking...
    if (statistics->size == statistics->samples) {
        LOG(LL_DEBUG, ("statistics->size = %d,  statistics->samples = %d", statistics->size, statistics->samples));
        // TODO... grow data array and add
        double *new_data = (double *) realloc(statistics->data, (statistics->samples + 1) * sizeof(double));
        if (new_data == NULL) {
            LOG(LL_ERROR, ("Problem adding data value."));
            return;
        }
        statistics->data = new_data;
        statistics->samples++;
    }
    statistics->data[statistics->size++] = value;

}


char *d_statistics_to_json(struct d_statistics *statistics) {

    struct mbuf buf;
    mbuf_init(&buf, 0);
    struct json_out json = JSON_OUT_MBUF(&buf);

    json_printf(&json, "{%Q:%d, %Q:%d, %Q:%.4f, %Q:%.4f, %Q:[ ",
                "samples", statistics->samples,
                "length", statistics->size,
                "mean", statistics->mean,
                "std_deviation", statistics->std_deviation,
                "data"

    );
    for (int i = 0; i < statistics->size; i++) {
        json_printf(&json, "%.4f", statistics->data[i]);
        if (i < statistics->size - 1) {
            json_printf(&json, ", ");
        }
    }
    json_printf(&json, " ] ");
    json_printf(&json, " }");
    return buf.buf;

}

// TODO:  if statistics->samples == 1 -> collapse calculations below to do nothing
void calculate_statistics(struct d_statistics *statistics) {
    double mean_sum = 0.0;
    double *data = statistics->data;
    for (int i = 0; i < statistics->size; i++) {
        mean_sum += data[i];
        LOG(LL_DEBUG, ("mean_sum -> %f,  data[%d] = %f", mean_sum, i, data[i]));
    }
    statistics->mean = mean_sum / statistics->size;
    LOG(LL_DEBUG, ("statistics->mean -> %f", statistics->mean));

    double std_dev_sum = 0.0;
    double std_dev_i = 0.0;
    for (int i = 0; i < statistics->size; i++) {
        std_dev_i = data[i] - statistics->mean;
        std_dev_sum += std_dev_i * std_dev_i;
    }
    statistics->std_deviation = sqrt(std_dev_sum / (statistics->size - 1));
}
