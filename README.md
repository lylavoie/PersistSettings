# PersistSettings

Persistent Settings / Config storage library for Arduino framework on ESP32 / ESP8266 devices,
using the NVS partition.

Config object / settings are stored as a CRC16 protected byte array within the NVS partition 
of the device's flash.  The config object can be any structure or class object, but must
initialize its members to default values. The constructor requires a non-zero version
identifier, which should be change if the data layout of the config object is changed.  It's
recommended this identifier by "built-into" the config object, as a static constant, if only
to "co-locate" it with the object definition.  

When reading the config object from the persistent storage, the following checks are 
performed on the data.  If any check fails, the config object is reset to the default
values.

1. Persistent NVS name space is not initialized (i.e. no config has previously been stored)
1. The version does not match the expected version
1. The size of the object read does not match the template object provided
1. The CRC16 indicates an error in the data

## Quick Start

1. Define an object to use as the config, with default values.
1. Construct the PersistSettings object using the config as a template.
1. Call the Begin() method to read the config from the NVS.
1. Access / update the config values through the Config member of PersistSettings.
1. Use the Write() method to save any changes to the Config member values.
1. Use the ResetToDefault() method to reset (and write) the defauls back to NVS.

## Examples

* [examples/simple_config](examples/simple_config/simple_config.cpp) - Stores
a simple configuration struct to the NVS, that contains an integer value.  That value is
incremented and stored each time the platform is reset.