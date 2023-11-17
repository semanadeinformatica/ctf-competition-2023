FROM docker.io/ubuntu:jammy AS app
# and from now on, do the build steps as usual :)

# NOTE (luisd): insert challange build-steps here!

RUN mkdir app
WORKDIR app
COPY message ./
COPY flag.txt ./

FROM pwn.red/jail

#image used inside the jail

COPY --from=app / /srv


# to make configuration more simple you can link your binary into /srv/app/run
# for testing, we use the /bin/sh binary

COPY message /srv/app/run 

# If you aren't running a simple binary eg.: python, you probably want to increase the cpu and mem parameters
ENV JAIL_TIME=0 JAIL_CPU=50 JAIL_MEM=5M