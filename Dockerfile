#===============================================================================================
#   this is for building the environment (ubuntu Ubuntu 26.04 LTS)
#   lsb_release -a
#   No LSB modules are available.
#   Distributor ID: Ubuntu
#   Description:    Ubuntu 26.04 LTS
#   Release:        26.04
#   Codename:       resolute
#
#   i need the docker image to create an ubuntu instance of the os as my environment
#===============================================================================================
FROM ubuntu:26.04 AS environment_builder

ENV DEBIAN_FRONTEND=nointeractive

# these instructions or commands will be ran sequencial from ubuntu:26.04
RUN apt-get update
RUN apt-get install -y build-essential
RUN apt-get install -y cmake
RUN apt-get install -y ninja-build
RUN apt-get install -y gdb
RUN apt-get install -y git
RUN apt-get install -y pkg-config
RUN apt-get install -y sqlite3
RUN apt-get install -y libsqlite3-dev
RUN apt-get install -y nlohmann-json3-dev
RUN apt-get install -y catch2
RUN apt-get install -y libcpp-httplib-dev
RUN rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . .

RUN cmake -B build -S .
RUN cmake --build build -j$(nproc)

#===============================================================================================
#   this is for building the run space (ubuntu Ubuntu 26.04 LTS)
#   lsb_release -a
#   No LSB modules are available.
#   Distributor ID: Ubuntu
#   Description:    Ubuntu 26.04 LTS
#   Release:        26.04
#   Codename:       resolute
#
#   i need the docker image to create an ubuntu instance of the os as my environment
#===============================================================================================
FROM ubuntu:26.04 AS runtime_space

ENV DEBIAN_FRONTEND=nointeractive

RUN apt-get update
RUN apt-get install -y sqlite3
RUN apt-get install -y libsqlite3-0
RUN apt-get install -y libpq5
RUN apt-get install -y libcpp-httplib0.26
RUN rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY --from=environment_builder /app/bin/NchabiChickens .

COPY --from=environment_builder /app/database ./database

EXPOSE 8080

CMD ["./NchabiChickens"]