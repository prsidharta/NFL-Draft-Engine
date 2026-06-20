FROM gcc:latest

RUN apt-get update && apt-get install -y cmake python3 python3-pip

RUN useradd -m -u 1000 appuser

WORKDIR /app

COPY --chown=appuser:appuser . /app

USER 1000

RUN mkdir build && cd build && cmake .. && make

CMD ["./build/redraftNFL"]