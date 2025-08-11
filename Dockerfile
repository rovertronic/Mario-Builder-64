FROM archlinux:base-20250803.0.394512 as build

RUN pacman -Syu --noconfirm && \
    pacman -S --noconfirm \
        util-linux \
        base-devel \
        capstone \
        pkgconf \
        python \
        git \
        wget

# Create a non-root user for building AUR packages
RUN useradd -m -G wheel builder && \
    echo 'builder ALL=(ALL) NOPASSWD: ALL' >> /etc/sudoers

# Install yay AUR helper and mips64-elf-binutils from AUR
WORKDIR /tmp
RUN git clone https://aur.archlinux.org/yay.git yay
RUN chown -R builder:builder yay
WORKDIR /tmp/yay
RUN sudo -u builder makepkg -si --noconfirm
RUN sudo -u builder yay -S --noconfirm mips64-elf-newlib
RUN sudo -u builder yay -S --noconfirm mips64-elf-toolchain
RUN sudo -u builder yay -S --noconfirm mips64-elf-binutils
# RUN sudo -u builder yay -S --noconfirm mips64-elf-gcc

# Lazily doing more python stuff after because it took 30+ minutes to compile all of the above
RUN pacman -S --noconfirm \
        python \
        python-pip
RUN python -m venv /opt/pyenv
RUN /opt/pyenv/bin/pip install pypng bitstring
ENV PATH="/opt/pyenv/bin:${PATH}"
ENV VIRTUAL_ENV="/opt/pyenv"

RUN mkdir /sm64
WORKDIR /sm64
ENV PATH="/sm64/tools:${PATH}"

CMD echo 'usage: docker run --rm --mount type=bind,source="$(pwd)",destination=/sm64 sm64 make VERSION=us -j4\n' \
         'see https://github.com/n64decomp/sm64/blob/master/README.md for advanced usage'
