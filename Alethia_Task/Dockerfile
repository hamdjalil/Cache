FROM gcc:latest

COPY . /usr/src/dockertest1

WORKDIR /usr/src/dockertest1

RUN g++ task.pp -o task task.cpp

CMD ["./task"]