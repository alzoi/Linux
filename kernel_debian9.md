# Установка ядра для Debian 9

https://linuxhint.com/how-to-upgrade-kernel-of-debian-9-stretch-from-source/

    sudo su -
    lsb_release -a
    uname -r
Скачиваем ядро версии 4.9 с патчем 65

    cd /usr/src/
    wget https://www.kernel.org/pub/linux/kernel/v4.x/linux-4.9.65.tar.xz

Установка необходимых для компиляции ядра компонентов
    
    apt-get install build-essential libncurses5-dev gcc libssl-dev bc -y
