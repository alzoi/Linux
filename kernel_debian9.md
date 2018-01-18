# Установка ядра для Debian 9

https://linuxhint.com/how-to-upgrade-kernel-of-debian-9-stretch-from-source/  
https://debian-handbook.info/browse/stable/sect.kernel-compilation.html

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

Для использования существующего конфигурационного файла работающего ядра копируем в папку исходников нового ядра 

    cp /boot/config-$(uname -r) .config
    
Выполняем конфигурирование ядра на основе файла /usr/src/linux/.config

    make menuconfig

выбираем в меню конфигуратора пункт "Exit" и "Save".

Сборка (компиляция) ядра (потребуется 12 ГБ места на жёстком диске)
    
    make deb-pkg
    
deb-пакеты нового ядра будут созданы в папке /usr/src/ появятся файлы /usr/src/linux-*4.9.65*.deb
    
    ls /usr/src/ | grep linux-*4.9.65*.deb
    ls ../*.deb

Для установки нового ядра нужно выполнить

    dpkg -i /usr/src/linux-*4.9.65*.deb

Перезагружаемся и проверяем версию ядра

     init 6
     uname -r
     

    
