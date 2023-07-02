# Use a base image with OpenGL support (e.g., NVIDIA's official OpenGL image)
FROM nvidia/opengl:1.2-glvnd-runtime-ubuntu20.04

# Install required packages
# RUN apt-get update && apt-get install tzdata && apt-get install -y \
#     build-essential \
#     cmake \
#     libglfw3-dev \
#     libglew-dev  

RUN apt-get update && apt-get install tzdata && apt-get install -y \
    g++ \
    cmake \
    libglfw3-dev \
    libgl1-mesa-dev \
    libglu1-mesa-dev 

# Set the working directory
WORKDIR /app

# Copy the source code into the container
COPY . /app

# Build the project
RUN ./bin/make.sh

EXPOSE 8080

# Set the entrypoint to run the compiled executable
ENTRYPOINT [ "./bin/main" ]
