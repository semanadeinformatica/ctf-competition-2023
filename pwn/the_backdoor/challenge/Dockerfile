FROM ubuntu:20.04 as app

# Install required packages
RUN apt-get update \
    && apt-get install -y --no-install-recommends \
        socat \
        libssl1.1 \
    && rm -rf /var/lib/apt/lists/*

# Copy necessary files
WORKDIR /app
COPY fs/flag.txt fs/the_backdoor /app/

FROM pwn.red/jail

#image used inside the jail

COPY --from=app / /srv

# to make configuration more simple you can link your binary into /srv/app/run
# for testing, we use the /bin/sh binary
RUN ln -s /app/the_backdoor /srv/app/run 

# If you aren't running a simple binary eg.: python, you probably want to increase the cpu and mem parameters
ENV JAIL_TIME=0 JAIL_CPU=50 JAIL_MEM=5M