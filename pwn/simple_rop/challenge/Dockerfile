FROM i386/ubuntu as app

RUN apt-get update && apt-get install -y socat

WORKDIR /app

COPY fs/flag.txt fs/simple_rop /app/

FROM pwn.red/jail

#image used inside the jail

COPY --from=app / /srv

# to make configuration more simple you can link your binary into /srv/app/run
# for testing, we use the /bin/sh binary
RUN ln -s /app/simple_rop /srv/app/run 

# If you aren't running a simple binary eg.: python, you probably want to increase the cpu and mem parameters
ENV JAIL_TIME=0 JAIL_CPU=50 JAIL_MEM=5M
