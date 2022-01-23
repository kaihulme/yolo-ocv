FROM "ubuntu:latest"

# Install prerequisites
RUN \
    apt-get update && apt-get upgrade -y \
    && apt-get install -y software-properties-common apt-file \
    && apt-add-repository -y ppa:deadsnakes/ppa \
    && apt-add-repository -y "deb http://security.ubuntu.com/ubuntu xenial-security main" \
    && apt-get update \
    && apt-get install -y build-essential g++ cmake git wget unzip \
    && apt-get install -y libgtk2.0-dev pkg-config libavcodec-dev \
    && apt-get install -y libavformat-dev libswscale-dev \
    && apt-get install -y python3.5-dev python3-numpy libtbb2 libtbb-dev \
    && apt-get install -y libjpeg-dev libpng-dev libtiff5-dev libjasper-dev \
    && apt-get install -y libdc1394-22-dev libeigen3-dev libtheora-dev \
    && apt-get install -y libvorbis-dev libxvidcore-dev libx264-dev \
    && apt-get install -y sphinx-common libtbb-dev yasm libfaac-dev \
    && apt-get install -y libopencore-amrnb-dev libopencore-amrwb-dev \ 
    && apt-get install -y libopenexr-dev libgstreamer-plugins-base1.0-dev \
    && apt-get install -y libavutil-dev libavfilter-dev libavresample-dev< \
    && apt-get install -y libjasper1 libjasper-dev


# Download and extract OpenCV
RUN \
    cd /opt \
	wget -O opencv.zip https://github.com/opencv/opencv/archive/4.x.zip \
	&& wget -O opencv_contrib.zip https://github.com/opencv/opencv_contrib/archive/4.x.zip \
	&& unzip opencv.zip && rm opencv.zip \
	&& unzip opencv_contrib.zip && rm opencv_contrib.zip

# Build and install OpenCV	
RUN \
	mkdir -p build && cd build \
	&& cmake -DOPENCV_EXTRA_MODULES_PATH=../opencv_contrib-4.x/modules ../opencv-4.x \
	&& cmake --build .

