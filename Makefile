clean:
	rm -rf ./builds
builds:
	arduino-cli compile --build-property "compiler.cpp.extra_flag='-DSTART_MESSAGE=\"OTA BUILD RUN\"' -DVERSION=3" --config-file ./.cli-config.yml --fqbn esp8266:esp8266:nodemcuv2 sensor.ino --output-dir ./builds/cabinet