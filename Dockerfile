FROM debian:bullseye

# Установка необходимых пакетов
RUN apt update && apt install -y \
    build-essential \
    libx11-dev \
    libxext-dev \
    libbsd-dev \
    libxrandr-dev \
    libxrender-dev \
    libxfixes-dev \
    libxshm-dev \
    libxi-dev \
    git \
    make \
    nano \
    pkg-config \
    x11-apps

# Создаем рабочую директорию
WORKDIR /app
