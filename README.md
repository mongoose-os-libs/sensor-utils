# A Formula Library for Mongoose OS apps


## Overview

A collection of C-functions with JS wrappers that make it convenient to calculate derived quantities (e.g. dew point temperature),
convert between different units of measure, and perform simple statistics on arrays of (double precision)
values.

### Typical usage pattern:

in _**mos.yml**_, add to **libs:** section,

`  - origin: https://github.com/pedalPusher68/formula_utils `
  
in your _**init.js**_, add something like the following,

```javascript
load('api_formula_utils.js');
```

and (here is example usage that tests the API),

```javascript
print('Test api_formula_utils.js          ');


//Initialize a statistics object (handle)

let StatsObj = FormulaUtils.initStatistics(4);

// add some numbers (e.g. obtained from sensor readings)

FormulaUtils.addDataValue( StatsObj, 5.51 );
FormulaUtils.addDataValue( StatsObj, 8.43 );
FormulaUtils.addDataValue( StatsObj, 6.77 );
FormulaUtils.addDataValue( StatsObj, 4.33 );
FormulaUtils.addDataValue( StatsObj, 6.20 );
FormulaUtils.addDataValue( StatsObj, 7.18 );
FormulaUtils.addDataValue( StatsObj, 4.92 );
FormulaUtils.addDataValue( StatsObj, 5.89 );

print('Statistics:  ',FormulaUtils.calculateStatistics(StatsObj));

// other convenience functions.

print('FormulaUtils.fahrenheit(0.0) -> ',FormulaUtils.fahrenheit(0.0));
print('FormulaUtils.celsius(32.0) -> ',FormulaUtils.celsius(32.0));
print('FormulaUtils.inchesHg(101325) -> ',FormulaUtils.inchesHg(101325));
print('FormulaUtils.mmHg(101325) -> ',FormulaUtils.mmHg(101325));
print('FormulaUtils.atmospheresHg(29.9213) -> ',FormulaUtils.atmospheresHg(29.9213));
print('FormulaUtils.atmospheresP(101325) -> ',FormulaUtils.atmospheresP(101325));
print('FormulaUtils.lengthF(1/12) -> ',FormulaUtils.lengthF(1.0/12.0));
print('FormulaUtils.computeDewpoint(4.6, 50.89) -> ',FormulaUtils.computeDewpoint(4.6, 50.89));
print('FormulaUtils.computeAltitude(103245.5, 101325.0) -> ',FormulaUtils.computeAltitude(103245.5, 101325.0));
```
Executing the above JS code on an ESP32 typically gives the following output:

```
[Jan 17 08:35:35.996] Test api_formula_utils.js

[Jan 17 08:35:36.183] Statistics:   {"samples":8, "length":8, "mean":6.1538, "std_deviation":1.3065, "data":[ 5.5100, 8.4300, 6.7700, 4.3300, 6.2000, 7.1800, 4.9200, 5.8900 ]  },

[Jan 17 08:35:36.214] FormulaUtils.fahrenheit(0.0) ->  32
[Jan 17 08:35:36.226] FormulaUtils.celsius(32.0) ->  0
[Jan 17 08:35:36.239] FormulaUtils.inchesHg(101325) ->  29.921252
[Jan 17 08:35:36.255] FormulaUtils.mmHg(101325) ->  1.178002
[Jan 17 08:35:36.268] FormulaUtils.atmospheresHg(29.9213) ->  1.000043
[Jan 17 08:35:36.282] FormulaUtils.atmospheresP(101325) ->  1
[Jan 17 08:35:36.295] FormulaUtils.lengthF((2.54/100.0) * 12) ->  1.000000
[Jan 17 08:35:36.313] FormulaUtils.computeDewpoint(4.6, 50.89) ->  -4.634330
[Jan 17 08:35:36.330] FormulaUtils.computeAltitude(103245.5, 101325.0) ->  -158.677439

```