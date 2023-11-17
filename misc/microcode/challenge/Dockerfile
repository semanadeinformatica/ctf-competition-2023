FROM bitnami/minideb:bookworm

# Install system dependencies
RUN install_packages curl unzip ca-certificates build-essential python3

# Create challege user
RUN useradd -m rob
RUN chsh -s /bin/bash rob

USER rob
WORKDIR /home/rob

# Setup toolchains

RUN mkdir toolchains

## Setup Rust Toolchain
ARG RUSTUP_INIT=./toolchains/rustup-init.sh
RUN curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs > ${RUSTUP_INIT}
RUN chmod +x ${RUSTUP_INIT}
RUN ${RUSTUP_INIT} -y --profile minimal

## Setup Deno Toolchain
ARG DENO_INIT=./toolchains/deno-init.sh
RUN curl -fsSL https://deno.land/x/install/install.sh > ${DENO_INIT}
RUN chmod +x ${DENO_INIT}
RUN ${DENO_INIT}

# Make toolchains available to all users
USER root
RUN ln -s /home/rob/.cargo/bin/* /usr/bin/
RUN ln -s /home/rob/.deno/bin/deno /usr/bin/deno

# Setup passwords
RUN echo "root:rob1989" | chpasswd
RUN echo "rob:rob1989" | chpasswd

# Setup flag
WORKDIR /root
RUN chmod 744 /root
COPY fs/flag.txt ./

# Setup passwords hint
USER rob
WORKDIR /home/rob

COPY fs/passwords.txt ./

# Prepare challenge
WORKDIR /home/rob/microcode

# Cache the dependencies as a layer (the following two steps are re-run only when deps.ts is modified).
# Ideally cache deps.ts will download and compile _all_ external files used in main.ts.
COPY src/deps.ts deps.ts
RUN deno cache deps.ts

# These steps will be re-run upon each file change in the challenge source files:
ADD src ./

# Compile the main app so that it doesn't need to be compiled each startup/entry.
RUN deno cache main.ts

EXPOSE 8000

CMD [ "deno", "run", "--allow-all", "main.ts" ]
