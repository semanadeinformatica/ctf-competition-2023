FROM docker.io/ubuntu:jammy AS app
RUN apt-get update && apt-get install socat zsh -y

RUN ln -sf /usr/bin/zsh /bin/sh 

# Create user
ENV USER_NAME=user
RUN useradd -m ${USER_NAME}
RUN useradd -m joao

COPY --chmod=666 entrypoint.sh .

# Add files
WORKDIR /home/${USER_NAME}/
RUN mkdir programs
COPY --chown=user:user /shell-files/programs/ ./programs
COPY --chown=joao:joao /shell-files/robot_factory ./
RUN chmod 4555 robot_factory

COPY --chown=joao:joao --chmod=600 flag.txt /home/${USER_NAME}/.

USER ${USER_NAME}
EXPOSE 5000
CMD ["/bin/sh", "/entrypoint.sh"]
