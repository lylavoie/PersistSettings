/* SPDX-License-Identifier: MIT
 * Copyright(c) 2022 Lincoln Lavoie <lincoln.lavoie@gmail.com>
 */

#include <Arduino.h>
#include <PersistSettings.h>

struct ConfigObject{
    // Indicates the version of the data structure.  Can not be zero and must
    // change anytime there would be a change to the byte ordering within the 
    // object (i.e. add a member object or change an array length).
    static const unsigned int Version = 1;  

    // All values should be initialized to their default values.  This
    // onject typedef is used to reset the object to the default values
    // if the settings can not be read from the persistent storage, an
    // error is detected, the version changes, or ResetToDefault() is called.
    int Setting1 = 0;
    char Setting2[20] = "Foo";
    bool Setting3 = false;
}

// Construct PersistSettings object with the template of our
// configuration object, and provide the expected version of
// the configuration. 
PersistSettings<ConfigObject> Settings(ConfigObject::Version);

void setup(){

    // Read the object from the persistent storage.  Before this 
    // call, the Settings.Config object would have only the default
    // values and Settings.Valid() will return false.
    Settings.begin();

    // Verify a valid Config is available and update a value.
    if( Settings.Valid() ){
        Settings.Config.Setting1++;
    }

    // Save the updated Config to the persistent storage.
    Settings.Write();

    // Log a result for the user.  This value should increase
    // each time the platform is reset.
    Serial.begin(9600);
    Serial.printf("Setting1 Value: %d\r\n", Settings.Config.Setting1);
}

void loop(){
    // NO-OP
}