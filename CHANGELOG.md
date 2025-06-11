# Changelog

## [1.1.0](https://github.com/VU-ASE/roverlib-c/compare/v1.0.4...v1.1.0) (2025-06-11)


### Features

* added configuration and stream tests ([f85ed5c](https://github.com/VU-ASE/roverlib-c/commit/f85ed5c3dfff70340c917a3af977825f8def1088))
* added extra tests and some NULL checking ([0c340b1](https://github.com/VU-ASE/roverlib-c/commit/0c340b1f45f158973262d1123b2a75e1727a9bc6))
* added some helper functions for bootinfo ([39caa21](https://github.com/VU-ASE/roverlib-c/commit/39caa2143e9d2285b4f605d45b8b737f6aff4175))
* cloning dep is now in the makefile ([865fd89](https://github.com/VU-ASE/roverlib-c/commit/865fd89744e38837b32d6040006ab34939f6d47b))
* include bootspec validation checks ([1092552](https://github.com/VU-ASE/roverlib-c/commit/10925523148c2a50c370e189ec6e4e874f17d605))


### Bug Fixes

* added return NULL for missing mandatory fields ([08d4d2b](https://github.com/VU-ASE/roverlib-c/commit/08d4d2b7d9cd66591d7ec6ba036fa6484d7f8079))
* added thread clean up logic ([270182c](https://github.com/VU-ASE/roverlib-c/commit/270182ca14ac6710a51ce14b6167fd6570cfce79))
* linkage of dependencies on first clone ([b25b805](https://github.com/VU-ASE/roverlib-c/commit/b25b8053aec7e9d1247a3b7dadd11662ae3e9104))
* prevent eternal "expected" tests with reused action ([6adba4e](https://github.com/VU-ASE/roverlib-c/commit/6adba4e7420d7af1f16fb16a0abeb344ef0d85c9))
* release-please PR eternally expected ([3559b1b](https://github.com/VU-ASE/roverlib-c/commit/3559b1bb75c531ea10669b73e6550f1b1927cd5b))

## [1.0.4](https://github.com/VU-ASE/roverlib-c/compare/v1.0.3...v1.0.4) (2025-03-30)


### Bug Fixes

* changed relative links to urls (max) ([d87e4cc](https://github.com/VU-ASE/roverlib-c/commit/d87e4cc523c86924a63b2cf242caede9ffe0dcf3))
* paths in include statements are now correct ([cca8124](https://github.com/VU-ASE/roverlib-c/commit/cca8124326b4f011780baccce8f06232e4539a39))

## [1.0.3](https://github.com/VU-ASE/roverlib-c/compare/v1.0.2...v1.0.3) (2025-03-30)


### Bug Fixes

* wrapper files missing lidar, generic and current ([666c487](https://github.com/VU-ASE/roverlib-c/commit/666c4877c52d7e82631c477fe0a47e4e860ac2d4))

## [1.0.2](https://github.com/VU-ASE/roverlib-c/compare/v1.0.1...v1.0.2) (2025-03-29)


### Bug Fixes

* rovercom update ([2f79143](https://github.com/VU-ASE/roverlib-c/commit/2f79143eac364159327182a58de09a7762eda0b8))

## [1.0.1](https://github.com/VU-ASE/roverlib-c/compare/v1.0.0...v1.0.1) (2025-03-28)


### Bug Fixes

* change socket type REQ -&gt; SUB ([bd29b7d](https://github.com/VU-ASE/roverlib-c/commit/bd29b7de0c9ac0ca4cbe49823efbb6e9cc846ae1))
* hash table initialization ([4776bf2](https://github.com/VU-ASE/roverlib-c/commit/4776bf23c372a1549f213c91a2543cc1b8513363))

## 1.0.0 (2025-03-26)


### Features

* add GDB to test program ([061866f](https://github.com/VU-ASE/roverlib-c/commit/061866f725c83de324ad1c5c6d5f7a7fd8d9252b))
* add test files and makefile ([e7adba1](https://github.com/VU-ASE/roverlib-c/commit/e7adba115afdc1adcc84852021ceefee892a48ee))
* compliant with merged float/int rovervalidate schema ([6abd94a](https://github.com/VU-ASE/roverlib-c/commit/6abd94a39f951d7b043fa1aeae0366adc2c1b16c))
* full integration (experimental) ([0931405](https://github.com/VU-ASE/roverlib-c/commit/0931405028871fc8ae50632e499d7ea46b48b5d7))
* moved from shared object to static library structure ([f878aff](https://github.com/VU-ASE/roverlib-c/commit/f878affc0b3aa6d88da588ee55b74acf6fa33625))
* roverlib-c compliant with linux installation through cmake ([018037a](https://github.com/VU-ASE/roverlib-c/commit/018037aabce6c52ab7c86362036dcca9ccddb951))
* set up devcontainer and basic architecture with quicktype ([0b80e7b](https://github.com/VU-ASE/roverlib-c/commit/0b80e7bee0e5e24fc1761852571eec8b6719ed12))


### Bug Fixes

* add dependency build step ([ba3c42a](https://github.com/VU-ASE/roverlib-c/commit/ba3c42a56b2b8b93d6bea34e4e3466fc1e613282))
* added dynamic buffer and changed stream name ([b93ddaa](https://github.com/VU-ASE/roverlib-c/commit/b93ddaa985ea77052a7b15408b92d9e5a0446b77))
* always pass "floats" as doubles ([99626f2](https://github.com/VU-ASE/roverlib-c/commit/99626f2717463b3e9985af2b0d25d7f26b47b472))
* configuration values not loaded properly ([e2c9854](https://github.com/VU-ASE/roverlib-c/commit/e2c985449288ba3e656c37a0b5073f2061510621))
* missing cd build ([c8ac8e2](https://github.com/VU-ASE/roverlib-c/commit/c8ac8e2f37540c976453fb933c26caae1e182181))
* moved main.c to test dir and docs ([0a247c5](https://github.com/VU-ASE/roverlib-c/commit/0a247c5a07befdf023f1a3d113716e2b023f90ef))
* properly check return code on write in test code ([760fdb5](https://github.com/VU-ASE/roverlib-c/commit/760fdb5b099bd38cc7dfcc9e712c8a955c6da8ea))
* removed non-existent lint-target ([332bcc8](https://github.com/VU-ASE/roverlib-c/commit/332bcc8fbf9db2dc65b2d18996f277d289c53956))
