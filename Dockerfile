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
    firefox \
    python3 \
    cmake \
    git \
    build-essential \
    libglfw3 \
    libglfw3-dev \
    xorg \
    xvfb \
    xauth \
    x11vnc \
    libgl1-mesa-dev \
    libglu1-mesa-dev 

RUN git clone --recursive https://github.com/Dav1dde/glad.git /tmp/glad

RUN cd /tmp/glad/cmake && \
    cmake . && \
    make 

RUN cd /usr/local/lib/ \
    git clone https://github.com/glfw/glfw.git \
    cd glfw \
    cmake . \
    make \
    sudo make install

ENV XAUTHORITY=/.Xauthority

# Set the working directory
WORKDIR /app

# Copy the source code into the container
COPY . /app

# Build the project
RUN cmake . && make

EXPOSE 8080

# Build the project
# RUN ./bin/make.sh

# Set the entrypoint to run the compiled executable
CMD [ "/usr/bin/firefox" ]
ENTRYPOINT [ "./GraphicsEngine" ]
