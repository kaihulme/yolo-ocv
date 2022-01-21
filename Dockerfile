FROM "ubuntu:latest"

RUN \
	apt-get update -y \
	&& apt-get install -y cmake g++ wget unzip \
	&& wget -O opencv.zip https://github.com/opencv/opencv/archive/4.x.zip \
	&& unzip opencv.zip \
	&& mkdir -p build && cd build \
	&& cmake  ../opencv-4.x \
	&& cmake --build .
