#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <stdlib.h>
#include <hashtable.h>
#include <pthread.h> 

/**
 * A "configuration" object holds the runtime options for a user program during the entire run.
 * its values and options are maintained by roverlib - so that if tunings arrive over the air (ota), 
 * they will be applied to the user program which can then access them. Because the configuration object is 
 * updated in a separate thread, the user program can access the keys and values of the configuration object while an update is being applied.
 * hence "safe" methods are defined, which use a mutex to ensure that the user program and roverlib can safely concurrently read/write the configuration object.
 *
 * @note: this implementation depends on the https://github.com/joelguittet/c-hashtable library, which was used by quicktype already, so easy to reuse
 */

typedef struct {
    hashtable_t* float_values;
    hashtable_t* string_values;
    hashtable_t* tunable;
    pthread_rwlock_t *rwlock;
    int64_t last_update;
} Service_configuration;

Service_configuration new_service_configuration(Service service) {
    Service_configuration config;
    config.float_values = hashtable_create(16, false);
    config.string_values = hashtable_create(16, false);
    config.tunable = hashtable_create(16, false);
    config.rwlock = (pthread_rwlock_t *)malloc(sizeof(pthread_rwlock_t));
    pthread_rwlock_init(config.rwlock, NULL);
    config.last_update = 0;

    Configuration *option = list_get_head(service.configuration);
    while (option != NULL) {
        switch (option->value->type) {
            case TYPE_FLOAT:
                hashtable_add(config.float_values, option->name, &option->value->value.number, sizeof(double));
                break;
            case TYPE_STRING:
                hashtable_add(config.string_values, option->name, option->value->value.string, strlen(option->value->value.string));
                break;
        }
        if (option->tunable) {
            hashtable_add(config.tunable, option->name, NULL, 0);
        }

        option = list_get_next(service.configuration);        
    }

    return config;
}

void set_number_value(Service_configuration *config, char *key, double value) {
    pthread_rwlock_wrlock(config->rwlock);

    // Check if this key is tunable
    if (hashtable_has_key(config->tunable, key)) {
        // If it is tunable, update the value
        hashtable_remove(config->float_values, key);
        hashtable_add(config->float_values, key, &value, sizeof(double));
    }

    pthread_rwlock_unlock(config->rwlock);
}

void set_string_value(Service_configuration *config, char *key, char *value) {
    pthread_rwlock_wrlock(config->rwlock);

    // Check if this key is tunable
    if (hashtable_has_key(config->tunable, key)) {
        // If it is tunable, update the value
        hashtable_remove(config->string_values, key);
        hashtable_add(config->string_values, key, value, strlen(value));
    }

    pthread_rwlock_unlock(config->rwlock);
}

#endif // CONFIGURATION_H