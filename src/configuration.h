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
    hashtable_t* numberValues;
    hashtable_t* stringValues;
    hashtable_t* tunable;
    pthread_rwlock_t *rwlock;
    int64_t last_update;
} ServiceConfiguration;

ServiceConfiguration NewServiceConfiguration() {
    ServiceConfiguration config;
    config.numberValues = hashtable_create(16, false);
    config.stringValues = hashtable_create(16, false);
    config.tunable = hashtable_create(16, false);
    config.rwlock = (pthread_rwlock_t *)malloc(sizeof(pthread_rwlock_t));
    pthread_rwlock_init(config.rwlock, NULL);
    config.last_update = 0;
    return config;
}

#endif // CONFIGURATION_H