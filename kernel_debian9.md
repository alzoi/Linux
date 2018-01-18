# Установка ядра Linux для Debian 9

https://linuxhint.com/how-to-upgrade-kernel-of-debian-9-stretch-from-source/  
https://debian-handbook.info/browse/stable/sect.kernel-compilation.html  
https://kali.training/topic/recompiling-the-linux-kernel/

Проверка свободного места на дисках системы
    
    sudo su -
    cd /
    du -sh *
    
Проверяем версию дистрибутива и ядра

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

Удаление старых скомпилированных файлов и конфигураций

    make clean
    make distclean

Для использования существующего конфигурационного файла работающего ядра копируем в папку исходников нового ядра 

    cp /boot/config-$(uname -r) .config
    
Выполняем конфигурирование ядра на основе файла /usr/src/linux/.config

    make menuconfig

выбираем в меню конфигуратора пункт "Exit" и "Save".

Сборка (компиляция) ядра Linux
    
    make deb-pkg

Для сборки ядра потребуется более 18 ГБ свободного места на жёстком диске.  
При компиляции ядра данные будут генерироваться в папке /usr/src/linux-4.9.65/.

deb-пакеты нового ядра будут созданы в папке /usr/src/ появятся файлы /usr/src/linux-*4.9.65*.deb
    
    ls ../linux-*4.9.65*.deb -l

Для установки нового ядра нужно выполнить установку всех созданных deb пакетов нового ядра (пакеты можно переносить и устанавливать на других машинах той же архитектуры)

    dpkg -i /usr/src/linux-*4.9.65*.deb

Перезагружаемся и проверяем версию ядра

     init 6
     uname -r
     

    
