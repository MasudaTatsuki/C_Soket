FROM debian:unstable-20240701-slim

RUN apt-get update && \
    apt-get install -y gcc g++ make

WORKDIR /app

# RUN cd /app
COPY EchoServer.c .
COPY entrypoint.sh .

RUN ls -lta
RUN ["chmod", "+x", "/app/entrypoint.sh"]
RUN chmod 755 entrypoint.sh

# ENTRYPOINT ["/app/entrypoint.sh"]
