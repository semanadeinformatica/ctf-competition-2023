# Builder for the challenge
FROM bitnami/java:17 AS build
# Don't use root for build
RUN useradd -m build
USER build

WORKDIR /usr/build

# Download gradle
COPY --chown=build:build serial-killer/gradle ./gradle
COPY --chown=build:build serial-killer/gradlew ./
RUN ./gradlew --no-daemon

# Compile challenge package
COPY --chown=build:build serial-killer ./
RUN ./gradlew installDist --no-daemon

# Runner for the challenge
FROM bitnami/java:17

RUN install_packages python3 ncat

# Create challenge user
RUN useradd -m ella
RUN chsh -s /bin/bash ella

USER ella

WORKDIR /home/ella/serial-killer
COPY --from=build --chown=ella:ella /usr/build/app/build/install/app ./

WORKDIR /home/ella

# Initialize serialized files
COPY --chown=ella:ella fs/ella ./
RUN cat flag.txt | xargs ./serial-killer.sh
RUN rm flag.txt

USER root

WORKDIR /root
COPY fs/root ./

EXPOSE 8000

CMD [ "/root/entrypoint.sh" ]
