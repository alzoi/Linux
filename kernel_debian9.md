# Установка ядра для Debian 9

https://linuxhint.com/how-to-upgrade-kernel-of-debian-9-stretch-from-source/

Проверяем версию дистрибутива и ядра

    sudo su -
    lsb_release -a
    uname -r

Обновляем список источнико для скачивания пакетов

    nano /etc/apt/sources.list

В файл добавляем следующие строки

    deb http://security.debian.org/debian-security stretch/updates main
    deb-src http://security.debian.org/debian-security stretch/updates main
    deb http://mirror.yandex.ru/debian stretch main contrib non-free
    deb-src http://mirror.yandex.ru/debian stretch main contrib non-free
    deb [arch=amd64] https://download.docker.com/linux/debian stretch stable

Скачиваем ядро версии 4.9 с патчем 65

    cd /usr/src/
    wget https://www.kernel.org/pub/linux/kernel/v4.x/linux-4.9.65.tar.xz

Установка необходимых для компиляции ядра компонентов
    
    apt-get install build-essential libncurses5-dev gcc libssl-dev bc -y
