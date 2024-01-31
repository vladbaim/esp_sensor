clean:
	rm -rf ./builds
builds:
	arduino-cli compile --build-property "build.extra_flags=-DVERSION=3 \"-DSTART_MESSAGE=\"OTA BUILD RUN\"\"" --config-file ./.cli-config.yml --fqbn esp8266:esp8266:nodemcuv2 sensor.ino --output-dir ./builds/cabinet