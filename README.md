# yolo-ocv

Object detection using YOLO-V3 with OpenCV.

## Requirements

- OpenCV2
- g++
- make
- YOLO-V3 (see below)

### Docker

A Dockerfile can be built which meets the requirements (requires [Docker](https://www.docker.com/)):

```bash
docker build .
```

This takes a while to build, an image can be pulled from [Docker Hub](https://hub.docker.com/repository/docker/kaihulme/ocv-cpp):

```bash
docker pull kaihulme/ocv-cpp:latest
```

#### docker-compose

To make use of [docker-compose](https://docs.docker.com/compose/), ensure image tag matches that configured in `docker-compose.yml`.

Run the following commands to run container using compose and enter interactive mode:

```bash
docker-compose up
docker-compose exec app bash
```

## Build and run

- Run `make` to build components.
- Run app with `./app`.

## YOLO-V3

This application requires configuration files for the YOLO-V3 neural network architecture, along with pre-trained weights.

Place the following files into `/resources/yolo`:

- `yolo3.cfg`
- `yolo3.weights`

Find these on [GitHub](https://github.com/AlexeyAB/darknet).
