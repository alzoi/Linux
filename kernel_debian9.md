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

Обновляем репозиторий пакетов

    apt-get update

Устанавливаем необходимые для компиляции ядра компоненты
    
    apt-get install build-essential libncurses5-dev gcc libssl-dev bc -y

Скачиваем архив исходников ядра Linux версии 4.9 с патчем 65 и распаковываем его в папку /usr/src/linux-4.9.65

    cd /usr/src/
    wget https://www.kernel.org/pub/linux/kernel/v4.x/linux-4.9.65.tar.xz
    tar xvf linux-4.9.65.tar.xz

Создаём новую ссылку на исходники нового ядра /usr/src/linux/ и переходим в эту папку
    
    mv linux _linux
    ln -s /usr/src/linux-4.9.65/ /usr/src/linux/
    cd /usr/src/linux/
    
   
    
